#include <stddef.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "motor_fsm.h"

// --- IMPLEMENTAZIONE DELLE FUNZIONI HARDWARE (HAL) ---

void hw_set_motor(bool on) {
    if (on) {
        GPIOA->ODR |= GPIO_ODR_OD5;    // Accendi LED (Motore ON)
    } else {
        GPIOA->ODR &= ~GPIO_ODR_OD5;   // Spegni LED (Motore OFF)
    }
}

bool hw_read_button(void) {
    // PC13 è Active Low sulla Nucleo (premuto = 0)
    // Ritorniamo true se il tasto è premuto
    return !(GPIOC->IDR & GPIO_IDR_ID13);
}

float hw_read_temp(void) {
    // Simuliamo una temperatura costante di 25 gradi.
    // In un caso reale, qui leggeresti l'ADC.
    return 25.0f; 
}

// --- CONFIGURAZIONE PERIFERICHE ---

void hardware_init(void) {
    // 1. Abilita il clock per GPIOA (LED) e GPIOC (Tasto)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

    // 2. Configura PA5 come Output (LED)
    GPIOA->MODER &= ~(3UL << 10); // Clear bits 10-11
    GPIOA->MODER |=  (1UL << 10); // Set bit 10 (01: Output)

    // 3. Configura PC13 come Input (Tasto)
    GPIOC->MODER &= ~(3UL << 26); // Clear bits 26-27 (00: Input)
    // PC13 ha già una resistenza di pull-up esterna sulla Nucleo
}

// Funzione di delay molto semplice per il debouncing
void simple_delay(uint32_t count) {
    for (volatile uint32_t i = 0; i < count; i++);
}

// --- PUNTO DI INGRESSO ---

int main(void) {
    SystemInit();
    hardware_init();

    // Prepariamo la struttura con i puntatori alle funzioni hardware
    motor_fsm_hal_t hal;
    hal.set_motor = hw_set_motor;
    hal.read_button = hw_read_button;
    hal.read_temp = hw_read_temp;

    // Inizializziamo la FSM
    motor_fsm_init(&hal);

    while (1) {
        // Aggiorna la logica della FSM
        motor_fsm_update();

        // Piccolo delay per il debouncing del tasto fisico
        // Impedisce che una singola pressione venga letta come più pressioni
        simple_delay(20000); 
    }

    return 0;
}

// Se il tuo startup file punta a Reset_Handler invece che a main:
void Reset_Handler(void) {
    main();
}
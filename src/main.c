#include <stddef.h>
#include "stm32f4xx.h"
#include "motor_fsm.h"
#include "utils.h"

// Funzioni HAL per la FSM
void hw_set_motor(bool on) {
    if (on) GPIOA->ODR |= GPIO_ODR_OD5;
    else    GPIOA->ODR &= ~GPIO_ODR_OD5;
}

bool hw_read_button(void) {
    // PC13 è active low sulla Nucleo
    return !(GPIOC->IDR & GPIO_IDR_ID13);
}

int main(void) {
    // SystemInit() viene chiamata automaticamente dallo startup_stm32f446xx.S
    // quindi qui la FPU è già attiva.

    // 1. Configura l'hardware
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
    
    GPIOA->MODER &= ~(GPIO_MODER_MODER5);
    GPIOA->MODER |=  (GPIO_MODER_MODE5_0);
    
    GPIOC->MODER &= ~(GPIO_MODER_MODER13);

    // 2. Inizializza FSM
    motor_fsm_hal_t my_hal = {
        .set_motor = hw_set_motor,
        .read_button = hw_read_button,
        .read_temp = NULL // o una tua funzione
    };
    motor_fsm_init(&my_hal);

    // 3. Loop
    while (1) {
        // Se il pulsante è premuto (ID13 == 0), accendi il LED (OD5 = 1)
        if (!(GPIOC->IDR & GPIO_IDR_ID13)) {
            GPIOA->ODR |= GPIO_ODR_OD5;
        } else {
            GPIOA->ODR &= ~GPIO_ODR_OD5;
        }
    }
}
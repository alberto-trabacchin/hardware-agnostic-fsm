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
    // COMMENTA SystemInit(); <--- Fondamentale: potrebbe essere bloccata qui
    
    // Configurazione minima immediata
    RCC->AHB1ENR |= (1UL << 0); // GPIOA Clock
    GPIOA->MODER &= ~(3UL << 10);
    GPIOA->MODER |=  (1UL << 10); // PA5 Output
    
    while (1) {
        GPIOA->ODR |= (1UL << 5); // Accendi fisso
    }
}
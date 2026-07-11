#include "stm32f4xx.h"

extern void _Error_Handler(void); // Dichiarazione esterna per la funzione di errore

// Gestore dell'interrupt SysTick (per HAL_Delay)
void SysTick_Handler(void) {}

// Esempio di gestore fault (se non gestito altrove)
void HardFault_Handler(void) {
    while (1) {
        _Error_Handler();
    }
}

// Implementazione di default della funzione _Error_Handler
void _Error_Handler(void) {
    // Loop infinito per indicare un errore critico
    // In un'applicazione reale, qui si potrebbe accendere un LED di errore o resettare il sistema.
    while(1);
}
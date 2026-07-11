#include <stdint.h>

// 1. Indirizzi per STM32F446RE
#define RCC_AHB1ENR  (*(volatile uint32_t *)(0x40023830))
#define GPIOA_MODER  (*(volatile uint32_t *)(0x40020000))
#define GPIOA_ODR    (*(volatile uint32_t *)(0x40020014))

// 2. Setup dello Stack (Fine della RAM)
#define STACK_TOP    0x20020000

// Prototipi
void Reset_Handler(void);

// 3. Tabella dei Vettori Minima (forzata all'inizio del binario)
__attribute__((section(".isr_vector")))
const uint32_t vtable[] = {
    STACK_TOP,            // 0. Puntatore allo Stack
    (uint32_t)Reset_Handler // 1. Indirizzo di avvio
};

// 4. Punto di ingresso
void Reset_Handler(void) {
    // Abilita clock porta A
    RCC_AHB1ENR |= (1UL << 0);
    
    // Configura PA5 come output
    GPIOA_MODER &= ~(3UL << 10);
    GPIOA_MODER |=  (1UL << 10);

    while(1) {
        // ACCENDI IL LED FISSO
        GPIOA_ODR |= (1UL << 5);
        
        // Se vuoi vederlo lampeggiare, scommenta sotto
        /*
        for(volatile int i=0; i<500000; i++);
        GPIOA_ODR &= ~(1UL << 5);
        for(volatile int i=0; i<500000; i++);
        */
    }
}

// Funzioni dummy per il linker
void _exit(int status) { while(1); }
void SystemInit(void) {}
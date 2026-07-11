#include <stdint.h>

// Forziamo la tabella dei vettori nel file C come nel Codice 1
__attribute__((section(".isr_vector")))
const uint32_t vtable[] = {
    0x20020000,         // Stack Pointer
    (uint32_t)0x080000ed // Reset_Handler (Indirizzo di partenza)
};

void Reset_Handler(void) {
    // Indirizzi diretti (STM32F446RE)
    *(volatile uint32_t *)0x40023830 |= (1UL << 0);   // RCC_AHB1ENR -> GPIOA Clock
    *(volatile uint32_t *)0x40020000 &= ~(3UL << 10); // GPIOA_MODER
    *(volatile uint32_t *)0x40020000 |=  (1UL << 10); // PA5 Output

    while(1) {
        *(volatile uint32_t *)0x40020014 |= (1UL << 5); // GPIOA_ODR -> LED ON
    }
}

int main(void) {
    Reset_Handler();
    return 0;
}
#include "stm32f4xx_hal.h"
#include "motor_fsm.h"
#include <stdbool.h>

// Definizione dei PIN per la Nucleo-F446RE
#define LED_PIN          GPIO_PIN_5
#define LED_GPIO_PORT    GPIOA
#define BUTTON_PIN       GPIO_PIN_13
#define BUTTON_GPIO_PORT GPIOC

// Variabile globale di test per simulare la temperatura senza sensore fisico
static float simulated_temperature = 25.0f; 

// Prototipi delle funzioni
void SystemClock_Config(void);
void GPIO_Init(void);

// 1. Implementazione delle funzioni di callback per la FSM
void my_set_motor(bool state) {
    // Il LED sulla scheda si accende quando il motore è attivo
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

bool my_read_button(void) {
    // Il pulsante blu della Nucleo è in configurazione Active LOW (0 quando premuto)
    return HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN) == GPIO_PIN_RESET;
}

float my_read_temp(void) {
    // Restituisce la temperatura simulata
    return simulated_temperature;
}

// 2. Inizializzazione delle periferiche GPIO
void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Abilita i clock delle porte GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configurazione del PIN del LED (PA5) come Output
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // Configurazione del PIN del Pulsante (PC13) come Input
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL; // La Nucleo ha già una resistenza di pull-up esterna su PC13
    HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
}

int main(void) {
    // 1. Abilita il clock sulla porta GPIOA (scrivendo nel registro RCC_AHB1ENR)
    // L'indirizzo del registro RCC_AHB1ENR è 0x40023830. Impostiamo il bit 0 a 1.
    *(volatile unsigned int *)(0x40023830) |= (1 << 0);
    
    // 2. Configura PA5 come output (scrivendo nel registro GPIOA_MODER a 0x40020000)
    // Puliamo i bit 11 e 10, poi impostiamo il bit 10 a 1 (Output Mode)
    *(volatile unsigned int *)(0x40020000) &= ~(3 << 10);
    *(volatile unsigned int *)(0x40020000) |= (1 << 10);

    // 3. Forza il pin PA5 a livello ALTO (scrivendo nel registro GPIOA_ODR a 0x40020014)
    // Impostiamo il bit 5 a 1 per accendere fisicamente il LED.
    *(volatile unsigned int *)(0x40020014) |= (1 << 5);

    while(1) {
        // Loop infinito con il LED forzato acceso staticamente
    }
}

// Configurazione del Clock di sistema (84 MHz come da tuo esempio)
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4; 
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        while(1);
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        while(1);
    }
}

void HAL_Delay(uint32_t Delay) {
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = tickstart + Delay;
    while(HAL_GetTick() < wait);
}
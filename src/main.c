#include "stm32f4xx_hal.h" // Includi la HAL
#include "motor_fsm.h"    // Includi la nostra FSM (la collegheremo dopo)

// Funzione di inizializzazione base (Clock, SysTick)
void SystemClock_Config(void) {
    // Implementazione minima per l'STM32F446RE
    // Questo è un esempio, in un progetto reale andrebbe configurato in dettaglio il Clock.
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
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4; // Esempio: 84 MHz
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        // Errore di configurazione oscillatore
        while(1);
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        // Errore di configurazione clock
        while(1);
    }
}

// Funzione principale che viene chiamata dopo il Reset_Handler
int main(void) {
    // Inizializzazione della HAL e del sistema
    HAL_Init();
    SystemClock_Config();

    // Loop infinito del firmware
    while(1) {
        // Qui la nostra FSM verrà aggiornata
    }
}

// Implementazione della funzione HAL_Delay (richiesta da HAL_Init())
void HAL_Delay(uint32_t Delay) {
    // Utilizza il timer SysTick
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = tickstart + Delay;
    while(HAL_GetTick() < wait);
}
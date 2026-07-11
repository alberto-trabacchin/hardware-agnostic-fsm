#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Include di base per la HAL */
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr.h"

/* Abilita/Disabilita i moduli HAL */
#define HAL_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED       /* <<< Corretto (aggiunto HAL_) */
#define HAL_GPIO_MODULE_ENABLED      /* <<< Corretto (aggiunto HAL_) */
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED       /* <<< Corretto (aggiunto HAL_) */
#define HAL_FLASH_MODULE_ENABLED     /* <<< Corretto (aggiunto HAL_) */
//#define HAL_DMA_MODULE_ENABLED       /* <<< Consigliato per il HAL */

/* ========================================================================== */
/* 1. CONFIGURAZIONE DEI VALORI DEGLI OSCILLATORI                             */
/* ========================================================================== */

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000U) /*!< Valore dell'oscillatore esterno HSE in Hz (8 MHz) */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    ((uint32_t)100U)   /*!< Timeout per l'avvio dell'HSE, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000U) /*!< Valore dell'oscillatore interno HSI in Hz (16 MHz) */
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE)
  #define LSI_VALUE  ((uint32_t)32000U)       /*!< Valore tipico del LSI interno in Hz */
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
  #define LSE_VALUE    ((uint32_t)32768U) /*!< Valore dell'oscillatore esterno LSE in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    ((uint32_t)5000U)   /*!< Timeout per l'avvio del LSE, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

#if !defined  (VDD_VALUE)
  #define VDD_VALUE                            ((uint32_t)3300U) /*!< Valore di VDD in mV (3.3V) */
#endif /* VDD_VALUE */

#if !defined  (TICK_INT_PRIORITY)
  #define TICK_INT_PRIORITY            ((uint32_t)0x0FU) /*!< Priorità dell'interrupt di sistema (SysTick) */
#endif /* TICK_INT_PRIORITY */

#if !defined  (PREFETCH_ENABLE)
  #define PREFETCH_ENABLE              1U
#endif /* PREFETCH_ENABLE */

#if !defined  (INSTRUCTION_CACHE_ENABLE)
  #define INSTRUCTION_CACHE_ENABLE     1U
#endif /* INSTRUCTION_CACHE_ENABLE */

#if !defined  (DATA_CACHE_ENABLE)
  #define DATA_CACHE_ENABLE            1U
#endif /* DATA_CACHE_ENABLE */

#if !defined  (EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    ((uint32_t)12288000U) /*!< Valore del clock audio esterno in Hz */
#endif /* EXTERNAL_CLOCK_VALUE */


/* Configurazioni SysTick */
#define  USE_RTOS                     0
#define  USE_Delay                  1

#ifdef __cplusplus
}
#endif

#ifndef assert_param
#ifdef  USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */
#endif /* assert_param */

#endif /* __STM32F4xx_HAL_CONF_H */
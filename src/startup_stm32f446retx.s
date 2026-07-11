.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* Indirizzi definiti dal linker script stm32f446re.ld */
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  ldr   sp, =_estack    /* Imposta lo Stack Pointer */

/* Copia la sezione .data da Flash a SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Inizializza a zero la sezione .bss in SRAM */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Chiama l'inizializzazione del clock di sistema CMSIS */
  bl  SystemInit
/* Chiama i costruttori statici (se presenti) */
  bl __libc_init_array
/* Salta al main() del tuo programma */
  bl  main

LoopForever:
  b LoopForever

.size Reset_Handler, .-Reset_Handler

/* ----------------------------------------------------------------------------
   Tabella dei Vettori di Interrupt (mappata in Flash all'avvio)
   ---------------------------------------------------------------------------- */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  /* Interrupt Esterni specifici per STM32F446xx */
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word TAMP_STAMP_IRQHandler
  .word RTC_WKUP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMA1_Stream0_IRQHandler
  .word DMA1_Stream1_IRQHandler
  .word DMA1_Stream2_IRQHandler
  .word DMA1_Stream3_IRQHandler
  .word DMA1_Stream4_IRQHandler
  .word DMA1_Stream5_IRQHandler
  .word DMA1_Stream6_IRQHandler
  .word ADC_IRQHandler
  .word CAN1_TX_IRQHandler
  .word CAN1_RX0_IRQHandler
  .word CAN1_RX1_IRQHandler
  .word CAN1_SCE_IRQHandler
  .word EXTI9_5_IRQHandler
  .word TIM1_BRK_TIM9_IRQHandler
  .word TIM1_UP_TIM10_IRQHandler
  .word TIM1_TRG_COM_TIM11_IRQHandler
  .word TIM1_CC_IRQHandler
  .word TIM2_IRQHandler
  .word TIM3_IRQHandler
  .word TIM4_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTC_Alarm_IRQHandler
  .word OTG_FS_WKUP_IRQHandler
  .word TIM8_BRK_TIM12_IRQHandler
  .word TIM8_UP_TIM13_IRQHandler
  .word TIM8_TRG_COM_TIM14_IRQHandler
  .word TIM8_CC_IRQHandler
  .word DMA1_Stream7_IRQHandler
  .word FMC_IRQHandler
  .word SDIO_IRQHandler
  .word TIM5_IRQHandler
  .word SPI3_IRQHandler
  .word UART4_IRQHandler
  .word UART5_IRQHandler
  .word TIM6_DAC_IRQHandler
  .word TIM7_IRQHandler
  .word DMA2_Stream0_IRQHandler
  .word DMA2_Stream1_IRQHandler
  .word DMA2_Stream2_IRQHandler
  .word DMA2_Stream3_IRQHandler
  .word DMA2_Stream4_IRQHandler
  .word 0
  .word 0
  .word CAN2_TX_IRQHandler
  .word CAN2_RX0_IRQHandler
  .word CAN2_RX1_IRQHandler
  .word CAN2_SCE_IRQHandler
  .word OTG_FS_IRQHandler
  .word DMA2_Stream5_IRQHandler
  .word DMA2_Stream6_IRQHandler
  .word DMA2_Stream7_IRQHandler
  .word USART6_IRQHandler
  .word I2C3_EV_IRQHandler
  .word I2C3_ER_IRQHandler
  .word OTG_HS_EP1_OUT_IRQHandler
  .word OTG_HS_EP1_IN_IRQHandler
  .word OTG_HS_WKUP_IRQHandler
  .word OTG_HS_IRQHandler
  .word DCMI_IRQHandler
  .word 0
  .word 0
  .word FPU_IRQHandler
  .word 0
  .word 0
  .word SPI4_IRQHandler
  .word 0
  .word 0
  .word SAI1_IRQHandler
  .word 0
  .word 0
  .word 0
  .word SAI2_IRQHandler
  .word QuadSPI_IRQHandler
  .word HDMI_CEC_IRQHandler
  .word SPDIF_RX_IRQHandler
  .word FMPI2C1_Event_IRQHandler
  .word FMPI2C1_Error_IRQHandler

/* ----------------------------------------------------------------------------
   Definizione dei gestori di interrupt di default (reindirizzati a Default_Handler)
   ---------------------------------------------------------------------------- */
  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
LoopAddr:
  b LoopAddr
  .size Default_Handler, .-Default_Handler

  .macro define_weak_handler name
  .weak \name
  .thumb_set \name, Default_Handler
  .endm

  define_weak_handler NMI_Handler
  define_weak_handler HardFault_Handler
  define_weak_handler MemManage_Handler
  define_weak_handler BusFault_Handler
  define_weak_handler UsageFault_Handler
  define_weak_handler SVC_Handler
  define_weak_handler DebugMon_Handler
  define_weak_handler PendSV_Handler
  define_weak_handler SysTick_Handler
  define_weak_handler WWDG_IRQHandler
  define_weak_handler PVD_IRQHandler
  define_weak_handler TAMP_STAMP_IRQHandler
  define_weak_handler RTC_WKUP_IRQHandler
  define_weak_handler FLASH_IRQHandler
  define_weak_handler RCC_IRQHandler
  define_weak_handler EXTI0_IRQHandler
  define_weak_handler EXTI1_IRQHandler
  define_weak_handler EXTI2_IRQHandler
  define_weak_handler EXTI3_IRQHandler
  define_weak_handler EXTI4_IRQHandler
  define_weak_handler DMA1_Stream0_IRQHandler
  define_weak_handler DMA1_Stream1_IRQHandler
  define_weak_handler DMA1_Stream2_IRQHandler
  define_weak_handler DMA1_Stream3_IRQHandler
  define_weak_handler DMA1_Stream4_IRQHandler
  define_weak_handler DMA1_Stream5_IRQHandler
  define_weak_handler DMA1_Stream6_IRQHandler
  define_weak_handler ADC_IRQHandler
  define_weak_handler CAN1_TX_IRQHandler
  define_weak_handler CAN1_RX0_IRQHandler
  define_weak_handler CAN1_RX1_IRQHandler
  define_weak_handler CAN1_SCE_IRQHandler
  define_weak_handler EXTI9_5_IRQHandler
  define_weak_handler TIM1_BRK_TIM9_IRQHandler
  define_weak_handler TIM1_UP_TIM10_IRQHandler
  define_weak_handler TIM1_TRG_COM_TIM11_IRQHandler
  define_weak_handler TIM1_CC_IRQHandler
  define_weak_handler TIM2_IRQHandler
  define_weak_handler TIM3_IRQHandler
  define_weak_handler TIM4_IRQHandler
  define_weak_handler I2C1_EV_IRQHandler
  define_weak_handler I2C1_ER_IRQHandler
  define_weak_handler I2C2_EV_IRQHandler
  define_weak_handler I2C2_ER_IRQHandler
  define_weak_handler SPI1_IRQHandler
  define_weak_handler SPI2_IRQHandler
  define_weak_handler USART1_IRQHandler
  define_weak_handler USART2_IRQHandler
  define_weak_handler USART3_IRQHandler
  define_weak_handler EXTI15_10_IRQHandler
  define_weak_handler RTC_Alarm_IRQHandler
  define_weak_handler OTG_FS_WKUP_IRQHandler
  define_weak_handler TIM8_BRK_TIM12_IRQHandler
  define_weak_handler TIM8_UP_TIM13_IRQHandler
  define_weak_handler TIM8_TRG_COM_TIM14_IRQHandler
  define_weak_handler TIM8_CC_IRQHandler
  define_weak_handler DMA1_Stream7_IRQHandler
  define_weak_handler FMC_IRQHandler
  define_weak_handler SDIO_IRQHandler
  define_weak_handler TIM5_IRQHandler
  define_weak_handler SPI3_IRQHandler
  define_weak_handler UART4_IRQHandler
  define_weak_handler UART5_IRQHandler
  define_weak_handler TIM6_DAC_IRQHandler
  define_weak_handler TIM7_IRQHandler
  define_weak_handler DMA2_Stream0_IRQHandler
  define_weak_handler DMA2_Stream1_IRQHandler
  define_weak_handler DMA2_Stream2_IRQHandler
  define_weak_handler DMA2_Stream3_IRQHandler
  define_weak_handler DMA2_Stream4_IRQHandler
  define_weak_handler CAN2_TX_IRQHandler
  define_weak_handler CAN2_RX0_IRQHandler
  define_weak_handler CAN2_RX1_IRQHandler
  define_weak_handler CAN2_SCE_IRQHandler
  define_weak_handler OTG_FS_IRQHandler
  define_weak_handler DMA2_Stream5_IRQHandler
  define_weak_handler DMA2_Stream6_IRQHandler
  define_weak_handler DMA2_Stream7_IRQHandler
  define_weak_handler USART6_IRQHandler
  define_weak_handler I2C3_EV_IRQHandler
  define_weak_handler I2C3_ER_IRQHandler
  define_weak_handler OTG_HS_EP1_OUT_IRQHandler
  define_weak_handler OTG_HS_EP1_IN_IRQHandler
  define_weak_handler OTG_HS_WKUP_IRQHandler
  define_weak_handler OTG_HS_IRQHandler
  define_weak_handler DCMI_IRQHandler
  define_weak_handler FPU_IRQHandler
  define_weak_handler SPI4_IRQHandler
  define_weak_handler SAI1_IRQHandler
  define_weak_handler SAI2_IRQHandler
  define_weak_handler QuadSPI_IRQHandler
  define_weak_handler HDMI_CEC_IRQHandler
  define_weak_handler SPDIF_RX_IRQHandler
  define_weak_handler FMPI2C1_Event_IRQHandler
  define_weak_handler FMPI2C1_Error_IRQHandler
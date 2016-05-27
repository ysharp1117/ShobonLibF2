/*
Generating stm32f2xx_io_view.c by gen_io_view.
*/
#include "stm32f2xx.h"

#ifdef SCS_BASE
volatile SCnSCB_Type * const IO_SCnSCB __attribute__ ((section(".ioview"))) = SCnSCB;
#endif
#ifdef SCB_BASE
volatile SCB_Type * const IO_SCB __attribute__ ((section(".ioview"))) = SCB;
#endif
#ifdef SysTick_BASE
volatile SysTick_Type * const IO_SysTick __attribute__ ((section(".ioview"))) = SysTick;
#endif
#ifdef NVIC_BASE
volatile NVIC_Type * const IO_NVIC __attribute__ ((section(".ioview"))) = NVIC;
#endif
#ifdef ITM_BASE
volatile ITM_Type * const IO_ITM __attribute__ ((section(".ioview"))) = ITM;
#endif
#ifdef DWT_BASE
volatile DWT_Type * const IO_DWT __attribute__ ((section(".ioview"))) = DWT;
#endif
#ifdef TPI_BASE
volatile TPI_Type * const IO_TPI __attribute__ ((section(".ioview"))) = TPI;
#endif
#ifdef CoreDebug_BASE
volatile CoreDebug_Type * const IO_CoreDebug __attribute__ ((section(".ioview"))) = CoreDebug;
#endif
#ifdef MPU_BASE
volatile MPU_Type * const IO_MPU __attribute__ ((section(".ioview"))) = MPU;
#endif
#ifdef TIM2_BASE
volatile TIM_TypeDef * const IO_TIM2 __attribute__ ((section(".ioview"))) = TIM2;
#endif
#ifdef TIM3_BASE
volatile TIM_TypeDef * const IO_TIM3 __attribute__ ((section(".ioview"))) = TIM3;
#endif
#ifdef TIM4_BASE
volatile TIM_TypeDef * const IO_TIM4 __attribute__ ((section(".ioview"))) = TIM4;
#endif
#ifdef TIM5_BASE
volatile TIM_TypeDef * const IO_TIM5 __attribute__ ((section(".ioview"))) = TIM5;
#endif
#ifdef TIM6_BASE
volatile TIM_TypeDef * const IO_TIM6 __attribute__ ((section(".ioview"))) = TIM6;
#endif
#ifdef TIM7_BASE
volatile TIM_TypeDef * const IO_TIM7 __attribute__ ((section(".ioview"))) = TIM7;
#endif
#ifdef TIM12_BASE
volatile TIM_TypeDef * const IO_TIM12 __attribute__ ((section(".ioview"))) = TIM12;
#endif
#ifdef TIM13_BASE
volatile TIM_TypeDef * const IO_TIM13 __attribute__ ((section(".ioview"))) = TIM13;
#endif
#ifdef TIM14_BASE
volatile TIM_TypeDef * const IO_TIM14 __attribute__ ((section(".ioview"))) = TIM14;
#endif
#ifdef RTC_BASE
volatile RTC_TypeDef * const IO_RTC __attribute__ ((section(".ioview"))) = RTC;
#endif
#ifdef WWDG_BASE
volatile WWDG_TypeDef * const IO_WWDG __attribute__ ((section(".ioview"))) = WWDG;
#endif
#ifdef IWDG_BASE
volatile IWDG_TypeDef * const IO_IWDG __attribute__ ((section(".ioview"))) = IWDG;
#endif
#ifdef SPI2_BASE
volatile SPI_TypeDef * const IO_SPI2 __attribute__ ((section(".ioview"))) = SPI2;
#endif
#ifdef SPI3_BASE
volatile SPI_TypeDef * const IO_SPI3 __attribute__ ((section(".ioview"))) = SPI3;
#endif
#ifdef USART2_BASE
volatile USART_TypeDef * const IO_USART2 __attribute__ ((section(".ioview"))) = USART2;
#endif
#ifdef USART3_BASE
volatile USART_TypeDef * const IO_USART3 __attribute__ ((section(".ioview"))) = USART3;
#endif
#ifdef UART4_BASE
volatile USART_TypeDef * const IO_UART4 __attribute__ ((section(".ioview"))) = UART4;
#endif
#ifdef UART5_BASE
volatile USART_TypeDef * const IO_UART5 __attribute__ ((section(".ioview"))) = UART5;
#endif
#ifdef I2C1_BASE
volatile I2C_TypeDef * const IO_I2C1 __attribute__ ((section(".ioview"))) = I2C1;
#endif
#ifdef I2C2_BASE
volatile I2C_TypeDef * const IO_I2C2 __attribute__ ((section(".ioview"))) = I2C2;
#endif
#ifdef I2C3_BASE
volatile I2C_TypeDef * const IO_I2C3 __attribute__ ((section(".ioview"))) = I2C3;
#endif
#ifdef CAN1_BASE
volatile CAN_TypeDef * const IO_CAN1 __attribute__ ((section(".ioview"))) = CAN1;
#endif
#ifdef CAN2_BASE
volatile CAN_TypeDef * const IO_CAN2 __attribute__ ((section(".ioview"))) = CAN2;
#endif
#ifdef PWR_BASE
volatile PWR_TypeDef * const IO_PWR __attribute__ ((section(".ioview"))) = PWR;
#endif
#ifdef DAC_BASE
volatile DAC_TypeDef * const IO_DAC __attribute__ ((section(".ioview"))) = DAC;
#endif
#ifdef TIM1_BASE
volatile TIM_TypeDef * const IO_TIM1 __attribute__ ((section(".ioview"))) = TIM1;
#endif
#ifdef TIM8_BASE
volatile TIM_TypeDef * const IO_TIM8 __attribute__ ((section(".ioview"))) = TIM8;
#endif
#ifdef USART1_BASE
volatile USART_TypeDef * const IO_USART1 __attribute__ ((section(".ioview"))) = USART1;
#endif
#ifdef USART6_BASE
volatile USART_TypeDef * const IO_USART6 __attribute__ ((section(".ioview"))) = USART6;
#endif
#ifdef ADC_BASE
volatile ADC_Common_TypeDef * const IO_ADC __attribute__ ((section(".ioview"))) = ADC;
#endif
#ifdef ADC1_BASE
volatile ADC_TypeDef * const IO_ADC1 __attribute__ ((section(".ioview"))) = ADC1;
#endif
#ifdef ADC2_BASE
volatile ADC_TypeDef * const IO_ADC2 __attribute__ ((section(".ioview"))) = ADC2;
#endif
#ifdef ADC3_BASE
volatile ADC_TypeDef * const IO_ADC3 __attribute__ ((section(".ioview"))) = ADC3;
#endif
#ifdef SDIO_BASE
volatile SDIO_TypeDef * const IO_SDIO __attribute__ ((section(".ioview"))) = SDIO;
#endif
#ifdef SPI1_BASE
volatile SPI_TypeDef * const IO_SPI1 __attribute__ ((section(".ioview"))) = SPI1;
#endif
#ifdef SYSCFG_BASE
volatile SYSCFG_TypeDef * const IO_SYSCFG __attribute__ ((section(".ioview"))) = SYSCFG;
#endif
#ifdef EXTI_BASE
volatile EXTI_TypeDef * const IO_EXTI __attribute__ ((section(".ioview"))) = EXTI;
#endif
#ifdef TIM9_BASE
volatile TIM_TypeDef * const IO_TIM9 __attribute__ ((section(".ioview"))) = TIM9;
#endif
#ifdef TIM10_BASE
volatile TIM_TypeDef * const IO_TIM10 __attribute__ ((section(".ioview"))) = TIM10;
#endif
#ifdef TIM11_BASE
volatile TIM_TypeDef * const IO_TIM11 __attribute__ ((section(".ioview"))) = TIM11;
#endif
#ifdef GPIOA_BASE
volatile GPIO_TypeDef * const IO_GPIOA __attribute__ ((section(".ioview"))) = GPIOA;
#endif
#ifdef GPIOB_BASE
volatile GPIO_TypeDef * const IO_GPIOB __attribute__ ((section(".ioview"))) = GPIOB;
#endif
#ifdef GPIOC_BASE
volatile GPIO_TypeDef * const IO_GPIOC __attribute__ ((section(".ioview"))) = GPIOC;
#endif
#ifdef GPIOD_BASE
volatile GPIO_TypeDef * const IO_GPIOD __attribute__ ((section(".ioview"))) = GPIOD;
#endif
#ifdef GPIOE_BASE
volatile GPIO_TypeDef * const IO_GPIOE __attribute__ ((section(".ioview"))) = GPIOE;
#endif
#ifdef GPIOF_BASE
volatile GPIO_TypeDef * const IO_GPIOF __attribute__ ((section(".ioview"))) = GPIOF;
#endif
#ifdef GPIOG_BASE
volatile GPIO_TypeDef * const IO_GPIOG __attribute__ ((section(".ioview"))) = GPIOG;
#endif
#ifdef GPIOH_BASE
volatile GPIO_TypeDef * const IO_GPIOH __attribute__ ((section(".ioview"))) = GPIOH;
#endif
#ifdef GPIOI_BASE
volatile GPIO_TypeDef * const IO_GPIOI __attribute__ ((section(".ioview"))) = GPIOI;
#endif
#ifdef CRC_BASE
volatile CRC_TypeDef * const IO_CRC __attribute__ ((section(".ioview"))) = CRC;
#endif
#ifdef RCC_BASE
volatile RCC_TypeDef * const IO_RCC __attribute__ ((section(".ioview"))) = RCC;
#endif
#ifdef FLASH_R_BASE
volatile FLASH_TypeDef * const IO_FLASH __attribute__ ((section(".ioview"))) = FLASH;
#endif
#ifdef DMA1_BASE
volatile DMA_TypeDef * const IO_DMA1 __attribute__ ((section(".ioview"))) = DMA1;
#endif
#ifdef DMA1_Stream0_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream0 __attribute__ ((section(".ioview"))) = DMA1_Stream0;
#endif
#ifdef DMA1_Stream1_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream1 __attribute__ ((section(".ioview"))) = DMA1_Stream1;
#endif
#ifdef DMA1_Stream2_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream2 __attribute__ ((section(".ioview"))) = DMA1_Stream2;
#endif
#ifdef DMA1_Stream3_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream3 __attribute__ ((section(".ioview"))) = DMA1_Stream3;
#endif
#ifdef DMA1_Stream4_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream4 __attribute__ ((section(".ioview"))) = DMA1_Stream4;
#endif
#ifdef DMA1_Stream5_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream5 __attribute__ ((section(".ioview"))) = DMA1_Stream5;
#endif
#ifdef DMA1_Stream6_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream6 __attribute__ ((section(".ioview"))) = DMA1_Stream6;
#endif
#ifdef DMA1_Stream7_BASE
volatile DMA_Stream_TypeDef * const IO_DMA1_Stream7 __attribute__ ((section(".ioview"))) = DMA1_Stream7;
#endif
#ifdef DMA2_BASE
volatile DMA_TypeDef * const IO_DMA2 __attribute__ ((section(".ioview"))) = DMA2;
#endif
#ifdef DMA2_Stream0_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream0 __attribute__ ((section(".ioview"))) = DMA2_Stream0;
#endif
#ifdef DMA2_Stream1_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream1 __attribute__ ((section(".ioview"))) = DMA2_Stream1;
#endif
#ifdef DMA2_Stream2_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream2 __attribute__ ((section(".ioview"))) = DMA2_Stream2;
#endif
#ifdef DMA2_Stream3_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream3 __attribute__ ((section(".ioview"))) = DMA2_Stream3;
#endif
#ifdef DMA2_Stream4_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream4 __attribute__ ((section(".ioview"))) = DMA2_Stream4;
#endif
#ifdef DMA2_Stream5_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream5 __attribute__ ((section(".ioview"))) = DMA2_Stream5;
#endif
#ifdef DMA2_Stream6_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream6 __attribute__ ((section(".ioview"))) = DMA2_Stream6;
#endif
#ifdef DMA2_Stream7_BASE
volatile DMA_Stream_TypeDef * const IO_DMA2_Stream7 __attribute__ ((section(".ioview"))) = DMA2_Stream7;
#endif
#ifdef ETH_BASE
volatile ETH_TypeDef * const IO_ETH __attribute__ ((section(".ioview"))) = ETH;
#endif
#ifdef DCMI_BASE
volatile DCMI_TypeDef * const IO_DCMI __attribute__ ((section(".ioview"))) = DCMI;
#endif
#ifdef CRYP_BASE
volatile CRYP_TypeDef * const IO_CRYP __attribute__ ((section(".ioview"))) = CRYP;
#endif
#ifdef HASH_BASE
volatile HASH_TypeDef * const IO_HASH __attribute__ ((section(".ioview"))) = HASH;
#endif
#ifdef HASH_DIGEST_BASE
volatile HASH_DIGEST_TypeDef * const IO_HASH_DIGEST __attribute__ ((section(".ioview"))) = HASH_DIGEST;
#endif
#ifdef RNG_BASE
volatile RNG_TypeDef * const IO_RNG __attribute__ ((section(".ioview"))) = RNG;
#endif
#ifdef FSMC_Bank1_R_BASE
volatile FSMC_Bank1_TypeDef * const IO_FSMC_Bank1 __attribute__ ((section(".ioview"))) = FSMC_Bank1;
#endif
#ifdef FSMC_Bank1E_R_BASE
volatile FSMC_Bank1E_TypeDef * const IO_FSMC_Bank1E __attribute__ ((section(".ioview"))) = FSMC_Bank1E;
#endif
#ifdef FSMC_Bank2_3_R_BASE
volatile FSMC_Bank2_3_TypeDef * const IO_FSMC_Bank2_3 __attribute__ ((section(".ioview"))) = FSMC_Bank2_3;
#endif
#ifdef FSMC_Bank4_R_BASE
volatile FSMC_Bank4_TypeDef * const IO_FSMC_Bank4 __attribute__ ((section(".ioview"))) = FSMC_Bank4;
#endif
#ifdef DBGMCU_BASE
volatile DBGMCU_TypeDef * const IO_DBGMCU __attribute__ ((section(".ioview"))) = DBGMCU;
#endif
#ifdef USB_OTG_FS_PERIPH_BASE
volatile USB_OTG_GlobalTypeDef * const IO_USB_OTG_FS __attribute__ ((section(".ioview"))) = USB_OTG_FS;
#endif
#ifdef USB_OTG_HS_PERIPH_BASE
volatile USB_OTG_GlobalTypeDef * const IO_USB_OTG_HS __attribute__ ((section(".ioview"))) = USB_OTG_HS;
#endif

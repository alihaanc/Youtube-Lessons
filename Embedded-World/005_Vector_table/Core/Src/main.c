/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct __attribute__((aligned(512), packed)) __vectable_t{

	/*****  Cortex-M Processor Exceptions Numbers *****************************************************************/

	uint32_t _estcak;
	uint32_t Reset_Handler;
	uint32_t NMI_Handler;			 /*!< 2 Non Maskable Interrupt  */
	uint32_t HardFault_Handler; 	/*!< 3 Cortex-M Hard Fault Interrupt*/
	uint32_t MemManage_Handler; 	/*!< 4 Cortex-M Memory Management Interrupt  */
	uint32_t BusFault_Handler; 		/*!< 5 Cortex-M Bus Fault Interrupt*/
	uint32_t UsageFault_Handler; 	/*!< 6 Cortex-M Usage Fault Interrupt */
	uint32_t reserved_1;
	uint32_t reserved_2;
	uint32_t reserved_3;
	uint32_t reserved_4;
	uint32_t SVC_Handler; 			/*!< 11 Cortex-M SV Call Interrupt */
	uint32_t DebugMon_Handler; 		/*!< 12 Cortex-M Debug Monitor Interrupt*/
	uint32_t reserved_5;
	uint32_t PendSV_Handler; 		/*!< 14 Cortex-M Pend SV Interrupt*/
	uint32_t SysTick_Handler; 		/*!< 15 Cortex-M System Tick Interrupt  */

	/******  STM32 specific Interrupt Numbers **********************************************************************/

	  uint32_t     WWDG_IRQHandler    ;                /* Window WatchDog              */
	  uint32_t     PVD_AVD_IRQHandler  ;               /* PVD/AVD through EXTI Line detection */
	  uint32_t     TAMP_STAMP_IRQHandler ;             /* Tamper and TimeStamps through the EXTI line */
	  uint32_t     RTC_WKUP_IRQHandler;                /* RTC Wakeup through the EXTI line */
	  uint32_t     FLASH_IRQHandler;                   /* FLASH                        */
	  uint32_t     RCC_IRQHandler   ;                  /* RCC                          */
	  uint32_t     EXTI0_IRQHandler ;                  /* EXTI Line0                   */
	  uint32_t     EXTI1_IRQHandler ;                  /* EXTI Line1                   */
	  uint32_t     EXTI2_IRQHandler  ;                 /* EXTI Line2                   */
	  uint32_t     EXTI3_IRQHandler ;                  /* EXTI Line3                   */
	  uint32_t     EXTI4_IRQHandler ;                  /* EXTI Line4                   */
	  uint32_t     DMA1_Stream0_IRQHandler ;           /* DMA1 Stream 0                */
	  uint32_t     DMA1_Stream1_IRQHandler ;           /* DMA1 Stream 1                */
	  uint32_t     DMA1_Stream2_IRQHandler ;           /* DMA1 Stream 2                */
	  uint32_t     DMA1_Stream3_IRQHandler ;           /* DMA1 Stream 3                */
	  uint32_t     DMA1_Stream4_IRQHandler ;           /* DMA1 Stream 4                */
	  uint32_t     DMA1_Stream5_IRQHandler;            /* DMA1 Stream 5                */
	  uint32_t     DMA1_Stream6_IRQHandler;            /* DMA1 Stream 6                */
	  uint32_t     ADC_IRQHandler  ;                   /* ADC1, ADC2 and ADC3s         */
	  uint32_t     FDCAN1_IT0_IRQHandler ;             /* FDCAN1 interrupt line 0      */
	  uint32_t     FDCAN2_IT0_IRQHandler ;             /* FDCAN2 interrupt line 0      */
	  uint32_t     FDCAN1_IT1_IRQHandler ;             /* FDCAN1 interrupt line 1      */
	  uint32_t     FDCAN2_IT1_IRQHandler ;             /* FDCAN2 interrupt line 1      */
	  uint32_t     EXTI9_5_IRQHandler  ;               /* External Line[9:5]s          */
	  uint32_t     TIM1_BRK_IRQHandler ;               /* TIM1 Break interrupt         */
	  uint32_t     TIM1_UP_IRQHandler ;                /* TIM1 Update interrupt        */
	  uint32_t     TIM1_TRG_COM_IRQHandler;            /* TIM1 Trigger and Commutation interrupt */
	  uint32_t     TIM1_CC_IRQHandler  ;               /* TIM1 Capture Compare         */
	  uint32_t     TIM2_IRQHandler  ;                  /* TIM2                         */
	  uint32_t     TIM3_IRQHandler  ;                  /* TIM3                         */
	  uint32_t     TIM4_IRQHandler ;                   /* TIM4                         */
	  uint32_t     I2C1_EV_IRQHandler ;                /* I2C1 Event                   */
	  uint32_t     I2C1_ER_IRQHandler ;                /* I2C1 Error                   */
	  uint32_t     I2C2_EV_IRQHandler ;                /* I2C2 Event                   */
	  uint32_t     I2C2_ER_IRQHandler ;                /* I2C2 Error                   */
	  uint32_t     SPI1_IRQHandler   ;                 /* SPI1                         */
	  uint32_t     SPI2_IRQHandler  ;                  /* SPI2                         */
	  uint32_t     USART1_IRQHandler ;                 /* USART1                       */
	  uint32_t     USART2_IRQHandler ;                 /* USART2                       */
	  uint32_t     USART3_IRQHandler  ;                /* USART3                       */
	  uint32_t     EXTI15_10_IRQHandler;               /* External Line[15:10]s        */
	  uint32_t     RTC_Alarm_IRQHandler  ;             /* RTC Alarm (A and B) through EXTI Line */
	  uint32_t     reserved_6            ;          /* Reserved                     */
	  uint32_t     TIM8_BRK_TIM12_IRQHandler  ;        /* TIM8 Break and TIM12         */
	  uint32_t     TIM8_UP_TIM13_IRQHandler ;          /* TIM8 Update and TIM13        */
	  uint32_t     TIM8_TRG_COM_TIM14_IRQHandler ;     /* TIM8 Trigger and Commutation and TIM14 */
	  uint32_t     TIM8_CC_IRQHandler    ;             /* TIM8 Capture Compare         */
	  uint32_t     DMA1_Stream7_IRQHandler;            /* DMA1 Stream7                 */
	  uint32_t     FMC_IRQHandler    ;                 /* FMC                          */
	  uint32_t     SDMMC1_IRQHandler ;                 /* SDMMC1                       */
	  uint32_t     TIM5_IRQHandler  ;                  /* TIM5                         */
	  uint32_t     SPI3_IRQHandler  ;                  /* SPI3                         */
	  uint32_t     UART4_IRQHandler ;                  /* UART4                        */
	  uint32_t     UART5_IRQHandler ;                  /* UART5                        */
	  uint32_t     TIM6_DAC_IRQHandler;               /* TIM6 and DAC1&2 underrun errors */
	  uint32_t     TIM7_IRQHandler      ;              /* TIM7                         */
	  uint32_t     DMA2_Stream0_IRQHandler ;          /* DMA2 Stream 0                */
	  uint32_t     DMA2_Stream1_IRQHandler ;           /* DMA2 Stream 1                */
	  uint32_t     DMA2_Stream2_IRQHandler ;           /* DMA2 Stream 2                */
	  uint32_t     DMA2_Stream3_IRQHandler   ;         /* DMA2 Stream 3                */
	  uint32_t     DMA2_Stream4_IRQHandler ;           /* DMA2 Stream 4                */
	  uint32_t     ETH_IRQHandler     ;                /* Ethernet                     */
	  uint32_t     ETH_WKUP_IRQHandler  ;              /* Ethernet Wakeup through EXTI line */
	  uint32_t     FDCAN_CAL_IRQHandler ;              /* FDCAN calibration unit interrupt*/
	  uint32_t     reserved_7     ;                             /* Reserved                     */
	  uint32_t     reserved_8   ;                               /* Reserved                     */
	  uint32_t     reserved_9   ;                              /* Reserved                     */
	  uint32_t     reserved_10    ;                              /* Reserved                     */
	  uint32_t     DMA2_Stream5_IRQHandler  ;          /* DMA2 Stream 5                */
	  uint32_t     DMA2_Stream6_IRQHandler ;           /* DMA2 Stream 6                */
	  uint32_t     DMA2_Stream7_IRQHandler   ;         /* DMA2 Stream 7                */
	  uint32_t     USART6_IRQHandler   ;               /* USART6                       */
	  uint32_t     I2C3_EV_IRQHandler ;                /* I2C3 event                   */
	  uint32_t     I2C3_ER_IRQHandler ;                /* I2C3 error                   */
	  uint32_t     OTG_HS_EP1_OUT_IRQHandler   ;       /* USB OTG HS End Point 1 Out   */
	  uint32_t     OTG_HS_EP1_IN_IRQHandler  ;         /* USB OTG HS End Point 1 In    */
	  uint32_t     OTG_HS_WKUP_IRQHandler   ;          /* USB OTG HS Wakeup through EXTI */
	  uint32_t     OTG_HS_IRQHandler    ;              /* USB OTG HS                   */
	  uint32_t     DCMI_PSSI_IRQHandler ;              /* DCMI, PSSI                   */
	  uint32_t     reserved_11     ;                             /* Reserved                     */
	  uint32_t     RNG_IRQHandler   ;                  /* Rng                          */
	  uint32_t     FPU_IRQHandler  ;                   /* FPU                          */
	  uint32_t     UART7_IRQHandler ;                  /* UART7                        */
	  uint32_t     UART8_IRQHandler ;                  /* UART8                        */
	  uint32_t     SPI4_IRQHandler ;                   /* SPI4                         */
	  uint32_t     SPI5_IRQHandler ;                   /* SPI5                         */
	  uint32_t     SPI6_IRQHandler  ;                  /* SPI6                         */
	  uint32_t     SAI1_IRQHandler ;                   /* SAI1                         */
	  uint32_t     LTDC_IRQHandler  ;                  /* LTDC                         */
	  uint32_t     LTDC_ER_IRQHandler;                 /* LTDC error                   */
	  uint32_t     DMA2D_IRQHandler  ;                 /* DMA2D                        */
	  uint32_t     reserved_12       ;                           /* Reserved                     */
	  uint32_t     OCTOSPI1_IRQHandler;                /* OCTOSPI1                     */
	  uint32_t     LPTIM1_IRQHandler;                  /* LPTIM1                       */
	  uint32_t     CEC_IRQHandler  ;                   /* HDMI_CEC                     */
	  uint32_t     I2C4_EV_IRQHandler;                /* I2C4 Event                   */
	  uint32_t     I2C4_ER_IRQHandler;                 /* I2C4 Error                   */
	  uint32_t     SPDIF_RX_IRQHandler   ;             /* SPDIF_RX                     */
	  uint32_t     reserved_13              ;                     /* Reserved                     */
	  uint32_t     reserved_14            ;                       /* Reserved                     */
	  uint32_t     reserved_15             ;                      /* Reserved                     */
	  uint32_t     reserved_16               ;                    /* Reserved                     */
	  uint32_t     DMAMUX1_OVR_IRQHandler  ;           /* DMAMUX1 Overrun interrupt    */
	  uint32_t     reserved_17            ;                       /* Reserved                     */
	  uint32_t     reserved_18            ;                       /* Reserved                     */
	  uint32_t     reserved_19             ;                      /* Reserved                     */
	  uint32_t     reserved_20             ;                      /* Reserved                     */
	  uint32_t     reserved_21            ;                       /* Reserved                     */
	  uint32_t     reserved_22            ;                       /* Reserved                     */
	  uint32_t     reserved_23            ;                       /* Reserved                     */
	  uint32_t     DFSDM1_FLT0_IRQHandler   ;          /* DFSDM Filter0 Interrupt      */
	  uint32_t     DFSDM1_FLT1_IRQHandler  ;           /* DFSDM Filter1 Interrupt      */
	  uint32_t     DFSDM1_FLT2_IRQHandler  ;           /* DFSDM Filter2 Interrupt      */
	  uint32_t     DFSDM1_FLT3_IRQHandler   ;          /* DFSDM Filter3 Interrupt      */
	  uint32_t     reserved_24                 ;                 /* Reserved                     */
	  uint32_t     SWPMI1_IRQHandler   ;               /* Serial Wire Interface 1 global interrupt */
	  uint32_t     TIM15_IRQHandler  ;                 /* TIM15 global Interrupt          */
	  uint32_t     TIM16_IRQHandler  ;                 /* TIM16 global Interrupt          */
	  uint32_t     TIM17_IRQHandler  ;                 /* TIM17 global Interrupt          */
	  uint32_t     MDIOS_WKUP_IRQHandler ;             /* MDIOS Wakeup  Interrupt         */
	  uint32_t     MDIOS_IRQHandler   ;                /* MDIOS global Interrupt          */
	  uint32_t     reserved_25             ;                     /* Reserved                        */
	  uint32_t     MDMA_IRQHandler   ;                 /* MDMA global Interrupt           */
	  uint32_t     reserved_26         ;                         /* Reserved                        */
	  uint32_t     SDMMC2_IRQHandler ;                 /* SDMMC2 global Interrupt         */
	  uint32_t     HSEM1_IRQHandler ;                  /* HSEM1 global Interrupt          */
	  uint32_t     reserved_27             ;                     /* Reserved                        */
	  uint32_t     ADC3_IRQHandler    ;                /* ADC3 global Interrupt           */
	  uint32_t     DMAMUX2_OVR_IRQHandler;            /* DMAMUX Overrun interrupt        */
	  uint32_t     BDMA_Channel0_IRQHandler;           /* BDMA Channel 0 global Interrupt */
	  uint32_t     BDMA_Channel1_IRQHandler ;          /* BDMA Channel 1 global Interrupt */
	  uint32_t     BDMA_Channel2_IRQHandler ;          /* BDMA Channel 2 global Interrupt */
	  uint32_t     BDMA_Channel3_IRQHandler ;          /* BDMA Channel 3 global Interrupt */
	  uint32_t     BDMA_Channel4_IRQHandler ;          /* BDMA Channel 4 global Interrupt */
	  uint32_t     BDMA_Channel5_IRQHandler ;          /* BDMA Channel 5 global Interrupt */
	  uint32_t     BDMA_Channel6_IRQHandler  ;         /* BDMA Channel 6 global Interrupt */
	  uint32_t     BDMA_Channel7_IRQHandler   ;        /* BDMA Channel 7 global Interrupt */
	  uint32_t     COMP1_IRQHandler  ;                 /* COMP1 global Interrupt          */
	  uint32_t     LPTIM2_IRQHandler ;                 /* LP TIM2 global interrupt        */
	  uint32_t     LPTIM3_IRQHandler ;                 /* LP TIM3 global interrupt        */
	  uint32_t     LPTIM4_IRQHandler ;                 /* LP TIM4 global interrupt        */
	  uint32_t     LPTIM5_IRQHandler ;                 /* LP TIM5 global interrupt        */
	  uint32_t     LPUART1_IRQHandler ;                /* LP UART1 interrupt              */
	  uint32_t     reserved_28      ;                            /* Reserved                        */
	  uint32_t     CRS_IRQHandler ;                    /* Clock Recovery Global Interrupt */
	  uint32_t     ECC_IRQHandler ;                    /* ECC diagnostic Global Interrupt */
	  uint32_t     SAI4_IRQHandler ;                   /* SAI4 global interrupt           */
	  uint32_t     DTS_IRQHandler  ;                   /* Digital Temperature Sensor  interrupt */
	  uint32_t     reserved_29     ;                             /* Reserved                              */
	  uint32_t     WAKEUP_PIN_IRQHandler  ;            /* Interrupt for all 6 wake-up pins      */
	  uint32_t     OCTOSPI2_IRQHandler  ;              /* OCTOSPI2 Interrupt       */
	  uint32_t     reserved_30               ;                   /* Reserved                 */
	  uint32_t     reserved_31             ;                     /* Reserved                 */
	  uint32_t     FMAC_IRQHandler   ;                 /* FMAC Interrupt           */
	  uint32_t     CORDIC_IRQHandler;                  /* CORDIC Interrupt         */
	  uint32_t     UART9_IRQHandler;                   /* UART9 Interrupt          */
	  uint32_t     USART10_IRQHandler;                 /* UART10 Interrupt         */
	  uint32_t     I2C5_EV_IRQHandler ;                /* I2C5 Event Interrupt     */
	  uint32_t     I2C5_ER_IRQHandler  ;               /* I2C5 Error Interrupt     */
	  uint32_t     FDCAN3_IT0_IRQHandler ;             /* FDCAN3 interrupt line 0  */
	  uint32_t     FDCAN3_IT1_IRQHandler ;             /* FDCAN3 interrupt line 1  */
	  uint32_t     TIM23_IRQHandler  ;                 /* TIM23 global interrupt   */
	  uint32_t     TIM24_IRQHandler     ;              /* TIM24 global interrupt   */


}vectable_t;
__attribute__((section(".dtcm_vectable"))) __IO  vectable_t ram_table;



uint32_t custom_uwTick = 0;
 volatile __attribute__((aligned(4))) void custom_handler(void){

	 custom_uwTick ++;
}


 void set_systic_handler(void){

   memcpy((void*)&ram_table, (void*)0x08000000, sizeof(ram_table));

   SCB->VTOR = (uint32_t)&ram_table;
   __DSB();
   __ISB();


   ram_table.SysTick_Handler  = (uint32_t) custom_handler;
   __NOP();
 }
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	set_systic_handler();


  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 34;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 3072;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

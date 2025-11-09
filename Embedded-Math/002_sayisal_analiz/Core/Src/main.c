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
#include "math.h"

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
//Fizik sabitleri
#define G 9.81

// Başlangıç parametreleri
double v0 = 50.0;      // ilk hız (m/s)
double theta_deg = 75.0; // atış açısı (derece)
double y0x =10.00000;         // ilk yükseklik (m)

double to_radian(double deg) {
    return deg * M_PI / 180.0;
}

// Yükseklik fonksiyonu
double f(double t) {
    double theta = to_radian(theta_deg);
    return y0x + v0 * sin(theta) * t - 0.5 * G * t * t;
}

// Bisection Method with relative error
double bisection(double a, double b, double tol, int max_iter) {
    double c_old = 0.0, c_new = 0.0;
    double rel_error = 1.0;
    int iter = 0;

    if (f(a) * f(b) >= 0) {
        printf("Hata: f(a) ve f(b) zıt işaretli olmalı.\r\n");
        return 0.0;
    }

    while (rel_error > tol && iter < max_iter) {
        c_new = (a + b) / 2.0;

        if (iter > 0)
            rel_error = fabs((c_new - c_old) / c_new);

        if (f(c_new) == 0.0)
            break;

        if (f(a) * f(c_new) < 0)
            b = c_new;
        else
            a = c_new;

        c_old = c_new;
        iter++;
    }

    printf("Iterasyon: %d, Bagil Hata: %.8f\r\n", iter, rel_error);
    return c_new;
}




#define G 9.81

typedef struct {
    double x;
    double y;
    double vx;
    double vy;
} State;

// dx/dt
double dx_dt(State s) { return s.vx; }
// dy/dt
double dy_dt(State s) { return s.vy; }
// dvx/dt
double dvx_dt(State s) { return 0.0; }
// dvy/dt
double dvy_dt(State s) { return -G; }

int denemeRunge(void) {

    double dt = 0.01;        // zaman adımı
    int max_steps = 100000;

    double theta = theta_deg * M_PI / 180.0;

    State s;
    s.x = 0.0;
    s.y = y0x;
    s.vx = v0 * cosf(theta);
    s.vy = v0 * sinf(theta);

    int step = 0;

    while (s.y > 0 && step < max_steps) {
        State k1, k2, k3, k4, s_temp;

        // k1
        k1.x  = dx_dt(s);
        k1.y  = dy_dt(s);
        k1.vx = dvx_dt(s);
        k1.vy = dvy_dt(s);

        // k2
        s_temp.x  = s.x  + 0.5 * dt * k1.x;
        s_temp.y  = s.y  + 0.5 * dt * k1.y;
        s_temp.vx = s.vx + 0.5 * dt * k1.vx;
        s_temp.vy = s.vy + 0.5 * dt * k1.vy;

        k2.x  = dx_dt(s_temp);
        k2.y  = dy_dt(s_temp);
        k2.vx = dvx_dt(s_temp);
        k2.vy = dvy_dt(s_temp);

        // k3
        s_temp.x  = s.x  + 0.5 * dt * k2.x;
        s_temp.y  = s.y  + 0.5 * dt * k2.y;
        s_temp.vx = s.vx + 0.5 * dt * k2.vx;
        s_temp.vy = s.vy + 0.5 * dt * k2.vy;

        k3.x  = dx_dt(s_temp);
        k3.y  = dy_dt(s_temp);
        k3.vx = dvx_dt(s_temp);
        k3.vy = dvy_dt(s_temp);

        // k4
        s_temp.x  = s.x  + dt * k3.x;
        s_temp.y  = s.y  + dt * k3.y;
        s_temp.vx = s.vx + dt * k3.vx;
        s_temp.vy = s.vy + dt * k3.vy;

        k4.x  = dx_dt(s_temp);
        k4.y  = dy_dt(s_temp);
        k4.vx = dvx_dt(s_temp);
        k4.vy = dvy_dt(s_temp);

        // RK4
        s.x  += dt/6.0 * (k1.x + 2*k2.x + 2*k3.x + k4.x);
        s.y  += dt/6.0 * (k1.y + 2*k2.y + 2*k3.y + k4.y);
        s.vx += dt/6.0 * (k1.vx + 2*k2.vx + 2*k3.vx + k4.vx);
        s.vy += dt/6.0 * (k1.vy + 2*k2.vy + 2*k3.vy + k4.vy);

        step++;
    }

    printf("iterasyon: %d s\r\n", step);
    printf("Dusme sures: %.6f s\r\n", dt*step);
    printf("Dusme mesafesi: %.6f m\r\n", s.x);

return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  double t_dusme = bisection(0.0,400, 1e-6, 100); // 0-5 saniye aralığında ara
  double theta = to_radian(theta_deg);

  double x_dusme = v0 * cos(theta) * t_dusme; // menzil
  printf("\r\n--- EGIK ATIS SONUCLARI ---\r\n");
  printf("\r\n--- Biscetion SONUCLARI ---\r\n");
  printf("\r\nDusme suresi: %.6f s\r\n", t_dusme);
  printf("\r\nDusme mesafesi: %.6f m\r\n", x_dusme);

  printf("\n--- Runge ---\n");
  denemeRunge();

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

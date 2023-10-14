/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "software_timer.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
    const int MAX_LED_MATRIX = 8;
    uint8_t index_led_matrix = 0;
    uint8_t shift = 0;
    uint8_t matrix_buffer[8] = {0xE7, 0xC3, 0x99, 0x99, 0x81, 0x81, 0x99, 0x99};
  /*
   1 1 1 0 0 1 1 1 -> 0xE7
   1 1 0 0 0 0 1 1 -> 0xC3
   1 0 0 1 1 0 0 1 -> 0x99
   1 0 0 1 1 0 0 1 -> 0x99
   1 0 0 0 0 0 0 1 -> 0x81
   1 0 0 0 0 0 0 1 -> 0X81
   1 0 0 1 1 0 0 1 -> 0x99
   1 0 0 1 1 0 0 1 -> 0x99
   */
    void clearMatrix(){
  	  HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, SET);
  	  HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, SET);
  	  HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, SET);
  	  HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, SET);
  	  HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, SET);
  	  HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, SET);
  	  HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, SET);
  	  HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, SET);
    }
    void setCol(uint8_t value){
  	  HAL_GPIO_WritePin(EMM0_GPIO_Port, EMM0_Pin, (value >> 7) & 1);
  	  HAL_GPIO_WritePin(EMM1_GPIO_Port, EMM1_Pin, (value >> 6) & 1);
  	  HAL_GPIO_WritePin(EMM2_GPIO_Port, EMM2_Pin, (value >> 5) & 1);
  	  HAL_GPIO_WritePin(EMM3_GPIO_Port, EMM3_Pin, (value >> 4) & 1);
  	  HAL_GPIO_WritePin(EMM4_GPIO_Port, EMM4_Pin, (value >> 3) & 1);
  	  HAL_GPIO_WritePin(EMM5_GPIO_Port, EMM5_Pin, (value >> 2) & 1);
  	  HAL_GPIO_WritePin(EMM6_GPIO_Port, EMM6_Pin, (value >> 1) & 1);
  	  HAL_GPIO_WritePin(EMM7_GPIO_Port, EMM7_Pin, (value >> 0) & 1);
    }
    void updateLEDMatrix (uint8_t index, uint8_t shift){
  	  clearMatrix();
  	uint8_t matrix_buffer_shift = (matrix_buffer[index] << shift) | ( matrix_buffer[index] >> (8-shift));
  	  switch (index){
  		case 0:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, RESET);
  			break ;
  		case 1:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, RESET);
  			break;
  		case 2:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, RESET);
  			break ;
  		case 3:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, RESET);
  			break ;
  		case 4:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, RESET);
  			break ;
  		case 5:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, RESET);
  			break ;
  		case 6:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, RESET);
  			break ;
  		case 7:
  			setCol(matrix_buffer_shift);
  			HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, RESET);
  			break ;
  		default :
  			break ;
  	}
  }


    setTimer(1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(timer_flag== 1){
	  	  updateLEDMatrix(index_led_matrix, shift);
	  	  index_led_matrix++;
	  	  if(index_led_matrix >= MAX_LED_MATRIX){
	  		  index_led_matrix = 0;
	  		  shift++;
	  		  if(shift >= 8){
	  			  shift = 0;
	  		  }
	  	  }
	  	  setTimer(5);
	    }

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 799;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EMM0_Pin|EMM1_Pin|DOT_Pin|GPIO_PIN_5
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |EMM2_Pin|EMM3_Pin|EMM4_Pin|EMM5_Pin
                          |EMM6_Pin|EMM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EMM0_Pin EMM1_Pin DOT_Pin PA5
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           EMM2_Pin EMM3_Pin EMM4_Pin EMM5_Pin
                           EMM6_Pin EMM7_Pin */
  GPIO_InitStruct.Pin = EMM0_Pin|EMM1_Pin|DOT_Pin|GPIO_PIN_5
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |EMM2_Pin|EMM3_Pin|EMM4_Pin|EMM5_Pin
                          |EMM6_Pin|EMM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timerRun();
}
/* USER CODE END 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

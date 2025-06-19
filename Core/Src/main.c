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
#include "mb.h"
#include "mbport.h"
#include "mt_port.h"
#include "mbdata.h"
#include "inertia_math.h"
#include "sensors.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DATA_UPD_TIME 50U // in ms
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern module_ctrl_t Data;
extern sensors_ctrl_t sensors_data;

uint8_t captured_pos = 0x00;
float init_elev = 0.0f;
float init_yaw = 0.0f;

uint32_t data_upd_time_prev = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
uint8_t capture_init_pos(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t capture_init_pos(void) {
	uint8_t err = 0x00;
	err = lsm6dsox_read_acc();
	Data.acc_raw[0] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[0]);
	Data.acc_raw[1] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[1]);
	Data.acc_raw[2] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[2]);
	err = lsm6dsox_read_gyro();
	Data.gyro_raw[0] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[0]);
	Data.gyro_raw[1] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[1]);
	Data.gyro_raw[2] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[2]);
	/*err = lis3mdl_read_mag();
	 Data.mag_raw[0] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[0]);
	 Data.mag_raw[1] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[1]);
	 Data.mag_raw[2] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[2]);*/
	if (!err) {
		init_elev = calc_elev_angle(&Data);
		//init_yaw = calc_yaw_angle(&Data);
	}
	return err;
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

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
	MX_I2C2_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOA, 0, GPIO_PIN_SET); /* Driver HARDSTOP connected to GND */

	MT_PORT_SetTimerModule(&htim3);
	MT_PORT_SetUartModule(&huart2);
	mb_data_init();

	uint8_t err = lsm6dsox_init();
	err = lis3mdl_init();

	eMBErrorCode eStatus;
	eStatus = eMBInit(MB_RTU, 0x0A, 0, 115200, MB_PAR_NONE);
	eStatus = eMBEnable();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		eMBPoll();
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		switch (Data.mode) {
		case 0xFFFF:
			captured_pos = 0x00;
			break;
		case 0x0001:
			if (HAL_GetTick() - data_upd_time_prev > DATA_UPD_TIME) {
				err = lsm6dsox_read_acc();
				Data.acc_raw[0] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[0]);
				Data.acc_raw[1] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[1]);
				Data.acc_raw[2] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[2]);
				err = lsm6dsox_read_gyro();
				Data.gyro_raw[0] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[0]);
				Data.gyro_raw[1] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[1]);
				Data.gyro_raw[2] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[2]);
				/*err = lis3mdl_read_mag();
				 Data.mag_raw[0] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[0]);
				 Data.mag_raw[1] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[1]);
				 Data.mag_raw[2] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[2]);*/
				Data.status = err;
				data_upd_time_prev = HAL_GetTick();
			}
			break;
		case 0x0002:
			if (!captured_pos) {
				if (capture_init_pos() == 0) {
					captured_pos = 0x01;
				} else {
					Data.mode = 0xFFFF;
					break;
				}
			}
			if (HAL_GetTick() - data_upd_time_prev > DATA_UPD_TIME) {
				err = lsm6dsox_read_acc();
				Data.acc_raw[0] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[0]);
				Data.acc_raw[1] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[1]);
				Data.acc_raw[2] = lsm6dsox_from_fs2_to_mg(sensors_data.acc_data_raw[2]);
				err = lsm6dsox_read_gyro();
				Data.gyro_raw[0] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[0]);
				Data.gyro_raw[1] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[1]);
				Data.gyro_raw[2] = lsm6dsox_from_fs125_to_mdps(sensors_data.gyro_data_raw[2]);
				/*err = lis3mdl_read_mag();
				 Data.mag_raw[0] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[0]);
				 Data.mag_raw[1] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[1]);
				 Data.mag_raw[2] = lis3mdl_from_fs4_to_gauss(sensors_data.mag_data_raw[2]);*/
				Data.status = err;
				Data.elev_angle = calc_elev_angle(&Data);
				Data.elev_angle_d = Data.elev_angle - init_elev;
				//Data.yaw_angle = calc_yaw_angle(&Data);
				//Data.yaw_angle_d = Data.yaw_angle - init_yaw;
				data_upd_time_prev = HAL_GetTick();
			}
			break;
		default:
			Data.mode = 0xFFFF;
			break;
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void) {

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	hi2c2.Init.Timing = 0x00303D5B;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
		Error_Handler();
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C2_Init 2 */

	/* USER CODE END I2C2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 15;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 50;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_RS485Ex_Init(&huart2, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

	/*Configure GPIO pin : PA0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PA8 */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
eMBErrorCode eMBRegInputCB(UCHAR *pucRegBuffer, USHORT usAddress,
		USHORT usNRegs) {
	return MB_ENOREG;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBRegHoldingCB(UCHAR *pucRegBuffer, USHORT usAddress,
		USHORT usNRegs, eMBRegisterMode eMode) {
	eMBErrorCode eStatus = MB_ENOERR;
	if (eMode == MB_REG_WRITE) {
		int iRegIndex;
		if ((usAddress >= REG_INPUT_START)
				&& (usAddress + usNRegs <= REG_INPUT_NREGS + 1)) {
			iRegIndex = (int) (usAddress - 1);
			memcpy((unsigned char*) &Data + iRegIndex * 2, pucRegBuffer,
					usNRegs * 2);
		} else {
			eStatus = MB_ENOREG;
		}
	} else if (eMode == MB_REG_READ) {
		int iRegIndex;
		if ((usAddress >= REG_INPUT_START)
				&& (usAddress + usNRegs <= REG_INPUT_NREGS + 1)) {
			iRegIndex = (int) (usAddress - 1);
			memcpy(pucRegBuffer, (unsigned char*) &Data + iRegIndex * 2,
					usNRegs * 2);
		} else {
			eStatus = MB_ENOREG;
		}
	} else {
		eStatus = MB_ENOREG;
	}
	return eStatus;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBRegCoilsCB(UCHAR *pucRegBuffer, USHORT usAddress,
		USHORT usNCoils, eMBRegisterMode eMode) {
	return MB_ENOREG;
}
/*----------------------------------------------------------------------------*/
eMBErrorCode eMBRegDiscreteCB(UCHAR *pucRegBuffer, USHORT usAddress,
		USHORT usNDiscrete) {
	return MB_ENOREG;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern ADC_HandleTypeDef hadc1;
extern volatile uint16_t adc_value;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_HandleTypeDef hrtc;
extern char showTime[10];
extern char showDate[12];
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Program_Handler(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZ0_Pin GPIO_PIN_1
#define BUZ0_GPIO_Port GPIOA
#define BUZ1_Pin GPIO_PIN_2
#define BUZ1_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_10
#define LCD_RST_GPIO_Port GPIOB
#define LCD_DI_Pin GPIO_PIN_11
#define LCD_DI_GPIO_Port GPIOB
#define LCD_CLK_Pin GPIO_PIN_12
#define LCD_CLK_GPIO_Port GPIOB
#define LCD_SHIFT_Pin GPIO_PIN_13
#define LCD_SHIFT_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_14
#define LCD_E_GPIO_Port GPIOB
#define LCD_DATA_Pin GPIO_PIN_15
#define LCD_DATA_GPIO_Port GPIOB
#define ENC_SW_Pin GPIO_PIN_15
#define ENC_SW_GPIO_Port GPIOA
#define ENC_L_Pin GPIO_PIN_3
#define ENC_L_GPIO_Port GPIOB
#define ENC_R_Pin GPIO_PIN_4
#define ENC_R_GPIO_Port GPIOB
#define LCD_CS1_Pin GPIO_PIN_8
#define LCD_CS1_GPIO_Port GPIOB
#define LCD_CS2_Pin GPIO_PIN_9
#define LCD_CS2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

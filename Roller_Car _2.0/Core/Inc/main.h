/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OUT6_Pin GPIO_PIN_2
#define OUT6_GPIO_Port GPIOE
#define OUT1_Pin GPIO_PIN_3
#define OUT1_GPIO_Port GPIOE
#define OUT7_Pin GPIO_PIN_4
#define OUT7_GPIO_Port GPIOE
#define OUT2_Pin GPIO_PIN_5
#define OUT2_GPIO_Port GPIOE
#define OUT8_Pin GPIO_PIN_6
#define OUT8_GPIO_Port GPIOE
#define OUT3_Pin GPIO_PIN_13
#define OUT3_GPIO_Port GPIOC
#define OUT9_Pin GPIO_PIN_14
#define OUT9_GPIO_Port GPIOC
#define OUT4_Pin GPIO_PIN_15
#define OUT4_GPIO_Port GPIOC
#define OUT10_Pin GPIO_PIN_0
#define OUT10_GPIO_Port GPIOF
#define OUT5_Pin GPIO_PIN_1
#define OUT5_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_2
#define KEY1_GPIO_Port GPIOF
#define KEY2_Pin GPIO_PIN_3
#define KEY2_GPIO_Port GPIOF
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOF
#define EN1_Pin GPIO_PIN_6
#define EN1_GPIO_Port GPIOF
#define CS1_Pin GPIO_PIN_7
#define CS1_GPIO_Port GPIOF
#define EN2_Pin GPIO_PIN_8
#define EN2_GPIO_Port GPIOF
#define CS2_Pin GPIO_PIN_9
#define CS2_GPIO_Port GPIOF
#define EN3_Pin GPIO_PIN_0
#define EN3_GPIO_Port GPIOC
#define CS3_Pin GPIO_PIN_1
#define CS3_GPIO_Port GPIOC
#define EN4_Pin GPIO_PIN_2
#define EN4_GPIO_Port GPIOC
#define CS4_Pin GPIO_PIN_0
#define CS4_GPIO_Port GPIOA
#define CS5_Pin GPIO_PIN_1
#define CS5_GPIO_Port GPIOA
#define EN5_Pin GPIO_PIN_2
#define EN5_GPIO_Port GPIOA
#define PUL_Pin GPIO_PIN_15
#define PUL_GPIO_Port GPIOF
#define DIR_Pin GPIO_PIN_0
#define DIR_GPIO_Port GPIOG
#define IN11_Pin GPIO_PIN_12
#define IN11_GPIO_Port GPIOC
#define IN6_Pin GPIO_PIN_0
#define IN6_GPIO_Port GPIOD
#define IN1_Pin GPIO_PIN_1
#define IN1_GPIO_Port GPIOD
#define IN16_Pin GPIO_PIN_2
#define IN16_GPIO_Port GPIOD
#define IN17_Pin GPIO_PIN_3
#define IN17_GPIO_Port GPIOD
#define IN12_Pin GPIO_PIN_4
#define IN12_GPIO_Port GPIOD
#define IN7_Pin GPIO_PIN_5
#define IN7_GPIO_Port GPIOD
#define IN2_Pin GPIO_PIN_6
#define IN2_GPIO_Port GPIOD
#define IN13_Pin GPIO_PIN_7
#define IN13_GPIO_Port GPIOD
#define IN18_Pin GPIO_PIN_9
#define IN18_GPIO_Port GPIOG
#define IN3_Pin GPIO_PIN_10
#define IN3_GPIO_Port GPIOG
#define IN8_Pin GPIO_PIN_11
#define IN8_GPIO_Port GPIOG
#define IN9_Pin GPIO_PIN_12
#define IN9_GPIO_Port GPIOG
#define IN4_Pin GPIO_PIN_13
#define IN4_GPIO_Port GPIOG
#define IN19_Pin GPIO_PIN_15
#define IN19_GPIO_Port GPIOG
#define IN14_Pin GPIO_PIN_3
#define IN14_GPIO_Port GPIOB
#define IN5_Pin GPIO_PIN_4
#define IN5_GPIO_Port GPIOB
#define IN10_Pin GPIO_PIN_5
#define IN10_GPIO_Port GPIOB
#define IN15_Pin GPIO_PIN_6
#define IN15_GPIO_Port GPIOB
#define IN20_Pin GPIO_PIN_7
#define IN20_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

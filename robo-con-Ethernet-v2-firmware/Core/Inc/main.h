/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define STICK_L_Y_Pin GPIO_PIN_0
#define STICK_L_Y_GPIO_Port GPIOC
#define STICK_L_X_Pin GPIO_PIN_1
#define STICK_L_X_GPIO_Port GPIOC
#define STICK_L_PUSH_Pin GPIO_PIN_2
#define STICK_L_PUSH_GPIO_Port GPIOC
#define STICK_R_PUSH_Pin GPIO_PIN_3
#define STICK_R_PUSH_GPIO_Port GPIOC
#define LED_LIPO_Pin GPIO_PIN_0
#define LED_LIPO_GPIO_Port GPIOA
#define TOGGLE_R_Pin GPIO_PIN_1
#define TOGGLE_R_GPIO_Port GPIOA
#define LEVER_R_Pin GPIO_PIN_2
#define LEVER_R_GPIO_Port GPIOA
#define LIPO_VOLTAGE_Pin GPIO_PIN_3
#define LIPO_VOLTAGE_GPIO_Port GPIOA
#define STICK_R_Y_Pin GPIO_PIN_4
#define STICK_R_Y_GPIO_Port GPIOA
#define STICK_R_X_Pin GPIO_PIN_5
#define STICK_R_X_GPIO_Port GPIOA
#define BUTTON_R4_Pin GPIO_PIN_6
#define BUTTON_R4_GPIO_Port GPIOA
#define BUTTON_R3_Pin GPIO_PIN_7
#define BUTTON_R3_GPIO_Port GPIOA
#define BUTTON_R2_Pin GPIO_PIN_4
#define BUTTON_R2_GPIO_Port GPIOC
#define BUTTON_R1_Pin GPIO_PIN_5
#define BUTTON_R1_GPIO_Port GPIOC
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define W5500_IT_Pin GPIO_PIN_6
#define W5500_IT_GPIO_Port GPIOC
#define W5500_RST_Pin GPIO_PIN_7
#define W5500_RST_GPIO_Port GPIOC
#define TOGGLE_L_Pin GPIO_PIN_8
#define TOGGLE_L_GPIO_Port GPIOC
#define BUTTON_L1_Pin GPIO_PIN_9
#define BUTTON_L1_GPIO_Port GPIOC
#define BUTTON_L2_Pin GPIO_PIN_8
#define BUTTON_L2_GPIO_Port GPIOA
#define BUTTON_L3_Pin GPIO_PIN_9
#define BUTTON_L3_GPIO_Port GPIOA
#define BUTTON_L4_Pin GPIO_PIN_10
#define BUTTON_L4_GPIO_Port GPIOA
#define LEVER_L_Pin GPIO_PIN_15
#define LEVER_L_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_10
#define LED0_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOB
#define LED_USB_Pin GPIO_PIN_4
#define LED_USB_GPIO_Port GPIOB
#define LED_W5500_Pin GPIO_PIN_5
#define LED_W5500_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

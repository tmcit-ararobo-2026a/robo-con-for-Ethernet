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
#define ST_LED_4_Pin GPIO_PIN_13
#define ST_LED_4_GPIO_Port GPIOC
#define ST_LED_3_Pin GPIO_PIN_14
#define ST_LED_3_GPIO_Port GPIOC
#define ST_LED_2_Pin GPIO_PIN_15
#define ST_LED_2_GPIO_Port GPIOC
#define ST_LED_1_Pin GPIO_PIN_0
#define ST_LED_1_GPIO_Port GPIOF
#define ST_LED_0_Pin GPIO_PIN_1
#define ST_LED_0_GPIO_Port GPIOF
#define Left_X_Stick_Pin GPIO_PIN_0
#define Left_X_Stick_GPIO_Port GPIOC
#define Left_Y_Stick_Pin GPIO_PIN_1
#define Left_Y_Stick_GPIO_Port GPIOC
#define Left_Push_Stick_Pin GPIO_PIN_2
#define Left_Push_Stick_GPIO_Port GPIOC
#define Right_Push_Stick_Pin GPIO_PIN_3
#define Right_Push_Stick_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define W5500_nINT_Pin GPIO_PIN_0
#define W5500_nINT_GPIO_Port GPIOB
#define W5500_nINT_EXTI_IRQn EXTI0_IRQn
#define W5500_RST_Pin GPIO_PIN_1
#define W5500_RST_GPIO_Port GPIOB
#define Right_X_Stick_Pin GPIO_PIN_11
#define Right_X_Stick_GPIO_Port GPIOB
#define Right_Y_Stick_Pin GPIO_PIN_12
#define Right_Y_Stick_GPIO_Port GPIOB
#define Right_Button_5_Pin GPIO_PIN_13
#define Right_Button_5_GPIO_Port GPIOB
#define Right_Button_6_Pin GPIO_PIN_14
#define Right_Button_6_GPIO_Port GPIOB
#define Right_Button_7_Pin GPIO_PIN_15
#define Right_Button_7_GPIO_Port GPIOB
#define Right_Lever_Switch_2_Pin GPIO_PIN_6
#define Right_Lever_Switch_2_GPIO_Port GPIOC
#define Right_Lever_Switch_1_Pin GPIO_PIN_7
#define Right_Lever_Switch_1_GPIO_Port GPIOC
#define Right_Lever_Switch_0_Pin GPIO_PIN_8
#define Right_Lever_Switch_0_GPIO_Port GPIOC
#define Right_Lever_Switch_4_Pin GPIO_PIN_9
#define Right_Lever_Switch_4_GPIO_Port GPIOC
#define Right_Lever_Switch_3_Pin GPIO_PIN_8
#define Right_Lever_Switch_3_GPIO_Port GPIOA
#define ST_LED_W5500_Pin GPIO_PIN_9
#define ST_LED_W5500_GPIO_Port GPIOA
#define ST_LED_USB_Pin GPIO_PIN_10
#define ST_LED_USB_GPIO_Port GPIOA
#define Left_Button_1_Pin GPIO_PIN_15
#define Left_Button_1_GPIO_Port GPIOA
#define Left_Button_2_Pin GPIO_PIN_10
#define Left_Button_2_GPIO_Port GPIOC
#define Left_Button_3_Pin GPIO_PIN_11
#define Left_Button_3_GPIO_Port GPIOC
#define Left_Button_4_Pin GPIO_PIN_12
#define Left_Button_4_GPIO_Port GPIOC
#define Left_Lever_Switch_3_Pin GPIO_PIN_3
#define Left_Lever_Switch_3_GPIO_Port GPIOB
#define Left_Lever_Switch_4_Pin GPIO_PIN_4
#define Left_Lever_Switch_4_GPIO_Port GPIOB
#define Left_Lever_Switch_0_Pin GPIO_PIN_5
#define Left_Lever_Switch_0_GPIO_Port GPIOB
#define Left_Lever_Switch_2_Pin GPIO_PIN_6
#define Left_Lever_Switch_2_GPIO_Port GPIOB
#define Left_Lever_Switch_1_Pin GPIO_PIN_7
#define Left_Lever_Switch_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

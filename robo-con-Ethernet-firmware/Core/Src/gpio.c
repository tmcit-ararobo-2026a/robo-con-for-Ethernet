/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ST_LED_4_Pin|ST_LED_3_Pin|ST_LED_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, ST_LED_1_Pin|ST_LED_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(W5500_nRST_GPIO_Port, W5500_nRST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ST_LED_W5500_Pin|ST_LED_USB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ST_LED_4_Pin ST_LED_3_Pin ST_LED_2_Pin */
  GPIO_InitStruct.Pin = ST_LED_4_Pin|ST_LED_3_Pin|ST_LED_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : ST_LED_1_Pin ST_LED_0_Pin */
  GPIO_InitStruct.Pin = ST_LED_1_Pin|ST_LED_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : Left_Push_Stick_Pin Right_Push_Stick_Pin Right_Lever_Switch_2_Pin Right_Lever_Switch_1_Pin
                           Right_Lever_Switch_0_Pin Right_Lever_Switch_4_Pin */
  GPIO_InitStruct.Pin = Left_Push_Stick_Pin|Right_Push_Stick_Pin|Right_Lever_Switch_2_Pin|Right_Lever_Switch_1_Pin
                          |Right_Lever_Switch_0_Pin|Right_Lever_Switch_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : W5500_nINT_Pin */
  GPIO_InitStruct.Pin = W5500_nINT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(W5500_nINT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : W5500_nRST_Pin */
  GPIO_InitStruct.Pin = W5500_nRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(W5500_nRST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Right_Button_5_Pin Right_Button_6_Pin Right_Button_7_Pin */
  GPIO_InitStruct.Pin = Right_Button_5_Pin|Right_Button_6_Pin|Right_Button_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Right_Lever_Switch_3_Pin */
  GPIO_InitStruct.Pin = Right_Lever_Switch_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Right_Lever_Switch_3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST_LED_W5500_Pin ST_LED_USB_Pin */
  GPIO_InitStruct.Pin = ST_LED_W5500_Pin|ST_LED_USB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Left_Button_1_Pin */
  GPIO_InitStruct.Pin = Left_Button_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(Left_Button_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Left_Button_2_Pin Left_Button_3_Pin Left_Button_4_Pin */
  GPIO_InitStruct.Pin = Left_Button_2_Pin|Left_Button_3_Pin|Left_Button_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Left_Lever_Switch_3_Pin Left_Lever_Switch_4_Pin Left_Lever_Switch_0_Pin Left_Lever_Switch_2_Pin
                           Left_Lever_Switch_1_Pin */
  GPIO_InitStruct.Pin = Left_Lever_Switch_3_Pin|Left_Lever_Switch_4_Pin|Left_Lever_Switch_0_Pin|Left_Lever_Switch_2_Pin
                          |Left_Lever_Switch_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

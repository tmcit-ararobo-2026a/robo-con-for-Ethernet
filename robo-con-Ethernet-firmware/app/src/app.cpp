#include "app/app.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>

#include "adc.h"
#include "app/robot_config.hpp"
#include "app/robot_ethernet.hpp"
#include "app/stick_config.hpp"
#include "tim.h"

namespace {

bool timer_triggered = false;
robot_config::teleop_t teleop;
RobotEthernet ether;
uint16_t adc_raw_value[4];
/* Hartbeat LED用 */
constexpr uint32_t k_heartbeat_toggle_interval_ms = 500;
uint32_t heartbeat_last_toggle_time_ms            = 0;
/**
 * @brief 一定周期のLEDチカチカ処理
 *
 */
void update_heartbeat_led()
{
    const uint32_t now_ms = HAL_GetTick();
    if ((now_ms - heartbeat_last_toggle_time_ms) >= k_heartbeat_toggle_interval_ms) {
        heartbeat_last_toggle_time_ms = now_ms;
        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    }
}

/**
 * @brief uint16のADC後の値をint8へ正規化
 *
 * @param target_adc_buffer 処理するADC値
 * @param zero_reference ADCのどの値をゼロとするか
 */
int8_t normalize_adc_value(uint16_t target_adc_buffer, uint16_t zero_reference)
{
    int normalized_value = 0;
    normalized_value     = target_adc_buffer - zero_reference;
    normalized_value     = std::clamp(normalized_value, INT8_MIN, INT8_MAX);
    return (int8_t)normalized_value;
}

void update_stick_values()
{
    teleop.analog.stick_right[0] = -normalize_adc_value(adc_raw_value[3], STICK_X_R_CENTER);
    teleop.analog.stick_right[1] = normalize_adc_value(adc_raw_value[2], STICK_Y_R_CENTER);
    teleop.analog.stick_left[0]  = -normalize_adc_value(adc_raw_value[0], STICK_X_L_CENTER);
    teleop.analog.stick_left[1]  = normalize_adc_value(adc_raw_value[1], STICK_Y_L_CENTER);
}

void update_buttons_value()
{
    teleop.buttons.up               = HAL_GPIO_ReadPin(BUTTON_L1_GPIO_Port, BUTTON_L1_Pin);
    teleop.buttons.down             = HAL_GPIO_ReadPin(BUTTON_L2_GPIO_Port, BUTTON_L2_Pin);
    teleop.buttons.right            = HAL_GPIO_ReadPin(BUTTON_L3_GPIO_Port, BUTTON_L3_Pin);
    teleop.buttons.left             = HAL_GPIO_ReadPin(BUTTON_L4_GPIO_Port, BUTTON_L4_Pin);
    teleop.buttons.circle           = HAL_GPIO_ReadPin(BUTTON_R5_GPIO_Port, BUTTON_R5_Pin);
    teleop.buttons.cross            = HAL_GPIO_ReadPin(BUTTON_R6_GPIO_Port, BUTTON_R6_Pin);
    teleop.buttons.triangle         = HAL_GPIO_ReadPin(BUTTON_R7_GPIO_Port, BUTTON_R7_Pin);
    teleop.buttons.stick_push_left  = HAL_GPIO_ReadPin(STICK_PUSH_L_GPIO_Port, STICK_PUSH_L_Pin);
    teleop.buttons.stick_push_right = HAL_GPIO_ReadPin(STICK_PUSH_R_GPIO_Port, STICK_PUSH_R_Pin);
}

void update_levers_value()
{
    /* left lever*/
    teleop.buttons.lever_left = robot_config::LeverPosition::FRONT;
    if (HAL_GPIO_ReadPin(LEVER_L0_GPIO_Port, LEVER_L0_Pin) == GPIO_PIN_SET) {
        teleop.buttons.lever_left = robot_config::LeverPosition::PUSH;
    } else {
        if (HAL_GPIO_ReadPin(LEVER_L2_GPIO_Port, LEVER_L2_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_left = robot_config::LeverPosition::LEFT_DEEP;
        } else if (HAL_GPIO_ReadPin(LEVER_L1_GPIO_Port, LEVER_L1_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_left = robot_config::LeverPosition::LEFT;
        }
        if (HAL_GPIO_ReadPin(LEVER_L4_GPIO_Port, LEVER_L4_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_left = robot_config::LeverPosition::RIGHT_DEEP;
        } else if (HAL_GPIO_ReadPin(LEVER_L3_GPIO_Port, LEVER_L3_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_left = robot_config::LeverPosition::RIGHT;
        }
    }
    /* right lever*/
    teleop.buttons.lever_right = robot_config::LeverPosition::FRONT;
    if (HAL_GPIO_ReadPin(LEVER_R0_GPIO_Port, LEVER_R0_Pin) == GPIO_PIN_SET) {
        teleop.buttons.lever_right = robot_config::LeverPosition::PUSH;
    } else {
        if (HAL_GPIO_ReadPin(LEVER_R2_GPIO_Port, LEVER_R2_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_right = robot_config::LeverPosition::LEFT;
        } else if (HAL_GPIO_ReadPin(LEVER_R1_GPIO_Port, LEVER_R1_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_right = robot_config::LeverPosition::LEFT_DEEP;
        }
        if (HAL_GPIO_ReadPin(LEVER_R4_GPIO_Port, LEVER_R4_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_right = robot_config::LeverPosition::RIGHT;
        } else if (HAL_GPIO_ReadPin(LEVER_R3_GPIO_Port, LEVER_R3_Pin) == GPIO_PIN_SET) {
            teleop.buttons.lever_right = robot_config::LeverPosition::RIGHT_DEEP;
        }
    }
}

void send_teleop()
{
    // teleopの値を更新
    update_stick_values();
    update_buttons_value();
    update_levers_value();
    // Ethernetで送信
    ether.send_teleop(teleop);
    // デバッグ表示
    /*
    printf(
        "teleop: header=%u stick_r=(%d,%d) stick_l=(%d,%d) "
        "lever_r=%u lever_l=%u "
        "push_r=%u push_l=%u buttons=(up:%u down:%u right:%u left:%u "
        "circle:%u cross:%u triangle:%u) checksum=%u\r\n",
        static_cast<unsigned>(teleop.header),
        teleop.analog.stick_right[0],
        teleop.analog.stick_right[1],
        teleop.analog.stick_left[0],
        teleop.analog.stick_left[1],
        static_cast<unsigned>(teleop.buttons.lever_right),
        static_cast<unsigned>(teleop.buttons.lever_left),
        static_cast<unsigned>(teleop.buttons.stick_push_right),
        static_cast<unsigned>(teleop.buttons.stick_push_left),
        static_cast<unsigned>(teleop.buttons.up),
        static_cast<unsigned>(teleop.buttons.down),
        static_cast<unsigned>(teleop.buttons.right),
        static_cast<unsigned>(teleop.buttons.left),
        static_cast<unsigned>(teleop.buttons.circle),
        static_cast<unsigned>(teleop.buttons.cross),
        static_cast<unsigned>(teleop.buttons.triangle),
        static_cast<unsigned>(teleop.data_checksum)
    );
    */
    HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
}
}  // namespace

void setup()
{
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_value, 4) != HAL_OK) {
        Error_Handler();
    }
    if (!ether.init()) {
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
    }
    HAL_TIM_Base_Start_IT(&htim6);
    heartbeat_last_toggle_time_ms = HAL_GetTick();
}

void loop()
{
    if (timer_triggered) {
        send_teleop();
        timer_triggered = false;
    }
    update_heartbeat_led();
}
extern "C" {

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim->Instance == htim6.Instance) {  // 100Hz timer
        timer_triggered = true;
    }
}
}
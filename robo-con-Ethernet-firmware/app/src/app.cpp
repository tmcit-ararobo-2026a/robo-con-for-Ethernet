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
void mcu_wake_led()
{
    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_USB_GPIO_Port, LED_USB_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_W5500_GPIO_Port, LED_W5500_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

    HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_USB_GPIO_Port, LED_USB_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(LED_W5500_GPIO_Port, LED_W5500_Pin, GPIO_PIN_RESET);
}
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
        HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
    }
}
/* TelopRate */
constexpr uint32_t k_teleop_count_max = 10 / 2;
uint32_t teleop_count                 = 0;
/**
 * @brief 10回に1回LEDをトグルする
 *
 */
void update_teleop_rate_led()
{
    teleop_count++;
    if (teleop_count >= k_teleop_count_max) {
        teleop_count = 0;
        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    }
}
/**
 * @brief uint16のADC後の値をint8へ正規化（デッドゾーン処理付き）
 *
 * @param target_adc_buffer 処理するADC値
 * @param zero_reference ADCのセンター（中立）値
 * @param min センターからの負方向の最大偏差（負の整数、例: -115）
 * @param max センターからの正方向の最大偏差（正の整数、例: 115）
 */
int8_t normalize_adc_value(uint16_t target_adc_buffer, int zero_reference, int min, int max)
{
    // センター位置からの偏差を計算
    int diff = static_cast<int>(target_adc_buffer) - zero_reference;

    // デッドゾーン（±10）の範囲内なら 0 を返す
    if (std::abs(diff) <= STICK_CENTER_MARGIN) {
        return 0;
    }

    int scaled_value = 0;

    if (diff > STICK_CENTER_MARGIN) {
        // 正の方向: デッドゾーンを超えた分を 0 ~ STICK_REFERENCE_MAX にスケーリング
        const int effective_range = max - STICK_CENTER_MARGIN;
        if (effective_range > 0) {
            scaled_value = (diff - STICK_CENTER_MARGIN) * STICK_REFERENCE_MAX / effective_range;
        }
    } else {
        // 負の方向: デッドゾーンを超えた分を 0 ~ -STICK_REFERENCE_MAX にスケーリング
        const int effective_range = -min - STICK_CENTER_MARGIN;  // -min で絶対値化
        if (effective_range > 0) {
            scaled_value = (diff + STICK_CENTER_MARGIN) * (-STICK_REFERENCE_MAX) / effective_range;
        }
    }
    return static_cast<int8_t>(std::clamp(scaled_value, -STICK_REFERENCE_MAX, STICK_REFERENCE_MAX));
}

void update_stick_values()
{
    teleop.analog.stick_right[0] =
        -normalize_adc_value(adc_raw_value[3], STICK_X_R_CENTER, STICK_X_R_MIN, STICK_X_R_MAX);
    teleop.analog.stick_right[1] =
        normalize_adc_value(adc_raw_value[2], STICK_Y_R_CENTER, STICK_Y_R_MIN, STICK_Y_R_MAX);
    teleop.analog.stick_left[0] =
        -normalize_adc_value(adc_raw_value[0], STICK_X_L_CENTER, STICK_X_L_MIN, STICK_X_L_MAX);
    teleop.analog.stick_left[1] =
        normalize_adc_value(adc_raw_value[1], STICK_Y_L_CENTER, STICK_Y_L_MIN, STICK_Y_L_MAX);
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
    update_teleop_rate_led();
}
}  // namespace

void setup()
{
    mcu_wake_led();
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_value, 4) != HAL_OK) {
        Error_Handler();
    }
    if (ether.init()) {
        HAL_GPIO_WritePin(LED_W5500_GPIO_Port, LED_W5500_Pin, GPIO_PIN_SET);
    }
    HAL_TIM_Base_Start_IT(&htim6);
    heartbeat_last_toggle_time_ms = HAL_GetTick();
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
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
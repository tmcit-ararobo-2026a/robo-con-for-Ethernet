#include "app/app.hpp"

#include <cstdint>
#include <algorithm>

#include "adc.h"
#include "app/robot_config.hpp"
#include "app/stick_config.hpp"

namespace {

robot_config::teleop_t teleop;

uint16_t adc_raw_value[2];
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
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
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
    if (target_adc_buffer < zero_reference)
    {
        normalized_value = -target_adc_buffer;
    } else {
        normalized_value = target_adc_buffer;
    }
    normalized_value = std::clamp(normalized_value, INT8_MIN, INT8_MAX);
    return (int8_t)normalized_value;   
}

void update_stick_values()
{
    
}

}  // namespace

void setup()
{
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_raw_value, 4) != HAL_OK) {
        Error_Handler();
    }
}

void loop()
{
    update_heartbeat_led();
}
extern "C" {
}
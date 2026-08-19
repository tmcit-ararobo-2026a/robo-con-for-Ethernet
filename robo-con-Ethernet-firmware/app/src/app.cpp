#include "app/app.hpp"

#include <cstdint>

#include "adc.h"

namespace {
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
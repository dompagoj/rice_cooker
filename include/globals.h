#pragma once

#include "app_state.h"
#include "ha_wrappers.h"

extern AppState app_state;

namespace devices
{

void init_devices();

extern CustomHASwitch power_switch;
extern CustomHASwitch high_temp_switch;
extern CustomHASwitch buzzer_switch;
extern CustomHASensor turn_off_sensor;
extern HASensor timer_sensor_ha;

} // namespace devices

#pragma once

#include "Buzzer.h"
#include "app_state.h"
#include "ha_wrappers.h"
#include "rotary.h"
#include <OneButton.h>

extern AppState app_state;

namespace devices
{

void init_devices();

extern CustomHASwitch keep_warm_switch;
extern CustomHASwitch high_temp_switch;
extern Buzzer buzzer;
extern CustomHASensor turn_off_sensor;
extern HASensor timer_sensor_ha;
extern OneButton power_button;
extern OneButton rotary_button;
extern Rotary rotary_encoder;

} // namespace devices

#include "app_state.h"
#include "TimeLib.h"
#include "globals.h"
#include "math.h"

void AppState::tick()
{
    m_cooker.tick();
    m_keep_warm.update(devices::keep_warm_switch.read_state());
    m_turnoff_sensor.update(devices::turn_off_sensor.update_state());

    devices::power_button.tick();
    devices::rotary_button.tick();
}

AppState::AppState() = default;

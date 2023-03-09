#include "app_state.h"
#include "TimeLib.h"
#include "globals.h"

void AppState::tick()
{
    m_power.update(devices::power_switch.read_state());
    m_heat.update(devices::high_temp_switch.read_state());
    m_turnoff_sensor.update(devices::turn_off_sensor.update_state());
}

AppState::AppState() = default;

void CookTimer::start()
{
    m_is_in_progress = true;
    m_start_time = now();
}

void CookTimer::end()
{
    m_is_in_progress = false;
}

void CookTimer::tick()
{
    auto now_millis = millis();
    if (now_millis - m_last_milis < 1000)
        return;

    m_last_milis = now_millis;

    time_t curr = now();

    // if ()
}

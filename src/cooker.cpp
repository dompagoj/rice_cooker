#include "cooker.h"

#include "globals.h"

bool RotaryState::operator==(const RotaryState &other) const
{
    return m_pos == other.m_pos;
}

bool RotaryState::operator!=(const RotaryState &other) const
{
    return m_pos != other.m_pos;
}

void Cooker::tick()
{
    m_has_changed = false;
    m_heat.update(devices::high_temp_switch.read_state());
    m_rotary_state.update(devices::rotary_encoder.get_state());

    if (m_is_started)
        tick_timer();

    update_timer();
}

void Cooker::start()
{
    m_is_started = true;
    devices::buzzer.cook_started();
}

void Cooker::end()
{
    m_is_started = false;
    reset();
    devices::high_temp_switch.turn_off();
    devices::buzzer.cook_ended();
}

void Cooker::reset()
{
    if (m_is_started || is_zero())
        return;

    m_minutes = 0;
    m_seconds = 0;
    m_timer_str = INITIAL_TIMER_STR;
    m_has_changed = true;
}

const String &Cooker::get_str() const
{
    return m_timer_str;
}

bool Cooker::has_changed() const
{
    return m_has_changed || m_rotary_state.is_changed;
}

bool Cooker::is_zero()
{
    return m_minutes == 0 && m_seconds == 0;
}

void Cooker::pause()
{
    m_is_started = false;
}

void Cooker::update_timer()
{
    if (m_rotary_state.is_changed)
    {

        m_minutes = clamp(m_rotary_state.state.m_dir == RotaryEncoder::Direction::CLOCKWISE ? m_minutes + 1 : m_minutes - 1, 0, 99);
    }
    else if (!m_is_started)
        return;

    char buf[3];
    utoa(m_minutes, buf, 10);
    if (m_minutes < 10)
    {
        buf[1] = buf[0];
        buf[0] = '0';
    }
    memcpy((char *)m_timer_str.c_str(), buf, 2);

    utoa(m_seconds, buf, 10);
    if (m_seconds < 10)
    {
        buf[1] = buf[0];
        buf[0] = '0';
    }
    memcpy((char *)m_timer_str.c_str() + 3, buf, 2);
}

void Cooker::tick_timer()
{
    auto now = millis();
    if (now - m_last_tick_time < 1000)
        return;

    m_has_changed = true;
    if (m_seconds == 0)
    {
        if (m_minutes == 0)
        {
            end();
        }
        else
        {
            m_minutes--;
            m_seconds = 59;
        }
    }
    else
    {
        m_seconds--;
    }

    m_last_tick_time = now;
}

#include "ha_wrappers.h"

CustomHASwitch::CustomHASwitch(const char *id, Pin pin, const char *name, const char *icon) : HASwitch(id), m_Pin(pin)
{
    setName(name);
    if (icon != nullptr)
    {
        setIcon(icon);
    }

    onCommand([](bool state, HASwitch *sender) {
        auto *sw = static_cast<CustomHASwitch *>(sender);
        if (sw->m_ChangeCb)
        {
            sw->m_ChangeCb(state, sw);
        }
        sw->m_Pin.set(state);
        sw->setState(state);
    });
}

void CustomHASwitch::turn_off()
{
    set_state(false);
}

void CustomHASwitch::turn_on()
{
    set_state(true);
}

void CustomHASwitch::set_state(bool state)
{
    if (m_ChangeCb)
        m_ChangeCb(state, this);

    setState(state);
    m_Pin.set(state);
}

void CustomHASwitch::toggle()
{
    auto state = m_Pin.read_bool();
    set_state(!state);
}

bool CustomHASwitch::read_state()
{
    return m_Pin.read_bool();
}

bool CustomHASwitch::read_ha_state()
{
    return getCurrentState();
}

CustomHASensor::CustomHASensor(char *id, Pin pin, const char *name, const char *icon) : HASensor(id), m_Pin(pin)
{
    setName(name);
    if (icon)
    {
        setIcon(icon);
    }
}

bool CustomHASensor::read_state()
{
    return m_Pin.read_bool();
}

bool CustomHASensor::update_state()
{
    bool state = read_state();
    if (m_State != state)
    {
        m_ChangeCb(state, this);
    }
    m_State = state;

    return state;
}

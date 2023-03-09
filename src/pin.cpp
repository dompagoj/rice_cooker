#include "pin.h"

Pin::Pin(u8 pin, u8 mode, bool inverted) : m_Pin(pin), m_Mode(mode), m_Inverted(inverted)
{
    pinMode(pin, mode);
    if (mode == OUTPUT)
    {
        digitalWrite(pin, inverted ? HIGH : LOW);
    }
}

void Pin::turn_on()
{
    set(true);
}

void Pin::set(bool state)
{
    auto arduino_state = state ? HIGH : LOW;
    digitalWrite(m_Pin, m_Inverted ? !arduino_state : arduino_state);
}

void Pin::turn_off()
{
    set(false);
}

i8 Pin::read() const
{
    return digitalRead(m_Pin);
}

bool Pin::read_bool() const
{
    auto res = read() == HIGH ? true : false;
    return m_Inverted ? !res : res;
}

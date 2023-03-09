#pragma once
#include "TypeDefs.h"
#include <ArduinoHA.h>

enum class PinMode
{
    Input,
    Output,
};

enum class PinState
{
    High,
    Low,
};

inline u8 getPinState(PinState state)
{
    return state == PinState::High ? HIGH : LOW;
}

inline u8 getPinMode(PinMode mode)
{
    return mode == PinMode::Input ? INPUT : OUTPUT;
}

struct Pin
{
    u8 m_Pin;
    u8 m_Mode;
    bool m_Inverted;

    explicit Pin(u8 pin, u8 mode, bool inverted = false);

    void turn_on();

    void set(bool state);

    void turn_off();

    i8 read() const;
    bool read_bool() const;
};
#include "rotary.h"

Rotary::Rotary(i8 pin1, i8 pin2) : m_encoder(pin1, pin2, RotaryEncoder::LatchMode::FOUR3)
{
}

void Rotary::tick()
{
    m_encoder.tick();
}

i32 Rotary::get_pos()
{
    return -m_encoder.getPosition();
}

RotaryEncoder::Direction Rotary::get_dir()
{
    auto dir = static_cast<i8>(m_encoder.getDirection());

    return static_cast<RotaryEncoder::Direction>(-dir);
}

RotaryState Rotary::get_state()
{
    RotaryState state{get_pos(), get_dir()};

    return state;
}

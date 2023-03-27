#pragma once

#include "TypeDefs.h"
#include "app_state.h"
#include <RotaryEncoder.h>

struct Rotary
{
    Rotary(i8 pin1, i8 pin2);

    void tick();
    i32 get_pos();
    RotaryEncoder::Direction get_dir();

    RotaryState get_state();

    /* data */
  private:
    RotaryEncoder m_encoder;
};

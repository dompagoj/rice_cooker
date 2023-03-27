#pragma once

#include "Arduino.h"
#include "TypeDefs.h"
#include <RotaryEncoder.h>

#include "cooker.h"
#include "state.h"

struct AppState
{
    State<bool> m_keep_warm{};
    State<bool> m_turnoff_sensor{};
    Cooker m_cooker{};
    bool m_is_display_off{};

    void tick();

    AppState();
};
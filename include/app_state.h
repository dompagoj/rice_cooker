#pragma once

#include "Arduino.h"
#include "TypeDefs.h"

template <typename T> struct State
{
    T state{};
    bool is_changed = true;

    void update(T val)
    {
        is_changed = val != state;
        state = val;
    }
};

struct CookTimer
{
    unsigned long m_last_milis = 0;
    time_t m_start_time = 0;
    bool m_is_in_progress{};

    void start();
    void end();
    void tick();
};

struct AppState
{
    State<bool> m_power{};
    State<bool> m_heat{};
    State<bool> m_turnoff_sensor{};

    bool m_cook_startet = false;

    void tick();

    AppState();
};
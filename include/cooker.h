#pragma once

#include "RotaryEncoder.h"
#include "TypeDefs.h"
#include "state.h"

#define INITIAL_TIMER_STR "00:00";

struct RotaryState
{
    i32 m_pos;
    RotaryEncoder::Direction m_dir;
    bool operator==(const RotaryState &other) const;
    bool operator!=(const RotaryState &other) const;
};

struct Cooker
{
    u8 m_minutes = 0;
    u8 m_seconds = 0;
    u32 m_last_tick_time{};

    bool m_is_started = false;
    String m_timer_str = INITIAL_TIMER_STR;
    State<RotaryState> m_rotary_state{};
    State<bool> m_heat{};

    void tick();
    void start();
    void end();
    void reset();
    bool has_changed() const;
    bool is_zero();
    void pause();
    const String &get_str() const;

  private:
    bool m_has_changed = false;
    void update_timer();
    void tick_timer();
};
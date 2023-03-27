#pragma once

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
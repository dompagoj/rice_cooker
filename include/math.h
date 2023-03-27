#pragma once

template <typename T> inline T clamp(T val, T min, T max)
{
    if (val > max)
        return max;
    if (val < min)
        return min;

    return val;
}

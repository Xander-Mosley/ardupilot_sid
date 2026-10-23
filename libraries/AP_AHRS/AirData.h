#pragma once

#include <cmath>
#include <cstdint>

// Pure telemetry math shared by AHRS and native tests. Does not change EKF fusion.
namespace AP_AirData {
inline uint16_t rate_hz(int16_t requested)
{
    return requested == 50 || requested == 100 ? requested : 20;
}
inline bool due(uint32_t now, uint32_t previous, int16_t requested)
{
    return uint32_t(now - previous) >= 1000U / rate_hz(requested);
}
inline uint16_t flow_flags(float u, float v, float w)
{
    if (!std::isfinite(u) || !std::isfinite(v) || !std::isfinite(w)) { return 0; }
    return 2U | ((u*u + v*v + w*w >= 4) ? 4U : 0U) | (u > 0 ? 8U : 0U);
}
inline float alpha(float u, float w)
{
    return u > 0 ? atanf(w/u) : 0;
}
inline float beta(float u, float v, float w)
{
    const float speed = sqrtf(u*u + v*v + w*w);
    return speed > 0 ? asinf(fmaxf(-1, fminf(1, v/speed))) : 0;
}
}

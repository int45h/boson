#pragma once

/*
    common_float.h: Common maths functions (float)
*/
#define _USE_MATH_DEFINES
#include <math.h>

/* 
    https://github.com/xbpeng/DeepMimic/issues/17 
    bssrdf came up with this clever but effective trick
*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const float  _180_OVER_PI = 180.f / M_PI,
                    _PI_OVER_180 = M_PI / 180.f;

static float radians_f(float deg)
{
    return deg * _PI_OVER_180;
}

static float degrees_f(float rad)
{
    return rad * _180_OVER_PI;
}

static float minf(float a, float b)
{
    return (a < b) ? a : b;
}

static float maxf(float a, float b)
{
    return (a > b) ? a : b;
}

static float clampf(float x, float l, float u)
{
    return minf(maxf(x, l), u);
}

static float lerpf(float a, float b, float x)
{
    return ((1 - x) * a) + (x * b);
}
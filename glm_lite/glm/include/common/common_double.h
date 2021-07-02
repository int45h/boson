#pragma once

/*
    common_double.h:    Common maths functions (double)
*/
#include <math.h>

/* 
    https://github.com/xbpeng/DeepMimic/issues/17 
    bssrdf came up with this clever but effective trick
*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const double _180_OVER_PID = (double)180 / M_PI,
                    _PI_OVER_180D = M_PI / (double)180;

static double radians_d(double deg)
{
    return deg * _PI_OVER_180D;
}

static double degrees_d(double rad)
{
    return rad * _180_OVER_PID;
}

static double mind(double a, double b)
{
    return (a < b) ? a : b;
}

static double maxd(double a, double b)
{
    return (a > b) ? a : b;
}

static double clampd(double x, double l, double u)
{
    return minf(maxf(x, l), u);
}

static double lerpd(double a, double b, double x)
{
    return ((1 - x) * a) + (x * b);
}
#pragma once

/*
    common_int.h:   Common maths functions (int)
*/
#include <math.h>

static int mini(int a, int b)
{
    return (a < b) ? a : b;
}

static int maxi(int a, int b)
{
    return (a > b) ? a : b;
}

static int clampi(int x, int l, int u)
{
    return minf(maxf(x, l), u);
}

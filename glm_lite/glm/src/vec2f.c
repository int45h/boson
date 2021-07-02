#include "../include/vec2f.h"

/*
    vec4f.c:    C source file for all float vec2 operations
*/

vec2f vec2f_init(float v[2])
{
    return (vec2f){v[0], v[1]};
}

void vec2f_copy(float src[2], float dest[2])
{
    dest[0] = src[0];
    dest[1] = src[1];
}

vec2f vec2f_zero_new()
{
    return (vec2f){0, 0};
}

void vec2f_zero(float v[2])
{
    v[0] = v[1] = 0;
}

vec2f vec2f_set_s_new(float s)
{
    return (vec2f){s, s};
}

void vec2f_set_s(float v[2], float s)
{
    v[0] = v[1] = s;
}

float vec2f_dot(float a[2], float b[2])
{
    return (a[0] * b[0]) + (a[1] * b[1]);
}

float vec2f_length(float v[2])
{
    return sqrt(v[0]*v[0] + v[1]*v[1]);
}

void vec2f_normalize(float v[2])
{
    float inv_mag = 1.f / vec2f_length(v);
    v[0] *= inv_mag;
    v[1] *= inv_mag;
}

void vec2f_add(float a[2], float b[2])
{
    b[0] = a[0] + b[0];
    b[1] = a[1] + b[1];
}

void vec2f_sub(float a[2], float b[2])
{
    b[0] = a[0] - b[0];
    b[1] = a[1] - b[1];
}

void vec2f_adds(float a[2], float b)
{
    a[0] += b;
    a[1] += b;
}

void vec2f_subs(float a[2], float b)
{
    a[0] -= b;
    a[1] -= b;
}

void vec2f_scale(float v[2], float s)
{
    v[0] *= s;
    v[1] *= s;
}

vec2f vec2f_add_new(float a[2], float b[2])
{
    return  (vec2f){    a[0] + b[0],
                        a[1] + b[1] };
}

vec2f vec2f_sub_new(float a[2], float b[2])
{
    return  (vec2f){    a[0] - b[0],
                        a[1] - b[1] };
}

vec2f vec2f_adds_new(float a[2], float b)
{
    return  (vec2f){    a[0] + b,
                        a[1] + b    };
}

vec2f vec2f_subs_new(float a[2], float b)
{
    return  (vec2f){    a[0] - b,
                        a[1] - b    };
}

vec2f vec2f_scale_new(float v[2], float s)
{
    return  (vec2f){    v[0] * s,
                        v[1] * s    };
}

void vec2f_mul(float a[2], float b[2])
{
    b[0] *= a[0];
    b[1] *= a[1];
}

vec2f vec2f_mul_new(float a[2], float b[2])
{
    return  (vec2f){    b[0] * a[0],
                        b[1] * a[1] };
}

vec2f vec2f_min_new(float a[2], float b[2])
{
    return  (vec2f){    minf(a[0], b[0]),
                        minf(a[1], b[1])    };
}

vec2f vec2f_max_new(float a[2], float b[2])
{
    return  (vec2f){    maxf(a[0], b[0]),
                        maxf(a[1], b[1])    };
}

vec2f vec2f_clamp_new(float a[2], float l[2], float u[2])
{
    return  (vec2f){    clampf(a[0], l[0], u[0]),
                        clampf(a[1], l[1], u[1])    };
}

vec2f vec2f_lerp_new(float a[2], float b[2], float t, float dest[2])
{
    return  (vec2f){    lerpf(a[0], b[0], t),
                        lerpf(a[1], b[1], t)    };
}

void vec2f_min(float a[2], float b[2], float dest[2])
{
    dest[0] = minf(a[0], b[0]);
    dest[1] = minf(a[1], b[1]);
}

void vec2f_max(float a[2], float b[2], float dest[2])
{
    dest[0] = maxf(a[0], b[0]);
    dest[1] = maxf(a[1], b[1]);
}

void vec2f_clamp(float a[2], float l[2], float u[2], float dest[2])
{
    dest[0] = clampf(a[0], l[0], u[0]);
    dest[1] = clampf(a[1], l[1], u[1]);
}

void vec2f_lerp(float a[2], float b[2], float t, float dest[2])
{
    dest[0] = lerpf(a[0], b[0], t);
    dest[1] = lerpf(a[1], b[1], t);
}

#include "../include/vec3f.h"

/*
    vec3f.c:    C source file for all float vec3 operations
*/

vec3f vec3f_init(float v[3])
{
    return (vec3f){v[0], v[1], v[2]};
}

void vec3f_copy(float src[3], float dest[3])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

vec3f vec3f_zero_new()
{
    return (vec3f){0, 0, 0};
}

void vec3f_zero(float v[3])
{
    v[0] = v[1] = v[2] = 0;
}

vec3f vec3f_set_s_new(float s)
{
    return (vec3f){s, s, s};
}

void vec3f_set_s(float v[3], float s)
{
    v[0] = v[1] = v[2] = s;
}

float vec3f_dot(float a[3], float b[3])
{
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

float vec3f_length(float v[3])
{
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

float vec3f_length_squared(float v[3])
{
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

void vec3f_normalize(float v[3])
{
    float inv_mag = 1.f / vec3f_length(v);
    v[0] *= inv_mag;
    v[1] *= inv_mag;
    v[2] *= inv_mag;
}

void vec3f_add(float a[3], float b[3], float dest[3])
{
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
}

void vec3f_sub(float a[3], float b[3], float dest[3])
{
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
}

void vec3f_adds(float a[3], float b, float dest[3])
{
    dest[0] = a[0] + b;
    dest[1] = a[1] + b;
    dest[2] = a[2] + b;
}

void vec3f_subs(float a[3], float b, float dest[3])
{
    dest[0] = a[0] - b;
    dest[1] = a[1] - b;
    dest[2] = a[2] - b;
}

void vec3f_scale(float v[3], float s, float dest[3])
{
    dest[0] = v[0] * s;
    dest[1] = v[1] * s;
    dest[2] = v[2] * s;
}

vec3f vec3f_add_new(float a[3], float b[3])
{
    return  (vec3f){    a[0] + b[0],
                        a[1] + b[1],
                        a[2] + b[2] };
}

vec3f vec3f_sub_new(float a[3], float b[3])
{
    return  (vec3f){    a[0] - b[0],
                        a[1] - b[1],
                        a[2] - b[2] };
}

vec3f vec3f_adds_new(float a[3], float b)
{
    return  (vec3f){    a[0] + b,
                        a[1] + b,
                        a[2] + b    };
}

vec3f vec3f_subs_new(float a[3], float b)
{
    return  (vec3f){    a[0] - b,
                        a[1] - b,
                        a[2] - b    };
}

vec3f vec3f_scale_new(float v[3], float s)
{
    return  (vec3f){    v[0] * s,
                        v[1] * s,
                        v[2] * s    };
}

void vec3f_mul(float a[3], float b[3], float dest[3])
{
    dest[0] = b[0] * a[0];
    dest[1] = b[1] * a[1];
    dest[2] = b[2] * a[2];
}

vec3f vec3f_mul_new(float a[3], float b[3])
{
    return  (vec3f){    b[0] * a[0],
                        b[1] * a[1],
                        b[2] * a[2] };
}

vec3f vec3f_min_new(float a[3], float b[3])
{
    return  (vec3f){    minf(a[0], b[0]),
                        minf(a[1], b[1]),
                        minf(a[2], b[2])    };
}

vec3f vec3f_max_new(float a[3], float b[3])
{
    return  (vec3f){    maxf(a[0], b[0]),
                        maxf(a[1], b[1]),
                        maxf(a[2], b[2])    };
}

vec3f vec3f_clamp_new(float a[3], float l[3], float u[3])
{
    return  (vec3f){    clampf(a[0], l[0], u[0]),
                        clampf(a[1], l[1], u[1]),
                        clampf(a[2], l[2], u[2])    };
}

vec3f vec3f_lerp_new(float a[3], float b[3], float t)
{
    return  (vec3f){    lerpf(a[0], b[0], t),
                        lerpf(a[1], b[1], t),
                        lerpf(a[2], b[2], t)    };
}

vec3f vec3f_normalize_new(float v[3])
{
    float inv_mag = 1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return (vec3f){ v[0]*inv_mag,
                    v[1]*inv_mag,
                    v[2]*inv_mag    };
}

void vec3f_min(float a[3], float b[3], float dest[3])
{
    dest[0] = minf(a[0], b[0]);
    dest[1] = minf(a[1], b[1]);
    dest[2] = minf(a[2], b[2]);
}

void vec3f_max(float a[3], float b[3], float dest[3])
{
    dest[0] = maxf(a[0], b[0]);
    dest[1] = maxf(a[1], b[1]);
    dest[2] = maxf(a[2], b[2]);
}

void vec3f_clamp(float a[3], float l[3], float u[3], float dest[3])
{
    dest[0] = clampf(a[0], l[0], u[0]);
    dest[1] = clampf(a[1], l[1], u[1]);
    dest[2] = clampf(a[2], l[2], u[2]);
}

void vec3f_lerp(float a[3], float b[3], float t, float dest[3])
{
    dest[0] = lerpf(a[0], b[0], t);
    dest[1] = lerpf(a[1], b[1], t);
    dest[2] = lerpf(a[2], b[2], t);
}

vec3f vec3f_cross_new(float a[3], float b[3])
{
    return  (vec3f){    +(a[1]*b[2] - a[2]*b[1]),
                        -(a[0]*b[2] - a[2]*b[0]),
                        +(a[0]*b[1] - a[1]*b[0])    };
}

void vec3f_cross(float a[3], float b[3], float dest[3])
{
    dest[0] = +(a[1]*b[2] - a[2]*b[1]);
    dest[1] = -(a[0]*b[2] - a[2]*b[0]);
    dest[2] = +(a[0]*b[1] - a[1]*b[0]);
}

vec3f vec3f_reflect_new(float v[3], float n[3])
{
    float cos_t = v[0]*n[0]+v[1]*n[1]+v[2]*n[2];
    return (vec3f){ v[0]-(2*cos_t*n[0]),
                    v[1]-(2*cos_t*n[1]),
                    v[2]-(2*cos_t*n[2])};
}

void vec3f_reflect(float v[3], float n[3], float dest[3])
{
    float cos_t = v[0]*n[0]+v[1]*n[1]+v[2]*n[2];
    dest[0] = v[0]-(2*cos_t*n[0]);
    dest[1] = v[1]-(2*cos_t*n[1]);
    dest[2] = v[2]-(2*cos_t*n[2]);
}
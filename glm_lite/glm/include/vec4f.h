#pragma once

/*
    vec4f.h:    Float Vector4 types and operations
*/

typedef union vec4f
{
    struct  {float w, x, y, z;};
    struct  {float r, g, b, a;};
    float   c[4];
}
vec4f;

#include "./common.h"

vec4f vec4f_init(float a[4]);
vec4f vec4f_zero_new();
vec4f vec4f_set_s_new(float s);

vec4f vec4f_add_new(float a[4], float b[4]);
vec4f vec4f_sub_new(float a[4], float b[4]);
vec4f vec4f_adds_new(float v[4], float s);
vec4f vec4f_subs_new(float v[4], float s);
vec4f vec4f_scale_new(float v[4], float s);
vec4f vec4f_mul_new(float a[4], float b[4]);
vec4f vec4f_min_new(float a[4], float b[4]);
vec4f vec4f_max_new(float a[4], float b[4]);
vec4f vec4f_clamp_new(float x[4], float l[4], float u[4]);
vec4f vec4f_lerp_new(float a[4], float b[4], float f);
vec4f vec4f_cubic_new(float a[4], float c);
vec4f vec4f_reflect_new(float v[4], float n[4]);
vec4f vec4f_normalize_new(float v[4]);

float vec4f_dot(float a[4], float b[4]);
float vec4f_length(float v[4]);
float vec4f_length_squared(float v[4]);

void print_vec4f(vec4f);
void vec4f_copy(float a[4], float b[4]);
void vec4f_zero(float v[4]);
void vec4f_set_s(float a[4], float s);
void vec4f_normalize(float a[4]);
void vec4f_add(float a[4], float b[4], float dest[4]);
void vec4f_sub(float a[4], float b[4], float dest[4]);
void vec4f_adds(float v[4], float s, float dest[4]);
void vec4f_subs(float v[4], float s, float dest[4]);
void vec4f_scale(float v[4], float s, float dest[4]);
void vec4f_mul(float a[4], float b[4], float dest[4]);
void vec4f_min(float a[4], float b[4], float dest[4]);
void vec4f_max(float a[4], float b[4], float dest[4]);
void vec4f_clamp(float x[4], float l[4], float u[4], float dest[4]);
void vec4f_lerp(float a[4], float b[4], float f, float dest[4]);
void vec4f_cubic(float v[4], float s);

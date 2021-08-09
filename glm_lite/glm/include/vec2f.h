#pragma once

/*
    vec2f.h:    Float Vector2 types and operations
*/

typedef union vec2f
{
    struct  {float x, y;};
    struct  {float u, v;};
    float   c[2];
}
vec2f;

#include "./common.h"

vec2f vec2f_init(float v[2]);
vec2f vec2f_zero_new();
vec2f vec2f_set_s_new(float s);

vec2f vec2f_add_new(float a[2], float b[2]);
vec2f vec2f_sub_new(float a[2], float b[2]);
vec2f vec2f_adds_new(float v[2], float s);
vec2f vec2f_subs_new(float v[2], float s);
vec2f vec2f_scale_new(float v[2], float s);
vec2f vec2f_mul_new(float a[2], float b[2]);
vec2f vec2f_min_new(float a[2], float b[2]);
vec2f vec2f_max_new(float a[2], float b[2]);
vec2f vec2f_clamp_new(float x[2], float l[2], float u[2]);
vec2f vec2f_lerp_new(float a[2], float b[2], float f);
vec2f vec2f_reflect_new(float v[2], float n[2]);
vec2f vec2f_normalize_new(float v[2]);

float vec2f_dot(float a[2], float b[2]);
float vec2f_length(float v[2]);
float vec2f_length_squared(float v[2]);

void print_vec2f(vec2f);
void vec2f_copy(float a[2], float b[2]);
void vec2f_zero(float v[2]);
void vec2f_set_s(float v[2], float s);
void vec2f_normalize(float v[2]);
void vec2f_add(float a[2], float b[2], float dest[2]);
void vec2f_sub(float a[2], float b[2], float dest[2]);
void vec2f_adds(float v[2], float s, float dest[2]);
void vec2f_subs(float v[2], float s, float dest[2]);
void vec2f_scale(float v[2], float s, float dest[2]);
void vec2f_mul(float a[2], float b[2], float dest[2]);
void vec2f_min(float a[2], float b[2], float dest[2]);
void vec2f_max(float a[2], float b[2], float dest[2]);
void vec2f_clamp(float x[2], float l[2], float u[2], float dest[2]);
void vec2f_lerp(float a[2], float b[2], float f, float dest[2]);
void vec2f_reflect(float v[2], float n[2], float dest[2]);
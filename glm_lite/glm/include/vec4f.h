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

vec4f vec4f_init(float[4]);
vec4f vec4f_zero_new();
vec4f vec4f_set_s_new(float);

vec4f vec4f_add_new(float[4], float[4]);
vec4f vec4f_sub_new(float[4], float[4]);
vec4f vec4f_adds_new(float[4], float);
vec4f vec4f_subs_new(float[4], float);
vec4f vec4f_scale_new(float[4], float);
vec4f vec4f_mul_new(float[4], float[4]);
vec4f vec4f_min_new(float[4], float[4]);
vec4f vec4f_max_new(float[4], float[4]);
vec4f vec4f_clamp_new(float[4], float[4], float[4]);
vec4f vec4f_lerp_new(float[4], float[4], float, float[4]);
vec4f vec4f_cubic_new(float[4], float);

float vec4f_dot(float[4], float[4]);
float vec4f_length(float[4]);

void print_vec4f(vec4f);
void vec4f_copy(float[4], float[4]);
void vec4f_zero(float[4]);
void vec4f_set_s(float[4], float);
void vec4f_normalize(float[4]);
void vec4f_add(float[4], float[4]);
void vec4f_sub(float[4], float[4]);
void vec4f_adds(float[4], float);
void vec4f_subs(float[4], float);
void vec4f_scale(float[4], float);
void vec4f_mul(float[4], float[4]);
void vec4f_min(float[4], float[4], float[4]);
void vec4f_max(float[4], float[4], float[4]);
void vec4f_clamp(float[4], float[4], float[4], float[4]);
void vec4f_lerp(float[4], float[4], float, float[4]);
void vec4f_cubic(float[4], float);

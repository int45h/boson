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

vec2f vec2f_init(float[2]);
vec2f vec2f_zero_new();
vec2f vec2f_set_s_new(float);

vec2f vec2f_add_new(float[2], float[2]);
vec2f vec2f_sub_new(float[2], float[2]);
vec2f vec2f_adds_new(float[2], float);
vec2f vec2f_subs_new(float[2], float);
vec2f vec2f_scale_new(float[2], float);
vec2f vec2f_mul_new(float[2], float[2]);
vec2f vec2f_min_new(float[2], float[2]);
vec2f vec2f_max_new(float[2], float[2]);
vec2f vec2f_clamp_new(float[2], float[2], float[2]);
vec2f vec2f_lerp_new(float[2], float[2], float, float[2]);

float vec2f_dot(float[2], float[2]);
float vec2f_length(float[2]);

void print_vec2f(vec2f);
void vec2f_copy(float[2], float[2]);
void vec2f_zero(float[2]);
void vec2f_set_s(float[2], float);
void vec2f_normalize(float[2]);
void vec2f_add(float[2], float[2]);
void vec2f_sub(float[2], float[2]);
void vec2f_adds(float[2], float);
void vec2f_subs(float[2], float);
void vec2f_scale(float[2], float);
void vec2f_mul(float[2], float[2]);
void vec2f_min(float[2], float[2], float[2]);
void vec2f_max(float[2], float[2], float[2]);
void vec2f_clamp(float[2], float[2], float[2], float[2]);
void vec2f_lerp(float[2], float[2], float, float[2]);

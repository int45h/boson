#pragma once

/*
    vec3f.h:    Float Vector3 types and operations
*/

typedef union vec3f
{
    struct  {float x, y, z;};
    struct  {float r, g, b;};
    float   c[3];
}
vec3f;

#include "./common.h"

vec3f vec3f_init(float[3]);
vec3f vec3f_zero_new();
vec3f vec3f_set_s_new(float);

vec3f vec3f_add_new(float[3], float[3]);
vec3f vec3f_sub_new(float[3], float[3]);
vec3f vec3f_adds_new(float[3], float);
vec3f vec3f_subs_new(float[3], float);
vec3f vec3f_scale_new(float[3], float);
vec3f vec3f_mul_new(float[3], float[3]);
vec3f vec3f_min_new(float[3], float[3]);
vec3f vec3f_max_new(float[3], float[3]);
vec3f vec3f_clamp_new(float[3], float[3], float[3]);
vec3f vec3f_lerp_new(float[3], float[3], float, float[3]);
vec3f vec3f_cross_new(float[3], float[3]);

float vec3f_dot(float[3], float[3]);
float vec3f_length(float[3]);

void print_vec3f(vec3f);
void vec3f_copy(float[3], float[3]);
void vec3f_zero(float[3]);
void vec3f_set_s(float[3], float);
void vec3f_normalize(float[3]);
void vec3f_add(float[3], float[3]);
void vec3f_sub(float[3], float[3]);
void vec3f_adds(float[3], float);
void vec3f_subs(float[3], float);
void vec3f_scale(float[3], float);
void vec3f_mul(float[3], float[3]);
void vec3f_min(float[3], float[3], float[3]);
void vec3f_max(float[3], float[3], float[3]);
void vec3f_clamp(float[3], float[3], float[3], float[3]);
void vec3f_lerp(float[3], float[3], float, float[3]);
void vec3f_cross(float[3], float[3], float[3]);

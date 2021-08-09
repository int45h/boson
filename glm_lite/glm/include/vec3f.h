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

vec3f vec3f_init(float v[3]);
vec3f vec3f_zero_new();
vec3f vec3f_set_s_new(float s);

vec3f vec3f_add_new(float a[3], float b[3]);
vec3f vec3f_sub_new(float a[3], float b[3]);
vec3f vec3f_adds_new(float a[3], float s);
vec3f vec3f_subs_new(float a[3], float s);
vec3f vec3f_scale_new(float a[3], float s);
vec3f vec3f_mul_new(float a[3], float b[3]);
vec3f vec3f_min_new(float a[3], float b[3]);
vec3f vec3f_max_new(float a[3], float b[3]);
vec3f vec3f_clamp_new(float x[3], float l[3], float u[3]);
vec3f vec3f_lerp_new(float a[3], float b[3], float f);
vec3f vec3f_cross_new(float a[3], float b[3]);
vec3f vec3f_reflect_new(float v[3], float n[3]);
vec3f vec3f_normalize_new(float v[3]);

float vec3f_dot(float a[3], float b[3]);
float vec3f_length(float v[3]);
float vec3f_length_squared(float v[3]);

void print_vec3f(vec3f);
void vec3f_copy(float a[3], float b[3]);
void vec3f_zero(float v[3]);
void vec3f_set_s(float v[3], float s);
void vec3f_normalize(float v[3]);
void vec3f_add(float a[3], float[3], float dest[3]);
void vec3f_sub(float a[3], float[3], float dest[3]);
void vec3f_adds(float v[3], float s, float dest[3]);
void vec3f_subs(float v[3], float s, float dest[3]);
void vec3f_scale(float v[3], float s, float dest[3]);
void vec3f_mul(float a[3], float b[3], float dest[3]);
void vec3f_min(float a[3], float b[3], float dest[3]);
void vec3f_max(float a[3], float b[3], float dest[3]);
void vec3f_clamp(float x[3], float l[3], float u[3], float dest[3]);
void vec3f_lerp(float a[3], float b[3], float f, float dest[3]);
void vec3f_cross(float a[3], float b[3], float dest[3]);
void vec3f_reflect(float v[3], float n[3], float dest[3]);
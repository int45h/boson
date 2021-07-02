#pragma once

/*
    quatf.h:    Float quaternion types and operations
*/

#include "./mat4f.h"
#include "./mat3f.h"
#include "./vec4f.h"
#include "./vec3f.h"
#include "./common.h"

typedef union quatf
{
    struct  {float i, j, k, r;};
    struct  {float x, y, z, w;};
    struct  {vec3f ijk; float real;};
    float   c[4];
}
quatf;

#define QUATF_IDENTITY  (quatf){0, 0, 0, 1}

void print_quatf(quatf);

quatf quatf_init(float, float, float, float);
quatf quatf_init_angle_new(float, float, float, float);
quatf quatf_scale_new(float[4], float);
quatf quatf_normalize_new(float[4]);
quatf quatf_conjugate_new(float[4]);
quatf quatf_add_new(float[4], float[4]);
quatf quatf_sub_new(float[4], float[4]);
quatf quatf_adds_new(float[4], float);
quatf quatf_subs_new(float[4], float);
quatf quatf_mul(float[4], float[4]);
quatf quatf_euler_new(float, float, float);
quatf quatf_lookat_new(float src[3], float dest[3]);

mat4f quatf_to_mat4f_new(float[4]);
mat4f quatf_to_mat4ft_new(float[4]);
mat4f quatf_to_look_mat4f_new(float[3], float[4]);
mat4f quatf_to_look_mat4ft_new(float[3], float[4]);

mat3f quatf_to_mat3f_new(float[4]);
mat3f quatf_to_mat3ft_new(float[4]);

vec3f quatf_mul_vec_new(float[4], float[3]);
vec3f quatf_to_euler_new(float[4]);

float quatf_norm(float[4]);
float quatf_dot(float[4], float[4]);
float quatf_angle(float[4]);

void quatf_init_angle(float, float, float, float, float[4]);
void quatf_copy(float[4], float[4]);
void quatf_scale(float[4], float);
void quatf_normalize(float[4]);
void quatf_conjugate(float[4]);
void quatf_add(float[4], float[4]);
void quatf_sub(float[4], float[4]);
void quatf_adds(float[4], float);
void quatf_subs(float[4], float);
void quatf_mul_vec(float[4], float[3], float[3]);
void quatf_euler(float, float, float, float[4]);
void quatf_to_euler(float[4], float[3]);
void quatf_to_mat4f(float[4], float[16]);
void quatf_to_mat4ft(float[4], float[16]);
void quatf_to_mat3f(float[4], float[9]);
void quatf_to_mat3ft(float[4], float[9]);
void quatf_to_look_mat4f(float[3], float[4], float[16]);
void quatf_to_look_mat4ft(float[3], float[4], float[16]);
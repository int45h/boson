#pragma once

/*
    mat4f.h: Float Matrix 4x4 types and operations
*/

#include "./vec4f.h"
#include "./vec3f.h"    

typedef union mat4f
{
    struct  {float  a, b, c, d,
                    e, f, g, h,
                    i, j, k, l,
                    m, n, o, p;};
    vec4f row[4];
    float ij[4][4];
    float comp[16];
}
mat4f;

#define MAT4F_IDENTITY  (mat4f){    1, 0, 0, 0,\
                                    0, 1, 0, 0,\
                                    0, 0, 1, 0,\
                                    0, 0, 0, 1  }

#define FLOAT_IDENTITY_MATRIX(m)    {   m[0]  = m[5]  = m[10] = m[15] = 1;\
                                        m[1]  = m[2]  = m[3]  = m[4]  =   \
                                        m[6]  = m[7]  = m[8]  = m[9]  =   \
                                        m[11] = m[12] = m[13] = m[14] = 0;  }

mat4f mat4f_init(   float, float, float, float,
                    float, float, float, float,
                    float, float, float, float,
                    float, float, float, float  );
mat4f mat4f_zero();
mat4f mat4f_mul_new(float[16], float[16]);
mat4f mat4f_inverse_new(float[16]);
mat4f mat4f_projection_new(float, float, float, float);
mat4f mat4ft_projection_new(float, float, float, float);
mat4f mat4f_translate_new(float[3]);
mat4f mat4ft_translate_new(float[3]);
mat4f mat4f_scale_new(float[3], float[3]);
mat4f mat4f_look_at_new(float from[3], float to[3]);
mat4f mat4ft_look_at_new(float from[3], float to[3]);
mat4f mat4f_rotation_euler_new(float, float, float);
mat4f mat4ft_rotation_euler_new(float, float, float);

vec4f mat4f_mul_vec_new(float[4], float[16]);

float mat4f_det(float[16]);
float mat4f_trace(float[16]);

void print_mat4f(mat4f m);
void mat4f_ucopy(float[16], float[16]);
void mat4f_transpose(float[16]);
void mat4f_mul(float[16], float[16]);
void mat4f_mul_vec(float[4], float[16]);
void mat4f_mul_scalar(float, float[16]);
void mat4f_inverse(float[16]);
void mat4f_set_row(float[4], float[16], int);
void mat4f_set_col(float[4], float[16], int);
void mat4f_projection(float, float, float, float, float[16]);
void mat4ft_projection(float, float, float, float, float[16]);
void mat4f_translate(float[3], float[16]);
void mat4ft_translate(float[3], float[16]);
void mat4f_scale(float[3], float[3], float[16]);
void mat4f_look_at(float from[3], float to[3], float m[16]);
void mat4ft_look_at(float from[3], float to[3], float m[16]);
void mat4f_rotation_euler(float, float, float, float[16]);
void mat4ft_rotation_euler(float, float, float, float[16]);

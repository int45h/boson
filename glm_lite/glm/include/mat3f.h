#pragma once

/*
    mat3f.h: Float Matrix 3x3 types and operations
*/

#include "./vec3f.h"

typedef union mat3f
{
    struct  {float  a, b, c,
                    d, e, f,
                    g, h, i;};

    vec3f row[3];
    float ij[3][3];
    float comp[9];
}
mat3f;

#define MAT3F_IDENTITY (mat3f){     1, 0, 0,\
                                    0, 1, 0,\
                                    0, 0, 1     }

mat3f mat3f_init(   float, float, float, 
                    float, float, float,
                    float, float, float );
mat3f mat3f_zero_new();
mat3f mat3f_mul_new(float[9], float[9]);

vec3f mat3f_mul_vec_new(float[3], float[9]);

float mat3f_det(float[9]);
float mat3f_trace(float[9]);

void print_mat3f(mat3f m);
void mat3f_zero(float[9]);
void mat3f_ucopy(float[9], float[9]);
void mat3f_transpose(float[9]);
void mat3f_scale(float, float[9]);
void mat3f_mul(float[9], float[9]);
void mat3f_mul_vec(float[3], float[9]);
void mat3f_inverse(float[9]);
void mat3f_set_row(float[3], float[9], int);
void mat3f_set_col(float[3], float[9], int);
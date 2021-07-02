#pragma once

/*
    mat2f.h: Float Matrix 2x2 types and operations
*/

#include "./vec2f.h"

typedef union mat2f
{
    struct  {float  a, b, 
                    c, d;};

    vec2f row[2];
    float m[4];
    float ij[2][2];
}
mat2f;

#define MAT2F_IDENTITY (mat2f){     1, 0,\
                                    0, 1    }

mat2f mat2f_init(   float, float, 
                    float, float    );
mat2f mat2f_zero_new();
mat2f mat2f_mul_new(float[4], float[4]);

vec2f vec2f_set_new(float[2]);
vec2f mat2f_mul_vec_new(float[2], float[4]);

float mat2f_det(float[4]);
float mat2f_trace(float[4]);

void print_mat2f(mat2f m);
void mat2f_zero(float[4]);
void mat2f_ucopy(float [4], float [4]);
void mat2f_transpose(float [4]);
void mat2f_scale(float, float[4]);
void mat2f_mul(float[4], float[4]);
void mat2f_mul_vec(float[2], float[4]);
void mat2f_inverse(float[4]);
void mat2f_set_row(float[2], float[4], int);
void mat2f_set_col(float[2], float[4], int);
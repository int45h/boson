#include "../include/mat2f.h"
#include <stdio.h>
/*
    mat2f.c:    C source file for all float mat2 operations
*/

void print_mat2f(mat2f m)
{
    printf("{\t%f, %f\n", m.a, m.b);
    printf("\t%f, %f\t}\n", m.c, m.d);
}

void mat2f_ucopy(float src[4], float dest[4])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}

void mat2f_transpose(float m[4])
{
    float   a = m[0],
            b = m[1],
            c = m[2],
            d = m[3];

    m[1] = c;
    m[2] = b;
}

mat2f mat2f_init(   float a, float b, 
                    float c, float d    )
{
    return  (mat2f){    a, b,
                        c, d    };
}

float mat2f_det(float m[4])
{
    return (m[0] * m[3]) - (m[1] * m[2]);
}

mat2f mat2f_zero_new()
{
    return  (mat2f){    0, 0,
                        0, 0    };
}

void mat2f_zero(float m[4])
{
    m[0] = m[1] = m[2] = m[3] = 0;
}

void mat2f_scale(float s, float m[4])
{
    m[0] *= s;
    m[1] *= s;
    m[2] *= s;
    m[3] *= s;
}

void mat2f_mul(float a[4], float b[4])
{
    float   b_0 = b[0],
            b_1 = b[1],
            b_2 = b[2],
            b_3 = b[3];
            
    b[0] = (a[0] * b_0) + (a[1] * b_2);
    b[1] = (a[0] * b_1) + (a[1] * b_3);
    b[2] = (a[2] * b_0) + (a[3] * b_2);
    b[3] = (a[2] * b_1) + (a[3] * b_3);
}

mat2f mat2f_mul_new(float a[4], float b[4])
{
    mat2f m;
    m.a = (a[0] * b[0]) + (a[1] * b[2]);
    m.b = (a[0] * b[1]) + (a[1] * b[3]);
    m.c = (a[2] * b[0]) + (a[3] * b[2]);
    m.d = (a[2] * b[1]) + (a[3] * b[3]);
    return m;
}

void mat2f_mul_vec(float v[2], float m[4])
{
    float   v_0 = v[0],
            v_1 = v[1];

    v[0] = (v_0 * m[0]) + (v_1 * m[2]);
    v[1] = (v_0 * m[1]) + (v_1 * m[3]);
}

vec2f vec2f_set_new(float v[2])
{
    return (vec2f){v[0], v[1]};
}

vec2f mat2f_mul_vec_new(float v[2], float m[4])
{
    vec2f v_out;
    v_out.x = (v[0] * m[0]) + (v[1] * m[2]);
    v_out.y = (v[0] * m[1]) + (v[1] * m[3]);
    return v_out;
}

void mat2f_inverse(float m[4])
{
    float   inv_det = (float)1.f / mat2f_det(m),
            m_a     = +m[3] * inv_det, m_b     = -m[1] * inv_det,
            m_c     = -m[2] * inv_det, m_d     = +m[0] * inv_det;

    m[0] = m_a;
    m[1] = m_b;
    m[2] = m_c;
    m[3] = m_d;
}

float mat2f_trace(float m[4])
{
    return m[0]+m[3];
}

void mat2f_set_col(float v[2], float m[4], int j)
{
    m[2*0 + j]  = v[0];
    m[2*1 + j]  = v[1];
}

void mat2f_set_row(float v[2], float m[4], int i)
{
    m[2*i + 0]  = v[0];
    m[2*i + 1]  = v[1];
}
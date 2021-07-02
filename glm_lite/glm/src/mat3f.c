#include "../include/mat3f.h"
#include <stdio.h>
void print_mat3f(mat3f m)
{
    printf("{\t%f, %f, %f\n",   m.a, 
                                m.b,
                                m.c);
    printf("\t%f, %f, %f\n",    m.d, 
                                m.e,
                                m.f);
    printf("\t%f, %f, %f}\n",   m.g, 
                                m.h,
                                m.i);
}

void mat3f_ucopy(float src[9], float dest[9])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
    dest[4] = src[4];
    dest[5] = src[5];
    dest[6] = src[6];
    dest[7] = src[7];
    dest[8] = src[8];   
}

void mat3f_transpose(float m[9])
{
    float   a = m[0],
            b = m[1],
            c = m[2],
            d = m[3],
            e = m[4],
            f = m[5],
            g = m[6],
            h = m[7],
            i = m[8];

    m[1] = d;
    m[3] = b;
    m[2] = g;
    m[6] = c;
    m[5] = h;
    m[7] = f;
}

mat3f mat3f_transpose_new(float m[9])
{
    return  (mat3f){    m[0], m[3], m[6],
                        m[1], m[4], m[7],
                        m[2], m[5], m[8]    };
}

mat3f mat3f_init(   float a, float b, float c, 
                    float d, float e, float f,
                    float g, float h, float i   )
{
    return  (mat3f){    a, b, c,
                        d, e, f,
                        g, h, i };
}

float mat3f_det(float m[9])
{
    return  (m[0] * (m[4]*m[8] - m[5]*m[7])) -
            (m[1] * (m[3]*m[8] - m[5]*m[6])) +
            (m[2] * (m[3]*m[7] - m[4]*m[6]));
}

mat3f mat3f_zero_new()
{
    mat3f m;
    m.a = m.b = m.c =
    m.d = m.e = m.f = 
    m.g = m.h = m.i = 0;
    return m;
}

void mat3f_zero(float m[9])
{
    m[0] = m[1] = m[2] =
    m[3] = m[4] = m[5] = 
    m[6] = m[7] = m[8] = 0;
}

void mat3f_scale(float s, float m[9])
{
    m[0] *= s;
    m[1] *= s;
    m[2] *= s;
    m[3] *= s;
    m[4] *= s;
    m[5] *= s;
    m[6] *= s;
    m[7] *= s;
    m[8] *= s;
}

mat3f mat3f_scale_new(float s, float m[9])
{
    return  (mat3f){    m[0]*s, m[1]*s, m[2]*s,
                        m[3]*s, m[4]*s, m[5]*s,
                        m[6]*s, m[7]*s, m[8]*s  };
}

void mat3f_mul(float a[9], float b[9])
{
    float   b_0 = b[0],
            b_1 = b[1],
            b_2 = b[2],
            b_3 = b[3],
            b_4 = b[4],
            b_5 = b[5],
            b_6 = b[6],
            b_7 = b[7],
            b_8 = b[8];

    b[0] = (a[0]*b_0 + a[1]*b_3 + a[2]*b_6);
    b[1] = (a[0]*b_1 + a[1]*b_4 + a[2]*b_7);
    b[2] = (a[0]*b_2 + a[1]*b_5 + a[2]*b_8);
    
    b[3] = (a[3]*b_0 + a[4]*b_3 + a[5]*b_6);
    b[4] = (a[3]*b_1 + a[4]*b_4 + a[5]*b_7);
    b[5] = (a[3]*b_2 + a[4]*b_5 + a[5]*b_8);

    b[6] = (a[6]*b_0 + a[7]*b_3 + a[8]*b_6);
    b[7] = (a[6]*b_1 + a[7]*b_4 + a[8]*b_7);
    b[8] = (a[6]*b_2 + a[7]*b_5 + a[8]*b_8);
}

mat3f mat3f_mul_new(float a[9], float b[9])
{
    mat3f m;
    m.comp[0] = (a[0]*b[0] + a[1]*b[3] + a[2]*b[6]);
    m.comp[1] = (a[0]*b[1] + a[1]*b[4] + a[2]*b[7]);
    m.comp[2] = (a[0]*b[2] + a[1]*b[5] + a[2]*b[8]);
    
    m.comp[3] = (a[3]*b[0] + a[4]*b[3] + a[5]*b[6]);
    m.comp[4] = (a[3]*b[1] + a[4]*b[4] + a[5]*b[7]);
    m.comp[5] = (a[3]*b[2] + a[4]*b[5] + a[5]*b[8]);

    m.comp[6] = (a[6]*b[0] + a[7]*b[3] + a[8]*b[6]);
    m.comp[7] = (a[6]*b[1] + a[7]*b[4] + a[8]*b[7]);
    m.comp[8] = (a[6]*b[2] + a[7]*b[5] + a[8]*b[8]);
    return m;
}

void mat3f_mul_vec(float v[3], float m[9])
{
    float   v_0 = v[0],
            v_1 = v[1],
            v_2 = v[2];

    v[0] = (v_0 * m[0]) + (v_1 * m[3]) + (v_2 * m[6]);
    v[1] = (v_0 * m[1]) + (v_1 * m[4]) + (v_2 * m[7]);
    v[2] = (v_0 * m[2]) + (v_1 * m[5]) + (v_2 * m[8]);
}

vec3f mat3f_mul_vec_new(float v[3], float m[9])
{
    vec3f v_out;
    v_out.c[0] = (v[0] * m[0]) + (v[1] * m[3]) + (v[2] * m[6]);
    v_out.c[1] = (v[0] * m[1]) + (v[1] * m[4]) + (v[2] * m[7]);
    v_out.c[2] = (v[0] * m[2]) + (v[1] * m[5]) + (v[2] * m[8]);
    return v_out;
}

void mat3f_inverse(float m[9])
{
    float   inv_det = 1.f / mat3f_det(m),
            a       = inv_det * (m[4]*m[8] - m[5]*m[7]),
            b       = inv_det * (m[3]*m[8] - m[5]*m[6]),
            c       = inv_det * (m[3]*m[7] - m[4]*m[6]),

            d       = inv_det * (m[1]*m[8] - m[2]*m[7]),
            e       = inv_det * (m[0]*m[8] - m[2]*m[6]),
            f       = inv_det * (m[0]*m[7] - m[1]*m[6]),
            
            g       = inv_det * (m[1]*m[5] - m[2]*m[4]),
            h       = inv_det * (m[0]*m[5] - m[2]*m[3]),
            i       = inv_det * (m[0]*m[4] - m[1]*m[3]);

    m[0] = +a;  m[1] = -d;  m[2] = +g;  
    m[3] = -b;  m[4] = +e;  m[5] = -h;  
    m[6] = +c;  m[7] = -f;  m[8] = +i;  
}

mat3f mat3f_inverse_new(float m[9])
{
    float   inv_det = 1.f / mat3f_det(m),
            a       = inv_det * (m[4]*m[8] - m[5]*m[7]),
            b       = inv_det * (m[3]*m[8] - m[5]*m[6]),
            c       = inv_det * (m[3]*m[7] - m[4]*m[6]),

            d       = inv_det * (m[1]*m[8] - m[2]*m[7]),
            e       = inv_det * (m[0]*m[8] - m[2]*m[6]),
            f       = inv_det * (m[0]*m[7] - m[1]*m[6]),
            
            g       = inv_det * (m[1]*m[5] - m[2]*m[4]),
            h       = inv_det * (m[0]*m[5] - m[2]*m[3]),
            i       = inv_det * (m[0]*m[4] - m[1]*m[3]);

    return (mat3f){ +a, -d, +g,
                    -b, +e, -h,
                    +c, -f, +i  };
}

float mat3f_trace(float m[9])
{
    return  m[0]+m[4]+m[8];
}

void mat3f_set_col(float v[3], float m[9], int j)
{
    m[3*0 + j]  = v[0];
    m[3*1 + j]  = v[1];
    m[3*2 + j]  = v[2];
}

void mat3f_set_row(float v[3], float m[9], int i)
{
    m[3*i + 0]  = v[0];
    m[3*i + 1]  = v[1];
    m[3*i + 2]  = v[2];
}
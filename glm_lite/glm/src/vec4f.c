#include "../include/vec4f.h"

/*
    vec4f.c:    C source file for all float vec3 operations
*/

vec4f vec4f_init(float v[4])
{
    return (vec4f){v[0], v[1], v[2], v[3]};
}

void vec4f_copy(float src[4], float dest[4])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}

vec4f vec4f_zero_new()
{
    return (vec4f){0, 0, 0, 0};
}

void vec4f_zero(float v[4])
{
    v[0] = v[1] = v[2] = v[3] = 0;
}

vec4f vec4f_set_s_new(float s)
{
    return (vec4f){s, s, s, s};
}

void vec4f_set_s(float v[4], float s)
{
    v[0] = v[1] = v[2] = v[3] = s;
}

float vec4f_dot(float a[4], float b[4])
{
    return  (a[0] * b[0]) + 
            (a[1] * b[1]) + 
            (a[2] * b[2]) + 
            (a[3] * b[3]);
}

float vec4f_length(float v[4])
{
    return sqrt(    v[0]*v[0] + 
                    v[1]*v[1] + 
                    v[2]*v[2] + 
                    v[3]*v[3]   );
}

float vec4f_length_squared(float v[4])
{
    return v[0]*v[0] + 
           v[1]*v[1] + 
           v[2]*v[2] + 
           v[3]*v[3];
}

void vec4f_normalize(float v[4])
{
    float inv_mag = 1.f / vec4f_length(v);
    v[0] *= inv_mag;
    v[1] *= inv_mag;
    v[2] *= inv_mag;
    v[3] *= inv_mag;
}

void vec4f_add(float a[4], float b[4], float dest[4])
{
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    dest[3] = a[3] + b[3];
}

void vec4f_sub(float a[4], float b[4], float dest[4])
{
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    dest[3] = a[3] - b[3];
}

void vec4f_adds(float a[4], float b, float dest[4])
{
    dest[0] = a[0] + b;
    dest[1] = a[1] + b;
    dest[2] = a[2] + b;
    dest[3] = a[3] + b;
}

void vec4f_subs(float a[4], float b, float dest[4])
{
    dest[0] = a[0] - b;
    dest[1] = a[1] - b;
    dest[2] = a[2] - b;
    dest[3] = a[3] - b;
}

void vec4f_scale(float v[4], float s, float dest[4])
{
    dest[0] = v[0] * s;
    dest[1] = v[1] * s;
    dest[2] = v[2] * s;
    dest[3] = v[3] * s;
}

vec4f vec4f_add_new(float a[4], float b[4])
{
    return  (vec4f){    a[0] + b[0],
                        a[1] + b[1],
                        a[2] + b[2],
                        a[3] + b[3] };
}

vec4f vec4f_sub_new(float a[4], float b[4])
{
    return  (vec4f){    a[0] - b[0],
                        a[1] - b[1],
                        a[2] - b[2],
                        a[3] - b[3] };
}

vec4f vec4f_adds_new(float a[4], float b)
{
    return  (vec4f){    a[0] + b,
                        a[1] + b,
                        a[2] + b,
                        a[3] + b    };
}

vec4f vec4f_subs_new(float a[4], float b)
{
    return  (vec4f){    a[0] - b,
                        a[1] - b,
                        a[2] - b,
                        a[3] - b    };
}

vec4f vec4f_scale_new(float v[4], float s)
{
    return  (vec4f){    v[0] * s,
                        v[1] * s,
                        v[2] * s,
                        v[3] * s    };
}

void vec4f_mul(float a[4], float b[4], float dest[4])
{
    dest[0] = b[0] * a[0];
    dest[1] = b[1] * a[1];
    dest[2] = b[2] * a[2];
    dest[3] = b[3] * a[3];
}

vec4f vec4f_mul_new(float a[4], float b[4])
{
    return  (vec4f){    b[0] * a[0],
                        b[1] * a[1],
                        b[2] * a[2],
                        b[3] * a[3] };
}

vec4f vec4f_min_new(float a[4], float b[4])
{
    return  (vec4f){    minf(a[0], b[0]),
                        minf(a[1], b[1]),
                        minf(a[2], b[2]),
                        minf(a[3], b[3])    };
}

vec4f vec4f_max_new(float a[4], float b[4])
{
    return  (vec4f){    maxf(a[0], b[0]),
                        maxf(a[1], b[1]),
                        maxf(a[2], b[2]),
                        maxf(a[3], b[3])    };
}

vec4f vec4f_clamp_new(float a[4], float l[4], float u[4])
{
    return  (vec4f){    clampf(a[0], l[0], u[0]),
                        clampf(a[1], l[1], u[1]),
                        clampf(a[2], l[2], u[2]),
                        clampf(a[3], l[3], u[3])    };
}

vec4f vec4f_lerp_new(float a[4], float b[4], float t)
{
    return  (vec4f){    lerpf(a[0], b[0], t),
                        lerpf(a[1], b[1], t),
                        lerpf(a[2], b[2], t),
                        lerpf(a[3], b[3], t)    };
}

vec4f vec4f_normalize_new(float v[3])
{
    float inv_mag = 1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
    return (vec4f){ v[0]*inv_mag,
                    v[1]*inv_mag,
                    v[2]*inv_mag,
                    v[3]*inv_mag    };
}

vec4f vec4f_reflect_new(float v[4], float n[4])
{
    float cos_t = v[0]*n[0]+v[1]*n[1]+v[2]*n[2]+v[3]*n[3];
    return (vec4f){ v[0]-(2*cos_t*n[0]),
                    v[1]-(2*cos_t*n[1]),
                    v[2]-(2*cos_t*n[2]),
                    v[3]-(2*cos_t*n[3])};
}

void vec4f_min(float a[4], float b[4], float dest[4])
{
    dest[0] = minf(a[0], b[0]);
    dest[1] = minf(a[1], b[1]);
    dest[2] = minf(a[2], b[2]);
    dest[3] = minf(a[3], b[3]);
}

void vec4f_max(float a[4], float b[4], float dest[4])
{
    dest[0] = maxf(a[0], b[0]);
    dest[1] = maxf(a[1], b[1]);
    dest[2] = maxf(a[2], b[2]);
    dest[2] = maxf(a[3], b[3]);    
}

void vec4f_clamp(float a[4], float l[4], float u[4], float dest[4])
{
    dest[0] = clampf(a[0], l[0], u[0]);
    dest[1] = clampf(a[1], l[1], u[1]);
    dest[2] = clampf(a[2], l[2], u[2]);
    dest[3] = clampf(a[3], l[3], u[3]);
}

void vec4f_lerp(float a[4], float b[4], float t, float dest[4])
{
    dest[0] = lerpf(a[0], b[0], t);
    dest[1] = lerpf(a[1], b[1], t);
    dest[2] = lerpf(a[2], b[2], t);
    dest[3] = lerpf(a[3], b[3], t);
}

void vec4f_cubic(float v[4], float s)
{
    float ss = s * s;

    v[0] = ss * s;
    v[1] = ss;
    v[2] = s;
    v[3] = 1;
}

void vec4f_reflect(float v[3], float n[3], float dest[4])
{
    float cos_t = v[0]*n[0]+v[1]*n[1]+v[2]*n[2]+v[3]*n[3];
    dest[0] = v[0]-(2*cos_t*n[0]);
    dest[1] = v[1]-(2*cos_t*n[1]);
    dest[2] = v[2]-(2*cos_t*n[2]);
    dest[3] = v[3]-(2*cos_t*n[3]);
}

vec4f vec4f_cubic_new(float v[4], float s)
{
    float ss = s * s;
    return  (vec4f){    ss * s,
                        ss,
                        s,
                        1       };
}
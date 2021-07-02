#pragma once

/* 
    fast_math.h:    A series of helper functions to do quick and dirty approximations of 
                    traditionally slow math functions
*/

/* Symbols so that functions from this library can be defined separately if not included */
#ifndef _FAST_MATH_INCLUDED 
#define _FAST_MATH_INCLUDED
#endif

#if defined(__amd64__) || defined(__x86_64__)
    #include <x86intrin.h>
#else
    #error "Error: this lib only supports amd64 CPUs right now!"
#endif

#include <math.h>

/* Fast floor function */
static inline int floor_x86(register float x)
{
    __asm__
    (
        "cvttss2si  %1, %0"
        : "=r" (x) : "x" (x)
    );
}

/* AVX implementation of inverse sqrt (Only works on x86, circa Q1 2011+) */
static inline float rsqrt_avx(register float x)
{
    __asm__ 
    (
        "vrsqrtps   %0, %0" 
        : "+x"  (x)
    );
}

/* Sqrt approximation using rsqrt_avx and 1 iteration of NR (Can be improved) */
static inline float fast_sqrt_avx(register float x)
{
    const register float    nr = rsqrt_avx(x),
                            x2 = x * 0.5f; 

    return x * (nr * (1.5f - (x2 * nr * nr)));
}

/* SSE implementation of inverse sqrt (Only works on x86, circa Q1 2011+) */
static inline float rsqrt_sse(float x)
{
    float x_out;
    __m128 out = _mm_load_ss(&x);
    _mm_store_ss(&x_out, _mm_rsqrt_ss(out));
    return x_out;
}

/* SSE implementation of inverse sqrt (Only works on x86, circa Q1 2011+) */
static inline float rsqrt_sse_nr(float x)
{
    float   x_out;

    __m128  out = _mm_load_ss(&x);
    _mm_store_ss(&x_out, _mm_rsqrt_ss(out));
    
    return x_out * (1.5f - (x*0.5f*x_out*x_out));
}

/* Unnecessarily fast clamp function (AVX i think) */
static inline float fast_clamp_sse4(register float x, const register float lower, const register float upper)
{
    __asm__
    (
        "pmaxsd     %1, %0\n\t"
        "pminsd     %2, %0"
        : "+x"  (x)
        : "x"   (lower), "x"   (upper)
    );
}

/* Fast max */
static inline float max_x86(float x, float y)
{
    float max;
    __m128  x_ss = _mm_load_ss(&x),
            y_ss = _mm_load_ss(&y);

    _mm_store_ss(&max, _mm_max_ss(x_ss, y_ss));
    return max;
}

/* Fast min */
static inline float min_x86(float x, float y)
{
    float min;
    __m128  x_ss = _mm_load_ss(&x),
            y_ss = _mm_load_ss(&y);

    _mm_store_ss(&min, _mm_min_ss(x_ss, y_ss));
    return min;
}

/* Fast linearstep (can be improved) */
static inline float fast_linearstep(register float x, const register float a, register float b)
{
    x = x - a;
    b = b - a;
    
    __asm__
    (
        "divps  %1, %0"
        : "+x"  (x)
        : "x"   (b)
    );
    return fast_clamp_sse4(x, 0, 1);
}

/* simple smoothstep for simps */
float fast_smoothstep( register float X, register float A, register float B )
{
    register float t = fast_linearstep( X, A, B );

    return t * t * ( 3 - 2 * t );
}

/* simple lerp */
float fast_lerp( register float X1, register float X2, register float T )
{
    return (X1 + T * (X2 - X1));
}
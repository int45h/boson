#pragma once

/*
    sse_quatf.h (sse):   All SSE operations for float quaternions
*/

#include <math.h>

quatf quatf_init_angle_new_sse(float theta, float x, float y, float z)
{
    theta *= 0.5f;
    float   sin_t2      = sin(theta),
            cos_t2      = cos(theta);
    float   args[4]     = {0, x, y, z};
    
    __m128  q_sse       = _mm_load_ps(args);
    __m128  q_mag       = _mm_mul_ps(q_sse, q_sse);

    __m128  sint_sse    = _mm_load1_ps(&sin_t2);
    
    q_mag               = _mm_hadd_ps(q_mag, q_mag);
    q_mag               = _mm_hadd_ps(q_mag, q_mag);

    q_sse               = _mm_mul_ps(q_sse, _mm_mul_ps(_mm_rsqrt_ps(q_mag), sint_sse));

    _mm_store_ps(args, q_sse);
    return  (quatf){args[1], 
                    args[2], 
                    args[3], 
                    cos_t2};
}

void quatf_normalize_sse(float q[4])
{
    __m128  q_sse = _mm_load_ps(q),
            q_mag = _mm_mul_ps(q_sse, q_sse);

    q_mag = _mm_hadd_ps(q_mag, q_mag);
    q_mag = _mm_hadd_ps(q_mag, q_mag);

    _mm_store_ps(q, _mm_mul_ps(_mm_rsqrt_ps(q_mag), q_sse));
}

float quatf_dot_sse(float q_a[4], float q_b[4])
{
    __m128  qa_sse = _mm_load_ps(q_a),
            qb_sse = _mm_load_ps(q_b);
        
    qa_sse = _mm_mul_ps(qa_sse, qb_sse);

    qa_sse = _mm_hadd_ps(qa_sse, qa_sse);
    qa_sse = _mm_hadd_ps(qa_sse, qa_sse);

    float dot;
    _mm_store_ss(&dot, qa_sse);

    return dot;
}

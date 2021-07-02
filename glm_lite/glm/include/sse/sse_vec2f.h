#pragma once

/*
    sse_vec2f.h (sse):   All SSE operations for float vector 2
*/


float vec2f_length_sse(float v[2])
{
    float v_new[4] = {v[0], v[1], 0, 0};
    __m128  v_sse = _mm_load_ps(v_new);

    v_sse = _mm_mul_ps(v_sse, v_sse);
    
    v_sse = _mm_hadd_ps(v_sse, v_sse);
    v_sse = _mm_hadd_ps(v_sse, v_sse);
    
    v_sse = _mm_mul_ps(v_sse, _mm_rsqrt_ss(v_sse));
    _mm_store_ps(v_new, v_sse);

    return v_new[0];
}

float vec2f_inv_length_sse(float v[2])
{
    float v_new[4] = {v[0], v[1], 0, 0};
    __m128  v_sse = _mm_load_ps(v_new);

    v_sse = _mm_mul_ps(v_sse, v_sse);
    
    v_sse = _mm_hadd_ps(v_sse, v_sse);
    v_sse = _mm_hadd_ps(v_sse, v_sse);
    
    v_sse = _mm_rsqrt_ss(v_sse);
    _mm_store_ps(v_new, v_sse);

    return v_new[0];
}

void vec2f_normalize_sse(float v[2])
{
    float v_new[4] = {v[0], v[1], 0, 0};
    
    __m128  v_sse = _mm_load_ps(v_new),
            v_mag = _mm_mul_ps(v_sse, v_sse);

    v_mag = _mm_hadd_ps(v_mag, v_mag);
    v_mag = _mm_hadd_ps(v_mag, v_mag);
    
    v_mag = _mm_rsqrt_ps(v_mag);
    v_sse = _mm_mul_ps(v_mag, v_sse);

    _mm_store_ps(v_new, v_sse);

    v[0] = v_new[0];
    v[1] = v_new[1];
}

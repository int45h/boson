#include "../include/quatf.h"

#include <stdio.h>

void print_quatf(quatf q)
{
    printf("%f + %fi + %fj + %fk\n",    q.w,
                                        q.x,
                                        q.y,
                                        q.z );
}

quatf quatf_init(float x, float y, float z, float w)
{
    return  (quatf){x, y, z, w};
}

void quatf_init_angle(float theta, float x, float y, float z, float q[4])
{
    theta *= 0.5f;
    float   sin_2_mag = sin(theta) / sqrt(x*x + y*y + z*z);
    q[0]    = sin_2_mag*x, 
    q[1]    = sin_2_mag*y,
    q[2]    = sin_2_mag*z, 
    q[3]    = cos(theta);
}

quatf quatf_init_angle_new(float theta, float x, float y, float z)
{
    theta *= 0.5f;
    float   sin_2_mag = sin(theta) / sqrt(x*x + y*y + z*z);
    return  (quatf){sin_2_mag*x, 
                    sin_2_mag*y,
                    sin_2_mag*z, 
                    cos(theta)};
}

void quatf_copy(float src[4], float dest[4])
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
}

void quatf_scale(float q[4], float s)
{
    q[0] *= s;
    q[1] *= s;
    q[2] *= s;
    q[3] *= s;
}

quatf quatf_scale_new(float q[4], float s)
{
    return  (quatf){q[0]*s,
                    q[1]*s,
                    q[2]*s,
                    q[3]*s};
}

float quatf_norm(float q[4])
{
    return 1.f / sqrt(  q[0]*q[0] + 
                        q[1]*q[1] + 
                        q[2]*q[2] + 
                        q[3]*q[3]);
}

void quatf_normalize(float q[4])
{
    float inv_mag = 1.f / sqrt( q[0]*q[0] + 
                                q[1]*q[1] + 
                                q[2]*q[2] + 
                                q[3]*q[3]);
    q[0] *= inv_mag;
    q[1] *= inv_mag;
    q[2] *= inv_mag;
    q[3] *= inv_mag;
}

quatf quatf_normalize_new(float q[4])
{
    float inv_mag = 1.f / sqrt( q[0]*q[0] + 
                                q[1]*q[1] + 
                                q[2]*q[2] + 
                                q[3]*q[3]);

    return quatf_scale_new(q, inv_mag);
}

float quatf_dot(float q_a[4], float q_b[4])
{
    return  (q_a[0]*q_b[0]) + 
            (q_a[1]*q_b[1]) + 
            (q_a[2]*q_b[2]) + 
            (q_a[3]*q_b[3]);
}

void quatf_conjugate(float q[4])
{
    q[0] *= -1;
    q[1] *= -1;
    q[2] *= -1;
}

quatf quatf_conjugate_new(float q[4])
{
    return (quatf){ q[0] * -1,
                    q[1] * -1,
                    q[2] * -1,
                    q[3]        };
}

void quatf_add(float q_a[4], float q_b[4])
{
    q_b[0] = q_a[0] + q_b[0];
    q_b[1] = q_a[1] + q_b[1];
    q_b[2] = q_a[2] + q_b[2];
    q_b[3] = q_a[3] + q_b[3];
}

void quatf_sub(float q_a[4], float q_b[4])
{
    q_b[0] = q_a[0] - q_b[0];
    q_b[1] = q_a[1] - q_b[1];
    q_b[2] = q_a[2] - q_b[2];
    q_b[3] = q_a[3] - q_b[3];
}

void quatf_adds(float q[4], float s)
{
    q[0] += s;
    q[1] += s;
    q[2] += s;
    q[3] += s;
}

void quatf_subs(float q[4], float s)
{
    q[0] -= s;
    q[1] -= s;
    q[2] -= s;
    q[3] -= s;
}

quatf quatf_add_new(float q_a[4], float q_b[4])
{
    return  (quatf){    q_a[0] + q_b[0],
                        q_a[1] + q_b[1],
                        q_a[2] + q_b[2],
                        q_a[3] + q_b[3] };
}

quatf quatf_sub_new(float q_a[4], float q_b[4])
{
    return  (quatf){    q_a[0] - q_b[0],
                        q_a[1] - q_b[1],
                        q_a[2] - q_b[2],
                        q_a[3] - q_b[3] };
}

quatf quatf_adds_new(float q[4], float s)
{
    return  (quatf){    q[0] + s,
                        q[1] + s,
                        q[2] + s,
                        q[3] + s    };
}

quatf quatf_subs_new(float q[4], float s)
{
    return  (quatf){    q[0] - s,
                        q[1] - s,
                        q[2] - s,
                        q[3] - s    };
}

float quatf_angle(float q[4])
{
    return 2 * acos(q[3]);
}

quatf quatf_mul(float a[4], float b[4])
{
    return  (quatf){    +(a[3]*b[0] + a[0]*b[3] + a[1]*b[2] - a[2]*b[1]),       // i
                        +(a[3]*b[1] - a[0]*b[2] + a[1]*b[3] + a[2]*b[0]),       // j
                        +(a[3]*b[2] + a[0]*b[1] - a[1]*b[0] + a[2]*b[3]),       // k
                        +(a[3]*b[3] - a[0]*b[0] - a[1]*b[1] - a[2]*b[2])    };  // r
}

vec3f quatf_mul_vec_new(float q[4], float v[3])
{
    // v' := 2 * cross(q.ijk, v)
    float   vx = 2 * (q[1]*v[2] - q[2]*v[1]),
            vy = 2 * (q[2]*v[0] - q[0]*v[2]),
            vz = 2 * (q[0]*v[1] - q[1]*v[0]);

    // v' := v + (q.r * v') + cross(q.ijk, v')
    return  (vec3f){    v[0] + q[3]*vx + q[1]*vz-q[2]*vy,
                        v[1] + q[3]*vy + q[2]*vx-q[0]*vz,
                        v[2] + q[3]*vz + q[0]*vy-q[1]*vx    };
}

void quatf_mul_vec(float q[4], float v[3], float out[3])
{
    // v' := 2 * cross(q.ijk, v)
    float   vx = 2 * (q[1]*v[2] - q[2]*v[1]),
            vy = 2 * (q[2]*v[0] - q[0]*v[2]),
            vz = 2 * (q[0]*v[1] - q[1]*v[0]);

    // v' := v + (q.r * v') + cross(q.ijk, v')
    out[0] = v[0] + q[3]*vx + q[1]*vz-q[2]*vy;
    out[1] = v[1] + q[3]*vy + q[2]*vx-q[0]*vz;
    out[2] = v[2] + q[3]*vz + q[0]*vy-q[1]*vx;
}

quatf quatf_euler_new(float x, float y, float z) 
{
	x *= 0.5f;
	y *= 0.5f;
	z *= 0.5f;
	
	float 	x_2cos = cos(x),    y_2cos = cos(y),    z_2cos = cos(z),
			x_2sin = sin(x),    y_2sin = sin(y),    z_2sin = sin(z),
            xy_2cos = x_2cos * y_2cos,
            yz_2cos = y_2cos * z_2cos,
            xz_2cos = x_2cos * z_2cos,
            xy_2sin = x_2sin * y_2sin,
            yz_2sin = y_2sin * z_2sin,
            xz_2sin = x_2sin * z_2sin;		
	
	return  (quatf) {   (x_2cos * yz_2cos) + (xy_2sin * z_2sin),
	                    (x_2sin * yz_2cos) - (x_2cos * yz_2sin),
	                    (xz_2cos * y_2sin) + (xz_2sin * y_2cos),
	                    (xy_2cos * z_2sin) - (xy_2sin * z_2cos)};
}

void quatf_euler(float x, float y, float z, float q[4]) 
{
	x *= 0.5f;
	y *= 0.5f;
	z *= 0.5f;
	
	float 	x_2cos = cos(x),    y_2cos = cos(y),    z_2cos = cos(z),
			x_2sin = sin(x),    y_2sin = sin(y),    z_2sin = sin(z),
            xy_2cos = x_2cos * y_2cos,
            yz_2cos = y_2cos * z_2cos,
            xz_2cos = x_2cos * z_2cos,
            xy_2sin = x_2sin * y_2sin,
            yz_2sin = y_2sin * z_2sin,
            xz_2sin = x_2sin * z_2sin;		
	
	q[0] = (x_2cos * yz_2cos) + (xy_2sin * z_2sin);
    q[1] = (x_2sin * yz_2cos) - (x_2cos * yz_2sin);
    q[2] = (xz_2cos * y_2sin) + (xz_2sin * y_2cos);
    q[3] = (xy_2cos * z_2sin) - (xy_2sin * z_2cos);
}

vec3f quatf_to_euler_new(float q[4])
{
    float   x = atan2(2*(q[3]*q[0] + q[1]*q[2]), 1-(2*(q[0]*q[0] + q[1]*q[1]))),
            y = asin(2*(q[3]*q[1] - q[2]*q[0])),
            z = atan2(2*(q[3]*q[2] + q[0]*q[1]), 1-(2*(q[1]*q[1] + q[2]*q[2])));

    return  (vec3f){x, y, z};
}

void quatf_to_euler(float q[4], float v[3])
{
    float   x = atan2(2*(q[3]*q[0] + q[1]*q[2]), 1-(2*(q[0]*q[0] + q[1]*q[1]))),
            y = asin(2*(q[3]*q[1] - q[2]*q[0])),
            z = atan2(2*(q[3]*q[2] + q[0]*q[1]), 1-(2*(q[1]*q[1] + q[2]*q[2])));

    v[0] = x;   v[1] = y;   v[2] = z;
}

void quatf_to_mat4f(float q[4], float m[16])
{
    float   s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    m[0]    = 1 - 2*Y - 2*Z;
    m[5]    = 1 - 2*X - 2*Z;
    m[10]   = 1 - 2*X - 2*Y;
    m[15]   = 1;

    m[1]    = (xy + wz);
    m[2]    = (xz - wy);
    
    m[4]    = (xy - wz);
    m[6]    = (yz + wx);

    m[8] = (xz + wy);
    m[9] = (yz - wx);

    m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0;
}

mat4f quatf_to_mat4f_new(float q[4])
{
    float   a, e, i, m,
            b, f, j, n,
            c, g, k, o,
            d, h, l, p,
            
            s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    a = 1 - 2*Y - 2*Z;
    f = 1 - 2*X - 2*Z;
    k = 1 - 2*X - 2*Y;
    p = 1;

    b = (xy + wz);
    c = (xz - wy);
    
    e = (xy - wz);
    g = (yz + wx);

    i = (xz + wy);
    j = (yz - wx);

    d = h = l = m = n = o = 0;

    return  (mat4f){    a, b, c, d,
                        e, f, g, h,
                        i, j, k, l,
                        m, n, o, p  }; 
}

/*
     0,  1,  2,  3,
     4,  5,  6,  7,
     8,  9, 10, 11,
    12, 13, 14, 15
*/
void quatf_to_mat4ft(float q[4], float m[16])
{
    float   s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    m[0]    = 1 - 2*Y - 2*Z;
    m[5]    = 1 - 2*X - 2*Z;
    m[10]   = 1 - 2*X - 2*Y;
    m[15]   = 1;

    m[4]    = (xy + wz);
    m[8]    = (xz - wy);
    
    m[1]    = (xy - wz);
    m[9]    = (yz + wx);

    m[2]    = (xz + wy);
    m[6]    = (yz - wx);

    m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0;
}

mat4f quatf_to_mat4ft_new(float q[4])
{
    float   a, e, i, m,
            b, f, j, n,
            c, g, k, o,
            d, h, l, p,
            
            s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    a = 1 - 2*Y - 2*Z;
    f = 1 - 2*X - 2*Z;
    k = 1 - 2*X - 2*Y;
    p = 1;

    b = (xy + wz);
    c = (xz - wy);
    
    e = (xy - wz);
    g = (yz + wx);

    i = (xz + wy);
    j = (yz - wx);

    d = h = l = m = n = o = 0;

    return  (mat4f){    a, e, i, m,
                        b, f, j, n,
                        c, g, k, o,
                        d, h, l, p  };
}

void quatf_to_mat3f(float q[4], float m[9])
{
    float   s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    m[0]    = 1 - 2*Y - 2*Z;
    m[4]    = 1 - 2*X - 2*Z;
    m[8]    = 1 - 2*X - 2*Y;

    m[1]    = (xy + wz);
    m[2]    = (xz - wy);
    
    m[3]    = (xy - wz);
    m[5]    = (yz + wx);

    m[6]    = (xz + wy);
    m[7]    = (yz - wx);
}

mat3f quatf_to_mat3f_new(float q[4])
{
    float   a, b, c, 
            d, e, f, 
            g, h, i,

            s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    a   = 1 - 2*Y - 2*Z;
    e   = 1 - 2*X - 2*Z;
    i   = 1 - 2*X - 2*Y;

    b   = (xy + wz);
    c   = (xz - wy);
    
    d   = (xy - wz);
    f   = (yz + wx);

    g   = (xz + wy);
    i   = (yz - wx);

    return  (mat3f){    a, b, c, 
                        d, e, f, 
                        g, h, i     }; 
}

void quatf_to_mat3ft(float q[4], float m[9])
{
    float   s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*x*w,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    m[0]    = 1 - 2*Y - 2*Z;
    m[4]    = 1 - 2*X - 2*Z;
    m[8]    = 1 - 2*X - 2*Y;

    m[3]    = (xy + wz);
    m[6]    = (xz - wy);
    
    m[1]    = (xy - wz);
    m[7]    = (yz + wx);

    m[2]    = (xz + wy);
    m[5]    = (yz - wx);
}

mat3f quatf_to_mat3ft_new(float q[4])
{
    float   a, b, c, 
            d, e, f, 
            g, h, i,

            s2 = 2 * quatf_norm(q);

    float   w = q[3],
            x = q[0],
            y = q[1],
            z = q[2],

            X = x*x,
            Y = y*y,
            Z = z*z,
            
            xy = s2*x*y,
            xz = s2*x*z,
            wx = s2*w*x,
            wy = s2*w*y,
            wz = s2*w*z,
            yz = s2*y*z;

    a   = 1 - 2*(Y - Z);
    e   = 1 - 2*(X - Z);
    i   = 1 - 2*(X - Y);

    b   = (xy + wz);
    c   = (xz - wy);
    
    d   = (xy - wz);
    f   = (yz + wx);

    g   = (xz + wy);
    i   = (yz - wx);
    
    return  (mat3f){    a, d, g, 
                        b, e, h, 
                        c, f, i     }; 
}

mat4f quatf_to_look_mat4f_new(float eye[3], float ori[4])
{
    mat4f m;
    /* Orientation */
    quatf_to_mat4ft(ori, m.comp);

    /* Translation */
    float v_T[4] = {eye[0], eye[1], eye[2], 1};
    mat4f_mul_vec(v_T, m.comp);
    
    vec4f_scale(v_T, -1, v_T);

    mat4f_set_col(v_T, m.comp, 3);

    return m;
}

void quatf_to_look_mat4f(float eye[3], float ori[4], float m[16])
{
    /* Orientation */
    quatf_to_mat4ft(ori, m);

    /* Translation */
    float v_T[4] = {eye[0], eye[1], eye[2], 1};
    mat4f_mul_vec(v_T, m);
    
    vec4f_scale(v_T, -1, v_T);

    mat4f_set_col(v_T, m, 3);
}

mat4f quatf_to_look_mat4ft_new(float eye[3], float ori[4])
{
    mat4f m;
    /* Orientation */
    quatf_to_mat4f(ori, m.comp);

    /* Translation */
    float v_T[4] = {eye[0], eye[1], eye[2], 1};
    mat4f_mul_vec(v_T, m.comp);
    
    vec4f_scale(v_T, -1, v_T);

    mat4f_set_row(v_T, m.comp, 3);

    return m;
}

void quatf_to_look_mat4ft(float eye[3], float ori[4], float m[16])
{
    /* Orientation */
    quatf_to_mat4f(ori, m);

    /* Translation */
    float v_T[4] = {eye[0], eye[1], eye[2], 1};
    mat4f_mul_vec(v_T, m);
    
    vec4f_scale(v_T, -1, v_T);

    mat4f_set_row(v_T, m, 3);
}

/* From https://stackoverflow.com/questions/12435671/quaternion-lookat-function */
quatf quatf_lookat_new(float src[3], float dest[3])
{
    vec3f forwardVector = vec3f_sub_new(dest, src);
    vec3f_normalize(forwardVector.c);

    float dot = vec3f_dot((vec3f){0, 0, 1}.c, forwardVector.c);
/*
    if (abs(dot - (-1.0f)) < 0.000001f)
    {
        return (quatf){0, 1, 0, 3.1415926535897932f};
    }
    if (abs(dot - (1.0f)) < 0.000001f)
    {
        return QUATF_IDENTITY;
    }
*/
    float   rotAngle    = acos(dot) * 0.5f, // Half angle
            s_rotAngle  = sin(rotAngle);

    vec3f rotAxis = vec3f_cross_new((vec3f){0, 0, 1}.c, forwardVector.c);
    vec3f_normalize(rotAxis.c);

    return (quatf){ rotAxis.x * s_rotAngle,
                    rotAxis.y * s_rotAngle,
                    rotAxis.z * s_rotAngle,
                    dot                     };
}
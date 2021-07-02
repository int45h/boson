#include "../include/mat4f.h"
#include <stdio.h>
/*
    mat4f.c:    C source file for all float mat2 operations
*/

void print_mat4f(mat4f m)
{
    printf("{\t%f, %f, %f, %f,\n",  m.a,
                                    m.b,
                                    m.c,
                                    m.d);
    printf("\t%f, %f, %f, %f,\n",   m.e,
                                    m.f,
                                    m.g,
                                    m.h);
    printf("\t%f, %f, %f, %f,\n",   m.i,
                                    m.j,
                                    m.k,
                                    m.l);
    printf("\t%f, %f, %f, %f}\n",   m.m,
                                    m.n,
                                    m.o,
                                    m.p);
}

mat4f mat4f_init(   float a, float b, float c, float d,
                    float e, float f, float g, float h,
                    float i, float j, float k, float l,
                    float m, float n, float o, float p  )
{
    return  (mat4f){    a, b, c, d,
                        e, f, g, h, 
                        i, j, k, l,
                        m, n, o, p  };
}

mat4f mat4f_zero()
{
    return  (mat4f){    0, 0, 0, 0,
                        0, 0, 0, 0, 
                        0, 0, 0, 0,
                        0, 0, 0, 0  };
}

mat4f mat4f_mul_new(float m_a[16], float m_b[16])
{
    float   a = m_a[0]*m_b[0] + m_a[1]*m_b[4] + m_a[2]*m_b[8] + m_a[3]*m_b[12], 
            b = m_a[0]*m_b[1] + m_a[1]*m_b[5] + m_a[2]*m_b[9] + m_a[3]*m_b[13], 
            c = m_a[0]*m_b[2] + m_a[1]*m_b[6] + m_a[2]*m_b[10] + m_a[3]*m_b[14], 
            d = m_a[0]*m_b[3] + m_a[1]*m_b[7] + m_a[2]*m_b[11] + m_a[3]*m_b[15], 
            
            e = m_a[4]*m_b[0] + m_a[5]*m_b[4] + m_a[6]*m_b[8] + m_a[7]*m_b[12], 
            f = m_a[4]*m_b[1] + m_a[5]*m_b[5] + m_a[6]*m_b[9] + m_a[7]*m_b[13], 
            g = m_a[4]*m_b[2] + m_a[5]*m_b[6] + m_a[6]*m_b[10] + m_a[7]*m_b[14], 
            h = m_a[4]*m_b[3] + m_a[5]*m_b[7] + m_a[6]*m_b[11] + m_a[7]*m_b[15],
            
            i = m_a[8]*m_b[0] + m_a[9]*m_b[4] + m_a[10]*m_b[8] + m_a[11]*m_b[12], 
            j = m_a[8]*m_b[1] + m_a[9]*m_b[5] + m_a[10]*m_b[9] + m_a[11]*m_b[13], 
            k = m_a[8]*m_b[2] + m_a[9]*m_b[6] + m_a[10]*m_b[10] + m_a[11]*m_b[14], 
            l = m_a[8]*m_b[3] + m_a[9]*m_b[7] + m_a[10]*m_b[11] + m_a[11]*m_b[15], 
            
            m = m_a[12]*m_b[0] + m_a[13]*m_b[4] + m_a[14]*m_b[8] + m_a[15]*m_b[12], 
            n = m_a[12]*m_b[1] + m_a[13]*m_b[5] + m_a[14]*m_b[9] + m_a[15]*m_b[13], 
            o = m_a[12]*m_b[2] + m_a[13]*m_b[6] + m_a[14]*m_b[10] + m_a[15]*m_b[14], 
            p = m_a[12]*m_b[3] + m_a[13]*m_b[7] + m_a[14]*m_b[11] + m_a[15]*m_b[15];

    return  (mat4f){    a, b, c, d,
                        e, f, g, h,
                        i, j, k, l, 
                        m, n, o, p  };
}

void mat4f_mul(float m_a[16], float m_b[16])
{
    float   a = m_a[0]*m_b[0] + m_a[1]*m_b[4] + m_a[2]*m_b[8] + m_a[3]*m_b[12], 
            b = m_a[0]*m_b[1] + m_a[1]*m_b[5] + m_a[2]*m_b[9] + m_a[3]*m_b[13], 
            c = m_a[0]*m_b[2] + m_a[1]*m_b[6] + m_a[2]*m_b[10] + m_a[3]*m_b[14], 
            d = m_a[0]*m_b[3] + m_a[1]*m_b[7] + m_a[2]*m_b[11] + m_a[3]*m_b[15], 
            
            e = m_a[4]*m_b[0] + m_a[5]*m_b[4] + m_a[6]*m_b[8] + m_a[7]*m_b[12], 
            f = m_a[4]*m_b[1] + m_a[5]*m_b[5] + m_a[6]*m_b[9] + m_a[7]*m_b[13], 
            g = m_a[4]*m_b[2] + m_a[5]*m_b[6] + m_a[6]*m_b[10] + m_a[7]*m_b[14], 
            h = m_a[4]*m_b[3] + m_a[5]*m_b[7] + m_a[6]*m_b[11] + m_a[7]*m_b[15],
            
            i = m_a[8]*m_b[0] + m_a[9]*m_b[4] + m_a[10]*m_b[8] + m_a[11]*m_b[12], 
            j = m_a[8]*m_b[1] + m_a[9]*m_b[5] + m_a[10]*m_b[9] + m_a[11]*m_b[13], 
            k = m_a[8]*m_b[2] + m_a[9]*m_b[6] + m_a[10]*m_b[10] + m_a[11]*m_b[14], 
            l = m_a[8]*m_b[3] + m_a[9]*m_b[7] + m_a[10]*m_b[11] + m_a[11]*m_b[15], 
            
            m = m_a[12]*m_b[0] + m_a[13]*m_b[4] + m_a[14]*m_b[8] + m_a[15]*m_b[12], 
            n = m_a[12]*m_b[1] + m_a[13]*m_b[5] + m_a[14]*m_b[9] + m_a[15]*m_b[13], 
            o = m_a[12]*m_b[2] + m_a[13]*m_b[6] + m_a[14]*m_b[10] + m_a[15]*m_b[14], 
            p = m_a[12]*m_b[3] + m_a[13]*m_b[7] + m_a[14]*m_b[11] + m_a[15]*m_b[15];

    m_b[0]  = a;
    m_b[1]  = b;
    m_b[2]  = c;
    m_b[3]  = d;
    
    m_b[4]  = e;
    m_b[5]  = f;
    m_b[6]  = g;
    m_b[7]  = h;
    
    m_b[8]  = i;
    m_b[9]  = j;
    m_b[10] = k;
    m_b[11] = l;
    
    m_b[12] = m;
    m_b[13] = n;
    m_b[14] = o;
    m_b[15] = p;
}

vec4f mat4f_mul_vec_new(float v[4], float m[16])
{
    return  (vec4f) {   v[0]*m[0] + v[1]*m[4] + v[2]*m[8] + v[3]*m[12], 
                        v[0]*m[1] + v[1]*m[5] + v[2]*m[9] + v[3]*m[13], 
                        v[0]*m[2] + v[1]*m[6] + v[2]*m[10] + v[3]*m[14], 
                        v[0]*m[3] + v[1]*m[7] + v[2]*m[11] + v[3]*m[15] };
};

void mat4f_mul_vec(float v[4], float m[16])
{
    float   w = v[0],
            x = v[1],
            y = v[2],
            z = v[3];

    v[0]    = w*m[0] + x*m[4] + y*m[8] + z*m[12]; 
    v[1]    = w*m[1] + x*m[5] + y*m[9] + z*m[13];
    v[2]    = w*m[2] + x*m[6] + y*m[10] + z*m[14]; 
    v[3]    = w*m[3] + x*m[7] + y*m[11] + z*m[15];
};

float mat4f_det(float M[16])
{
    float   a = M[0],	b = M[1], 	c = M[2], 	d = M[3],
	        e = M[4], 	f = M[5], 	g = M[6], 	h = M[7],
	        i = M[8], 	j = M[9], 	k = M[10], 	l = M[11],
	        m = M[12],	n = M[13], 	o = M[14], 	p = M[15];
	    
	float	t_0 = k*p - l*o,
	        t_1 = j*p - l*n,
	    	t_2 = j*o - k*n,
	    	t_3 = i*p - l*m,
	    	t_4 = i*o - k*m,
	    	t_5 = i*n - j*m;
	    
    return (+ a * ( f * t_0 - g * t_1 + h * t_2 )
	        - b * ( e * t_0 - g * t_3 + h * t_4 )
	        + c * ( e * t_1 - f * t_3 + h * t_5 )
	        - d * ( e * t_2 - f * t_4 + g * t_5 ));
}

void mat4f_ucopy(float dest[16], float src[16])
{
    dest[0]    = src[0];
    dest[1]    = src[1];
    dest[2]    = src[2];
    dest[3]    = src[3];
    
    dest[4]    = src[4];
    dest[5]    = src[5];
    dest[6]    = src[6];
    dest[7]    = src[7];
    
    dest[8]    = src[8];
    dest[9]    = src[9];
    dest[10]   = src[10];
    dest[11]   = src[11];
    
    dest[12]   = src[12];
    dest[13]   = src[13];
    dest[14]   = src[14];
    dest[15]   = src[15];
};

void mat4f_transpose(float M[16])
{
    float   b = M[1],
            c = M[2],
            d = M[3],
            e = M[4],
            
            g = M[6],
            h = M[7],
            i = M[8],
            j = M[9],
            
            l = M[11],
            m = M[12],
            n = M[13],
            o = M[14];
    
    M[1] = e;
    M[2] = i;
    M[3] = m;
    M[4] = b;

    M[6] = j;
    M[7] = n; 
    M[8] = c;
    M[9] = g;

    M[11] = o;
    M[12] = d;
    M[13] = h;
    M[14] = l;
};

void mat4f_mul_scalar(float s, float m[16])
{
    m[0]    *= s;
    m[1]    *= s;
    m[2]    *= s;
    m[3]    *= s;

    m[4]    *= s;
    m[5]    *= s;
    m[6]    *= s;
    m[7]    *= s;
    
    m[8]    *= s;
    m[9]    *= s;
    m[10]   *= s;
    m[11]   *= s;
    
    m[12]   *= s;
    m[13]   *= s;
    m[14]   *= s;
    m[15]   *= s;
};

#define det3x3( a, b, c,\
                d, e, f,\
                g, h, i )   (a * (e*i - f*h)) -\
                            (b * (d*i - f*g)) +\
                            (c * (d*h - e*g))

void mat4f_inverse(float M[16])
{
    float 	a = det3x3(M[5], M[6], M[7], M[9], M[10], M[11], M[13], M[14], M[15]),
			b = det3x3(M[4], M[6], M[7], M[8], M[10], M[11], M[12], M[14], M[15]),
			c = det3x3(M[4], M[5], M[7], M[8], M[9] , M[11], M[12], M[13], M[15]),
			d = det3x3(M[4], M[5], M[6], M[8], M[9] , M[10], M[12], M[13], M[14]),
				
			e = det3x3(M[1], M[2], M[3], M[9], M[10], M[11], M[13], M[14], M[15]),
			f = det3x3(M[0], M[2], M[3], M[8], M[10], M[11], M[12], M[14], M[15]),
			g = det3x3(M[0], M[1], M[3], M[8], M[9] , M[11], M[12], M[13], M[15]),
			h = det3x3(M[0], M[1], M[2], M[8], M[9] , M[10], M[12], M[13], M[14]),
				
			i = det3x3(M[1], M[2], M[3], M[5], M[6] , M[7] , M[13], M[14], M[15]),
			j = det3x3(M[0], M[2], M[3], M[4], M[6] , M[7] , M[12], M[14], M[15]),
			k = det3x3(M[0], M[1], M[3], M[4], M[5] , M[7] , M[12], M[13], M[15]),
			l = det3x3(M[0], M[1], M[2], M[4], M[5] , M[6] , M[12], M[13], M[14]),
				
			m = det3x3(M[1], M[2], M[3], M[5], M[6] , M[7] , M[9] , M[10], M[11]),
			n = det3x3(M[0], M[2], M[3], M[4], M[6] , M[7] , M[8] , M[10], M[11]),
			o = det3x3(M[0], M[1], M[3], M[4], M[5] , M[7] , M[8] , M[9] , M[11]),
			p = det3x3(M[0], M[1], M[2], M[4], M[5] , M[6] , M[8] , M[9] , M[10]),
            inv_det = mat4f_det(M);
		
    M[0]    = +(inv_det * a);
    M[1]    = -(inv_det * b);
    M[2]    = +(inv_det * c);
    M[3]    = -(inv_det * d);
    M[4]    = -(inv_det * e);
    M[5]    = +(inv_det * f);
    M[6]    = -(inv_det * g);
    M[7]    = +(inv_det * h);
    M[8]    = +(inv_det * i);
    M[9]    = -(inv_det * j);
    M[10]   = +(inv_det * k);
    M[11]   = -(inv_det * l);
    M[12]   = -(inv_det * m);
    M[13]   = +(inv_det * n);
    M[14]   = -(inv_det * o);
    M[15]   = +(inv_det * p);            
}

mat4f mat4f_inverse_new(float M[16])
{
    float 	inv_det = mat4f_det(M),
            a = +(inv_det * det3x3(M[5], M[6], M[7], M[9], M[10], M[11], M[13], M[14], M[15])),
			b = -(inv_det * det3x3(M[4], M[6], M[7], M[8], M[10], M[11], M[12], M[14], M[15])),
			c = +(inv_det * det3x3(M[4], M[5], M[7], M[8], M[9] , M[11], M[12], M[13], M[15])),
			d = -(inv_det * det3x3(M[4], M[5], M[6], M[8], M[9] , M[10], M[12], M[13], M[14])),
			e = -(inv_det * det3x3(M[1], M[2], M[3], M[9], M[10], M[11], M[13], M[14], M[15])),
			f = +(inv_det * det3x3(M[0], M[2], M[3], M[8], M[10], M[11], M[12], M[14], M[15])),
			g = -(inv_det * det3x3(M[0], M[1], M[3], M[8], M[9] , M[11], M[12], M[13], M[15])),
			h = +(inv_det * det3x3(M[0], M[1], M[2], M[8], M[9] , M[10], M[12], M[13], M[14])),
			i = +(inv_det * det3x3(M[1], M[2], M[3], M[5], M[6] , M[7] , M[13], M[14], M[15])),
			j = -(inv_det * det3x3(M[0], M[2], M[3], M[4], M[6] , M[7] , M[12], M[14], M[15])),
			k = +(inv_det * det3x3(M[0], M[1], M[3], M[4], M[5] , M[7] , M[12], M[13], M[15])),
			l = -(inv_det * det3x3(M[0], M[1], M[2], M[4], M[5] , M[6] , M[12], M[13], M[14])),
			m = -(inv_det * det3x3(M[1], M[2], M[3], M[5], M[6] , M[7] , M[9] , M[10], M[11])),
			n = +(inv_det * det3x3(M[0], M[2], M[3], M[4], M[6] , M[7] , M[8] , M[10], M[11])),
			o = -(inv_det * det3x3(M[0], M[1], M[3], M[4], M[5] , M[7] , M[8] , M[9] , M[11])),
			p = +(inv_det * det3x3(M[0], M[1], M[2], M[4], M[5] , M[6] , M[8] , M[9] , M[10]));
	return  (mat4f){    a, b, c, d,
                        e, f, g, h,
                        i, j, k, l,
                        m, n, o, p  };
}

float mat4f_trace(float m[16])
{
    return m[0]+m[5]+m[10]+m[15];
}

void mat4f_set_col(float v[4], float m[16], int j)
{
    m[4*0 + j] = v[0];
    m[4*1 + j] = v[1];
    m[4*2 + j] = v[2];
    m[4*3 + j] = v[3];
}

void mat4f_set_row(float v[4], float m[16], int i)
{
    m[4*i + 0] = v[0];
    m[4*i + 1] = v[1];
    m[4*i + 2] = v[2];
    m[4*i + 3] = v[3];
}

void mat4f_projection(float aspect, float fov, float n, float f, float m[16]) 
{
	fov = radians_f(fov);
	float 	tan_fov 	= tan(fov * 0.5f),
			cot_fov 	= (float)(1/tan_fov);
	float 	frust_len_1	= (float)(1 / (f-n)); 
		
	float 	t = n * tan_fov, 
			b = -t, 
			r = t * aspect, 
			l = -r;
		
	float	rl_1 	= (float)1/(r-l),
			tb_1 	= (float)1/(t-b),
			n_2		= (float)2*n;
		
	m[0]    = n_2*rl_1,	
    m[1]    = 0;
    m[2]    = 0;
    m[3]    = 0;

	m[4]    = 0;
    m[5]    = n_2*tb_1;
    m[6]    = 0;
    m[7]    = 0;

	m[8]    = (r+l)*rl_1;
    m[9]    = (t+b)*tb_1; 
    m[10]   = (-f-n)*frust_len_1;
    m[11]   = -1;
				
    m[12]   = 0;
    m[13]   = 0;
    m[14]   = -n_2*f*frust_len_1;
    m[15]   = 0;
}

mat4f mat4f_projection_new(float aspect, float fov, float n, float f)
{
	fov = radians_f(fov);
	float 	tan_fov 	= tan(fov * 0.5f),
			cot_fov 	= (float)(1/tan_fov);
	float 	frust_len_1	= (float)(1 / (f-n)); 
		
	float 	t = n * tan_fov, 
			b = -t, 
			r = t * aspect, 
			l = -r;
		
	float	rl_1 	= (float)1/(r-l),
			tb_1 	= (float)1/(t-b),
			n_2		= (float)2*n;
		
	mat4f proj = (mat4f){	n_2*rl_1,	0,			0,					0,
							0,			n_2*tb_1,	0,					0,
							(r+l)*rl_1,	(t+b)*tb_1, (-f-n)*frust_len_1,	-1,
							0,			0,			-n_2*f*frust_len_1, 0  };
	return proj;	
}

void mat4ft_projection(float aspect, float fov, float n, float f, float m[16]) 
{
	fov = radians_f(fov);
	float 	tan_fov 	= tan(fov * 0.5f),
			cot_fov 	= (1.f/tan_fov);
	float 	frust_len_1	= (1.f / (f-n)); 
		
	float 	t = n * tan_fov, 
			b = -t, 
			r = t * aspect, 
			l = -r;
		
	float	rl_1 	= 1.f/(r-l),
			tb_1 	= 1.f/(t-b),
			n_2		= 2*n;
		
	m[0]    = n_2*rl_1,	
    m[4]    = 0;
    m[8]    = 0;
    m[12]   = 0;

	m[1]    = 0;
    m[5]    = n_2*tb_1;
    m[9]    = 0;
    m[13]   = 0;

	m[2]    = (r+l)*rl_1;
    m[6]    = (t+b)*tb_1; 
    m[10]   = (-f-n)*frust_len_1;
    m[14]   = -1;
				
    m[3]    = 0;
    m[7]    = 0;
    m[11]   = -n_2*f*frust_len_1;
    m[15]   = 0;
}

mat4f mat4ft_projection_new(float aspect, float fov, float n, float f)
{
	fov = radians_f(fov);
	float 	tan_fov 	= tan(fov * 0.5f),
			cot_fov 	= (1.f/tan_fov);
	float 	frust_len_1	= (1.f / (f-n)); 
		
	float 	t = n * tan_fov, 
			b = -t, 
			r = t * aspect, 
			l = -r;
		
	float	rl_1 	= (float)1/(r-l),
			tb_1 	= (float)1/(t-b),
			n_2		= (float)2*n;

	mat4f proj = (mat4f){	n_2*rl_1,	0,			(r+l)*rl_1,         0,
							0,			n_2*tb_1,	(t+b)*tb_1,         0,
							0,	        0,          (-f-n)*frust_len_1,	-n_2*f*frust_len_1,
							0,			0,			-1,                 0  };
	return proj;	
}

void mat4f_translate(float v[3], float m[16])
{
    m[0]  = m[5]  = m[10] = m[15] = 1;
    m[4]  = m[6]  = m[8]  = m[9]  = 
    m[12] = m[13] = m[14] = 0;

    m[3]  = v[0];
    m[7]  = v[1];
    m[11] = v[2];
}

mat4f mat4f_translate_new(float v[3])
{
    return  (mat4f){    1, 0, 0, v[0],
                        0, 1, 0, v[1],
                        0, 0, 1, v[2],
                        0, 0, 0, 1      };
}

void mat4ft_translate(float v[3], float m[16])
{
    m[0]  = m[5]  = m[10] = m[15] = 1;
    m[1]  = m[2]  = m[3]  = m[4]  = 
    m[6]  = m[7]  = m[8]  = m[9]  = 
    m[11] = 0;
    
    m[12] = v[0];
    m[13] = v[1];
    m[14] = v[2];
}

mat4f mat4ft_translate_new(float v[3])
{
    return  (mat4f){    1,    0,    0,    0,
                        0,    1,    0,    0,
                        0,    0,    1,    0,
                        v[0], v[1], v[2], 1     };
}

void mat4f_scale(float v[3], float s[3], float m[16])
{
    m[0]    = v[0]*s[0];
    m[5]    = v[1]*s[1];
    m[10]   = v[2]*s[2];
    m[15]   = 1;

    m[1]  = m[2]  = m[3]  = m[4]  =
    m[6]  = m[7]  = m[8]  = m[9]  =
    m[11] = m[12] = m[13] = m[14] = 0;
}

mat4f mat4f_scale_new(float v[3], float s[3])
{
    return  (mat4f){    v[0]*s[0], 0, 0, 0,
                        0, v[1]*s[1], 0, 0,
                        0, 0, v[2]*s[2], 0,
                        0, 0, 0, 1          };
}

void mat4f_look_at(float from[3], float to[3], float m[16])
{
    vec3f   forward = vec3f_sub_new(from, to);
    vec3f_normalize(forward.c);
    vec3f   right   = vec3f_cross_new((vec3f){0, 1, 0}.c, forward.c),
            up      = vec3f_cross_new(forward.c, right.c);

    m[0]    =   right.x;
    m[1]    =   up.x;
    m[2]    =   forward.x;
    m[3]    =   from[0];
    m[4]    =   right.y;
    m[5]    =   up.y;
    m[6]    =   forward.y;
    m[7]    =   from[1];
    m[8]    =   right.z;
    m[9]    =   up.z;
    m[10]   =   forward.z;
    m[11]   =   from[2];    
    m[12]   =   0.f;
    m[13]   =   0.f;
    m[14]   =   0.f;
    m[15]   =   1.f;
}

void mat4ft_look_at(float from[3], float to[3], float m[16])
{
    vec3f   forward = vec3f_sub_new(from, to);
    vec3f_normalize(forward.c);
    vec3f   right   = vec3f_cross_new((vec3f){0, 1, 0}.c, forward.c);
    vec3f_normalize(right.c);
    vec3f   up      = vec3f_cross_new(forward.c, right.c);

    m[0]    =   right.x;
    m[1]    =   right.y;
    m[2]    =   right.z;
    m[3]    =   0.f;
    m[4]    =   up.x;
    m[5]    =   up.y;
    m[6]    =   up.z;
    m[7]    =   0.f;
    m[8]    =   forward.x;
    m[9]    =   forward.y;
    m[10]   =   forward.z;
    m[11]   =   0.f;
    m[12]   =   from[0];
    m[13]   =   from[1];
    m[14]   =   from[2];
    m[15]   =   1.f;
}

mat4f mat4f_look_at_new(float from[3], float to[3])
{
    vec3f   forward = vec3f_sub_new(from, to);
    vec3f_normalize(forward.c);
    vec3f   right   = vec3f_cross_new((vec3f){0, 1, 0}.c, forward.c),
            up      = vec3f_cross_new(forward.c, right.c);

    return  (mat4f){    right.x,    up.x,   forward.x,  from[0],
                        right.y,    up.y,   forward.y,  from[1],
                        right.z,    up.z,   forward.z,  from[2],
                        0.f,        0.f,    0.f,        1.f     };
}

mat4f mat4ft_look_at_new(float from[3], float to[3])
{
    vec3f   forward = vec3f_sub_new(from, to);
    vec3f_normalize(forward.c);
    vec3f   right   = vec3f_cross_new((vec3f){0, 1, 0}.c, forward.c),
            up      = vec3f_cross_new(forward.c, right.c);

    return  (mat4f){    right.x,    right.y,    right.z,    0.f,
                        up.x,       up.y,       up.z,       0.f,
                        forward.x,  forward.y,  forward.z,  0.f,
                        from[0],    from[1],    from[2],    1.f };
}

mat4f mat4f_rotation_euler_new(float y, float p, float r)
{
    return  (mat4f){
        cos(y)*cos(p),  cos(y)*sin(p)*sin(r) - sin(y)*cos(r),   cos(y)*sin(p)*cos(r) - sin(y)*sin(r),   0,
        sin(y)*cos(p),  sin(y)*sin(p)*sin(r) - cos(y)*cos(r),   sin(y)*sin(p)*cos(r) - cos(y)*sin(r),   0,
        -sin(p),        cos(p)*sin(r),                          cos(p)*cos(r),                          0,
        0, 0, 0, 1
    };
}

void mat4f_rotation_euler(float y, float p, float r, float to[16])
{
    
    to[0]   = cos(y)*cos(p),
    to[1]   = cos(y)*sin(p)*sin(r) - sin(y)*cos(r),
    to[2]   = cos(y)*sin(p)*cos(r) - sin(y)*sin(r),
    to[3]   = 0,
    
    to[4]   = sin(y)*cos(p),
    to[5]   = sin(y)*sin(p)*sin(r) - cos(y)*cos(r),
    to[6]   = sin(y)*sin(p)*cos(r) - cos(y)*sin(r),
    to[7]   = 0,
    
    to[8]   = -sin(p),
    to[9]   = cos(p)*sin(r),
    to[10]  = cos(p)*cos(r),
    to[11]  = 0,
    
    to[12]  = 0,
    to[13]  = 0,
    to[14]  = 0,
    to[15]  = 1;
}

mat4f mat4ft_rotation_euler_new(float y, float p, float r)
{
    return  (mat4f){
        cos(y)*cos(p),                          sin(y)*cos(p),                          -sin(p),        0,
        cos(y)*sin(p)*sin(r) - sin(y)*cos(r),   sin(y)*sin(p)*sin(r) - cos(y)*cos(r),   cos(p)*sin(r),  0,
        cos(y)*sin(p)*cos(r) - sin(y)*sin(r),   sin(y)*sin(p)*cos(r) - cos(y)*sin(r),   cos(p)*cos(r),  0,
        0, 0, 0, 1
    };
}

void mat4ft_rotation_euler(float y, float p, float r, float to[16])
{
    to[0]   = cos(y)*cos(p),
    to[4]   = cos(y)*sin(p)*sin(r) - sin(y)*cos(r),
    to[8]   = cos(y)*sin(p)*cos(r) - sin(y)*sin(r),
    to[12]  = 0,
    
    to[1]   = sin(y)*cos(p),
    to[5]   = sin(y)*sin(p)*sin(r) - cos(y)*cos(r),
    to[9]   = sin(y)*sin(p)*cos(r) - cos(y)*sin(r),
    to[13]  = 0,
    
    to[2]   = -sin(p),
    to[6]   = cos(p)*sin(r),
    to[10]  = cos(p)*cos(r),
    to[14]  = 0,
    
    to[3]   = 0,
    to[7]   = 0,
    to[11]  = 0,
    to[15]  = 1;
}
#include "util.h"
#include "stdio.h"

namespace hlm{


/*
0, 3, 6
1, 4, 7
2, 5, 8
I use linear, column major, array.
glm uses x, y convention rather than row-column.
*/
mat3 transpose(const mat3& mat){
	mat3 m;
	m(3) = mat[1]; m(1) = mat[3];
	m(6) = mat[2]; m(2) = mat[6];
	m(5) = mat[7]; m(7) = mat[5];
	m(0) = mat[0]; m(4) = mat[4];
	m(8) = mat[8];
	return m;
}

mat3 inverseTranspose(const mat3& m){
	mat3 inv;
	float det = m[0] * (m[4] * m[8] - m[5] * m[7]) 
			  - m[1] * (m[3] * m[8] - m[5] * m[6])
			  + m[2] * (m[3] * m[7] - m[4] * m[6]);

	if(det == 0.0f){
		return inv;
	}
	det = 1.0f / det;
	inv(0) =  (m[4] * m[8] - m[7] * m[5]) * det;
	inv(1) = -(m[3] * m[8] - m[6] * m[5]) * det;
	inv(2) =  (m[3] * m[7] - m[6] * m[4]) * det;
	inv(3) = -(m[1] * m[4] - m[7] * m[2]) * det;
	inv(4) =  (m[0] * m[8] - m[6] * m[2]) * det;
	inv(5) = -(m[0] * m[7] - m[6] * m[1]) * det;
	inv(6) =  (m[1] * m[5] - m[4] * m[2]) * det;
	inv(7) = -(m[0] * m[5] - m[3] * m[2]) * det;
	inv(8) =  (m[0] * m[4] - m[3] * m[1]) * det;
    return inv;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

mat4 inverse(const mat4& m){
	mat4 inv;
    float det;
    inv( 0) =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv( 4) = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv( 8) =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv(12) = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv( 1) = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv( 5) =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv( 9) = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv(13) =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv( 2) =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv( 6) = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv(10) =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv(14) = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv( 3) = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv( 7) =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv(11) = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv(15) =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];
 
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	
    if(det == 0){
		return inv;
	}
    det = 1.0f / det;
    inv = inv * det;
    return inv;
}
/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

mat4 transpose(const mat4& mat){
	mat4 m;
	m(1) = mat[4]; m(4) = mat[1];
	m(2) = mat[8]; m(8) = mat[2];
	m(3) = mat[12];m(12)= mat[3];
	m(6) = mat[9]; m(9) = mat[6];
	m(7) = mat[13];m(13)= mat[7];
	m(11)= mat[14];m(14)=mat[11];
	m(0) = mat[0]; m(5) = mat[5];
	m(10) = mat[10]; m(15) = mat[15];
	return m;
}

void print(const vec3& v){
	printf("%6.3f, %6.3f, %6.3f\n", v.x, v.y, v.z);
}
void print(const vec4& v){
	printf("%6.3f, %6.3f, %6.3f, %6.3f\n", v.x, v.y, v.z, v.w);
}
void print(const mat3& mat){
	printf("%6.3f, %6.3f, %6.3f\n", mat[0], mat[3], mat[6]);
	printf("%6.3f, %6.3f, %6.3f\n", mat[1], mat[4], mat[7]);
	printf("%6.3f, %6.3f, %6.3f\n", mat[2], mat[5], mat[8]);
}
void print(const mat4& mat){
	printf("%6.3f, %6.3f, %6.3f, %6.3f\n", mat[0], mat[4], mat[8] , mat[12]);
	printf("%6.3f, %6.3f, %6.3f, %6.3f\n", mat[1], mat[5], mat[9] , mat[13]);
	printf("%6.3f, %6.3f, %6.3f, %6.3f\n", mat[2], mat[6], mat[10], mat[14]);
	printf("%6.3f, %6.3f, %6.3f, %6.3f\n", mat[3], mat[7], mat[11], mat[15]);
}

mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up){
	mat4 m;
	vec3 f(normalize(center - eye));
	vec3 s(normalize(cross(f, up)));
	vec3 u(cross(s, f));
	
	m(0) = s.x;
    m(4) = s.y;
    m(8) = s.z;

    m(1) = u.x;
    m(5) = u.y;
    m(9) = u.z;

    m(2)  = -f.x;
    m(6)  = -f.y;
    m(10) = -f.z;
	
	m(12) = -dot(s, eye);
	m(13) = -dot(u, eye);
	m(14) = dot(f, eye);

	return m;
}
/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/


mat4 Wmatrix(const float width, const float height){
	mat4 m;
	m(0) = width / 2.0f;
	m(5) = height / 2.0f;	// positive here because openGL texture coordinates are flipped
	m(12) = (width - 1.0f) / 2.0f;
	m(13) = (height - 1.0f) / 2.0f;
	return m;
}

mat4 Amatrix(const float hwratio, const float fov){
	mat4 m;
	float d = 1.0f;
	float w = 2.0f * d * std::tan(radians(fov / 2.0f));
	float h = hwratio * w;
	m(0) = 2.0f / w;
	m(5) = 2.0f / h;
	return m;	
}
/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/
mat4 Nmatrix(double near, double far){
	mat4 m;
	near = std::abs(near);
	far = std::abs(far);
	m(10) = -(far + near) / (far - near);
	m(14) = -(2.0 * far * near) / (far - near);
	m(11) = -1.0;
	m(15) = 0.0;
	return m;
}

// aspect = w/h
mat4 GLperspective(double fovy, double aspect, double near, double far){
	mat4 m;
	near = std::abs(near);
	far = std::abs(far);
	double ha = std::tan(radians(fovy / 2.0));
	m(0) = 1.0 / (aspect * ha);
	m(5) = 1.0 / ha;
	m(10) = -(far + near) / (far - near);
	m(14) = -(2.0 * far * near) / (far - near);
	m(11) = -1.0;
	m(15) = 0.0;
	return m;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

// normalized matrix for rotations around the origin
//http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
mat4 rotate(const vec4& v){
	mat4 m;
	if(v.w == 0.0f){
		return m;
	}
	const float c = cos(v.w);
	const float cinv = 1.0f - c;
	const float s = sin(v.w);
	const float u2 = v.x*v.x;
	const float v2 = v.y*v.y;
	const float w2 = v.z*v.z;
	
	m(0)  = u2 + (1.0f - u2) * c;
    m(4)  = v.x * v.y * cinv - v.z * s;
    m(8)  = v.x * v.z * cinv + v.y * s;
 
    m(1)  = v.x * v.y * cinv + v.z * s;
    m(5)  = v2 + (1.0f - v2) * c;
    m(9)  = v.y * v.z * cinv - v.x * s;
 
    m(2)  = v.x * v.z * cinv - v.y * s;
    m(6)  = v.y * v.z * cinv + v.x * s;
    m(10) = w2 + (1.0f - w2) * c;
	return m;
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToAngle/
vec4 eulerToAxisAngle(const vec3& in){
	vec4 v;
	vec3 c, s;
	c.x = cos(radians(in.x * 0.5f));
	c.y = cos(radians(in.y * 0.5f));
	c.z = cos(radians(in.z * 0.5f));
	s.x = sin(radians(in.x * 0.5f));
	s.y = sin(radians(in.y * 0.5f));
	s.z = sin(radians(in.z * 0.5f));
	v.w = 2.0f * acos(c.x*c.y*c.z - s.x*s.y*s.z);
	v.x = s.x*s.y*c.z + c.x*c.y*s.z;
	v.y = s.x*c.y*c.z + c.x*s.y*s.z;
	v.z = c.x*s.y*c.z - s.x*c.y*s.z;
	float len = length(vec3(v));
	if(len != 0.0f){
		v.x = v.x / len;
		v.y = v.y / len;
		v.z = v.z / len;
	}
	else {
		v.w = 0.0f;
	}
	return v;
}


}; // hlm
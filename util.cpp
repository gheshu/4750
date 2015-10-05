#include "util.h"

#include <cmath>
#include <algorithm>
#include "stdio.h"

namespace hlm{
	
float dot(const vec3& lhs, const vec3& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z;
}
float dot(const vec4& lhs, const vec4& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z + lhs.w + rhs.w;
}

float distance(const vec3& lhs, const vec3& rhs){
	return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2) 
		+ std::pow(rhs.z - lhs.z, 2));
}
float distance(const vec4& lhs, const vec4& rhs){
	return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2) 
		+ std::pow(rhs.z - lhs.z, 2) + std::pow(rhs.w - lhs.w, 2));
}

float length(const vec3& lhs){
	return distance(vec3(0.0f), lhs);
}
float length(const vec4& lhs){
	return distance(vec4(0.0f), lhs);
}

vec3 abs(const vec3& v){
	return vec3(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

vec4 abs(const vec4& v){
	return vec4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
}

mat3 inverse(const mat3& m){
	mat3 inv;
	float det = m[0] * (m[4] * m[8] - m[5] * m[7]) -
			 m[3] * (m[1] * m[8] - m[7] * m[2]) +
			 m[6] * (m[1] * m[5] - m[4] * m[2]);

	if(det == 0){
		return inv;
	}
	det = 1.0f / det;
	inv(0) = (m[4] * m[8] - m[5] * m[7]) * det;
	inv(3) = (m[6] * m[5] - m[3] * m[8]) * det;
	inv(6) = (m[3] * m[7] - m[6] * m[4]) * det;
	inv(1) = (m[7] * m[2] - m[1] * m[8]) * det;
	inv(4) = (m[0] * m[8] - m[6] * m[2]) * det;
	inv(7) = (m[1] * m[6] - m[0] * m[7]) * det;
	inv(2) = (m[1] * m[5] - m[2] * m[4]) * det;
	inv(5) = (m[2] * m[3] - m[0] * m[5]) * det;
	inv(8) = (m[0] * m[4] - m[1] * m[3]) * det;
    return inv;
}
/*
0, 3, 6
1, 4, 7
2, 5, 8
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

float fract(const float f){
	float i;
	return std::modf(f, &i);
}

vec3 fract(const vec3& v){
	float i;
	return vec3(std::modf(v.x, &i),std::modf(v.y, &i),std::modf(v.z, &i));
}
vec4 fract(const vec4& v){
	float i;
	return vec4(std::modf(v.x, &i),std::modf(v.y, &i),std::modf(v.z, &i),std::modf(v.w, &i));
}

vec3 floor(const vec3& v){
	return vec3(std::floor(v.x),std::floor(v.y),std::floor(v.z));
}
vec4 floor(const vec4& v){
	return vec4(std::floor(v.x),std::floor(v.y),std::floor(v.z), std::floor(v.w));
}

vec3 ceil(const vec3& v){
	return vec3(std::ceil(v.x),std::ceil(v.y),std::ceil(v.z));
}
vec4 ceil(const vec4& v){
	return vec4(std::ceil(v.x),std::ceil(v.y),std::ceil(v.z),std::ceil(v.w));
}

vec3 round(const vec3& v){
	return vec3(std::round(v.x),std::round(v.y),std::round(v.z));
}
vec4 round(const vec4& v){
	return vec4(std::round(v.x),std::round(v.y),std::round(v.z),std::round(v.w));
}

vec3 normalize(const vec3& v){
	float len = length(v);
	return vec3(v.x / len, v.y / len, v.z / len);
}
vec4 normalize(const vec4& v){
	float len = length(v);
	return vec4(v.x / len, v.y / len, v.z / len, v.w / len);
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

mat4 lookAt(const vec3& eye, const vec3& center, const vec3& _up){
	mat4 m;
	vec3 forward = normalize(center - eye);
	vec3 up = normalize(_up);
	vec3 side = normalize(cross(forward, up));
	up = cross(side, forward);
	
	m(0) = side.x;
    m(1) = side.y;
    m(2) = side.z;

    m(4) = up.x;
    m(5) = up.y;
    m(6) = up.z;

    m(8)  = -forward.x;
    m(9)  = -forward.y;
    m(10) = -forward.z;
	
	m(12) = -dot(side, eye);
	m(13) = -dot(up, eye);
	m(14) = -dot(forward, eye);
	return m;
}

mat4 Wmatrix(const float width, const float height){
	mat4 m;
	m(0) = width / 2.0f;
	m(5) = height / 2.0f;	// positive here because of openGL texture coordinates
	m(12) = (width - 1) / 2.0f;
	m(13) = (height - 1) / 2.0f;
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

mat4 Nmatrix(const float znear, const float zfar){
	mat4 m;
	float alpha = (znear + zfar) / (zfar - znear);
	float beta = (2.0f * znear * zfar) / (znear - zfar);
	m(10) = alpha;
	m(14) = beta;
	m(11) = -1.0f;
	return m;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

vec3 radians(const vec3& v){
	return vec3(radians(v.x), radians(v.y), radians(v.z));
}
vec4 radians(const vec4& v){
	return vec4(radians(v.x), radians(v.y), radians(v.z), radians(v.w));
}

vec3 cross(const vec3& lhs, const vec3& rhs){
	vec3 v;
	v.x = lhs.y * rhs.z - lhs.z * rhs.y;
	v.y = lhs.z * rhs.x - lhs.x * rhs.z;
	v.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return v;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

// normalized matrix for rotations around the origin
mat4 rotate(const float angle, const vec3& _v){
	mat4 m;
	vec3 v = normalize(_v);
	float c = cos(radians(angle));
	float s = sin(radians(angle));
	float u2 = v.x*v.x;
	float v2 = v.y*v.y;
	float w2 = v.z*v.z;
	
	m(0)  = u2 + (1.0f - u2) * c;
    m(4)  = v.x * v.y * (1.0f - c) - v.z * s;
    m(8)  = v.x * v.z * (1.0f - c) + v.y * s;
 
    m(1)  = v.x * v.y * (1.0f - c) + v.z * s;
    m(5)  = v2 + (1.0f - v2) * c;
    m(9)  = v.y * v.z * (1.0f - c) - v.x * s;
 
    m(2)  = v.x * v.z * (1.0f - c) - v.y * s;
    m(6)  = v.y * v.z * (1.0f - c) + v.x * s;
    m(10) = w2 + (1.0f - w2) * c;
	
	return m;
}
mat4 rotate(const vec4& _v){
	mat4 m;
	vec3 v = normalize(vec3(_v.x, _v.y, _v.z));
	float c = cos(radians(_v.w));
	float s = sin(radians(_v.w));
	float u2 = v.x*v.x;
	float v2 = v.y*v.y;
	float w2 = v.z*v.z;
	
	m(0)  = u2 + (1.0f - u2) * c;
    m(4)  = v.x * v.y * (1.0f - c) - v.z * s;
    m(8)  = v.x * v.z * (1.0f - c) + v.y * s;
 
    m(1)  = v.x * v.y * (1.0f - c) + v.z * s;
    m(5)  = v2 + (1.0f - v2) * c;
    m(9)  = v.y * v.z * (1.0f - c) - v.x * s;
 
    m(2)  = v.x * v.z * (1.0f - c) - v.y * s;
    m(6)  = v.y * v.z * (1.0f - c) + v.x * s;
    m(10) = w2 + (1.0f - w2) * c;
	
	return m;
}
mat4 scale(const vec3& v){
	mat4 m;
	m(0) = v.x;
	m(5) = v.y;
	m(10) = v.z;
	return m;
}
mat4 scale(const vec4& v){
	mat4 m;
	m(0) = v.x;
	m(5) = v.y;
	m(10) = v.z;
	return m;
}
mat4 translate(const vec3& v){
	mat4 m;
	m(12) = v.x;
	m(13) = v.y;
	m(14) = v.z;
	return m;
}
mat4 translate(const vec4& v){
	mat4 m;
	m(12) = v.x;
	m(13) = v.y;
	m(14) = v.z;
	return m;
}

const float* value_ptr(vec3& v){
	return &v.x;
}
const float* value_ptr(vec4& v){
	return &v.x;
}
const float* value_ptr(mat3& m){
	return &m(0);
}
const float* value_ptr(mat4& m){
	return &m(0);
}

}; // hlm
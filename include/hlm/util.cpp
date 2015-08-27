#include "util.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "stdio.h"

namespace hlm{

float dot(vec3& lhs, vec3& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z;
}
float dot(vec4& lhs, vec4& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z + lhs.w + rhs.w;
}

float distance(vec3& lhs, vec3& rhs){
	return sqrt(pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2) 
		+ pow(rhs.z - lhs.z, 2));
}
float distance(vec4& lhs, vec4& rhs){
	return sqrt(pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2) 
		+ pow(rhs.z - lhs.z, 2) + pow(rhs.w - lhs.w, 2));
}

float length(vec3& lhs){
	return distance(vec3(0.0f), lhs);
}
float length(vec4& lhs){
	return distance(vec4(0.0f, lhs);
}

void abs(vec3& v){
	v.x = abs(v.x); v.y = abs(v.y);
	v.z = abs(v.z);
}
void abs(vec4& v){
	v.x = abs(v.x); v.y = abs(v.y);
	v.z = abs(v.z); v.w = abs(v.w);
}

void inverse(mat3& mat){
	
}
void transpose(mat3& mat){
	
}

bool inverse(mat4& mat){
{
	mat4 inv;
    float det;
 
    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];
 
    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
 
    if(det == 0)
        return false;
 
    det = 1.f / det;
 
    for(int i = 0; i < 16; i++){
        mat[i] = inv[i] * det;
	}
 
    return true;
}

}
void transpose(mat4& mat){
	
}

float fract(float f){
	float intpart;
	return modf(f, &intpart);
}
void fract(vec3& v){
	float intpart;
	v.x = modf(v.x, &intpart);
	v.y = modf(v.y, &intpart);
	v.z = modf(v.z, &intpart);
}
void fract(vec4& v){
	float intpart;
	v.x = modf(v.x, &intpart);
	v.y = modf(v.y, &intpart);
	v.z = modf(v.z, &intpart);
	v.w = modf(v.w, &intpart);
}

void normalize(vec3& v){
	float len = length(v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
}
void normalize(vec4& v){
	float len = length(v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	v.w /= len;
}

void print(vec3& v){
	printf("%f, %f, %f\n", v.x, v.y, v.z);
}
void print(vec4& v){
	printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w);
}
void print(mat3& mat){
	printf("%f, %f, %f\n", mat[0], mat[3], mat[6]);
	printf("%f, %f, %f\n", mat[1], mat[4], mat[7]);
	printf("%f, %f, %f\n", mat[2], mat[5], mat[8]);
}
void print(mat4& mat){
	printf("%f, %f, %f, %f\n", mat[0], mat[4], mat[8] , mat[12]);
	printf("%f, %f, %f, %f\n", mat[1], mat[5], mat[9] , mat[13]);
	printf("%f, %f, %f, %f\n", mat[2], mat[6], mat[10], mat[14]);
	printf("%f, %f, %f, %f\n", mat[3], mat[7], mat[11], mat[15]);
}

mat4 lookAt(vec3& position, vec3& at, vec3& up);
mat4 perspective(float fov, float WHaspect, float near, float far);
mat4 ortho(float left, float right, float top, float bottom, float znear, float zfar);

}; // hlm
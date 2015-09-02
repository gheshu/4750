#include "util.h"

#include "math.h"
#include "stdio.h"

namespace hlm{
	
float dot(const vec3& lhs, const vec3& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z;
}
float dot(const vec4& lhs, const vec4& rhs){
	return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z + lhs.w + rhs.w;
}

float distance(const vec3& lhs, const vec3& rhs){
	return sqrt(pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2) 
		+ pow(rhs.z - lhs.z, 2));
}
float distance(const vec4& lhs, const vec4& rhs){
	return sqrt(pow(rhs.x - lhs.x, 2) + pow(rhs.y - lhs.y, 2) 
		+ pow(rhs.z - lhs.z, 2) + pow(rhs.w - lhs.w, 2));
}

float length(const vec3& lhs){
	return distance(vec3(0.0f), lhs);
}
float length(const vec4& lhs){
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

bool inverse(const mat3& m, mat3& inv){
	float det = m[0] * (m[4] * m[8] - m[5] * m[7]) -
			 m[3] * (m[1] * m[8] - m[7] * m[2]) +
			 m[6] * (m[1] * m[5] - m[4] * m[2]);

	if(det == 0){
		return false;
	}
	det = 1.0f / det;

	inv[0] = (m[4] * m[8] - m[5] * m[7]) * det;
	inv[3] = (m[6] * m[5] - m[3] * m[8]) * det;
	inv[6] = (m[3] * m[7] - m[6] * m[4]) * det;
	inv[1] = (m[7] * m[2] - m[1] * m[8]) * det;
	inv[4] = (m[0] * m[8] - m[6] * m[2]) * det;
	inv[7] = (m[1] * m[6] - m[0] * m[7]) * det;
	inv[2] = (m[1] * m[5] - m[2] * m[4]) * det;
	inv[5] = (m[2] * m[3] - m[0] * m[5]) * det;
	inv[8] = (m[0] * m[4] - m[1] * m[3]) * det;
	
    return true;
}
/*
0, 3, 6
1, 4, 7
2, 5, 8
*/
void transpose(mat3& mat){
	std::swap(mat[1], mat[3]);
	std::swap(mat[2], mat[6]);
	std::swap(mat[5], mat[7]);
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

bool inverse(const mat4& m, mat4& inv){
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
	
    if(det == 0){
		return false;
	}
    det = 1.0f / det;
    inv *= det;
    return true;
}
/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

void transpose(mat4& mat){
	std::swap(mat[1], mat[4]);
	std::swap(mat[2], mat[8]);
	std::swap(mat[3], mat[12]);
	std::swap(mat[6], mat[9]);
	std::swap(mat[7], mat[13]);
	std::swap(mat[11], mat[14]);
}

float fract(const float f){
	float i;
	return modf(f, &i);
}

void fract(vec3& v){
	float i;
	v.x = modf(v.x, &i);
	v.y = modf(v.y, &i);
	v.z = modf(v.z, &i);
}
void fract(vec4& v){
	float i;
	v.x = modf(v.x, &i);
	v.y = modf(v.y, &i);
	v.z = modf(v.z, &i);
	v.w = modf(v.w, &i);
}

void floor(vec3& v){
	v.x = floor(v.x);
	v.y = floor(v.y);
	v.z = floor(v.z);
}
void floor(vec4& v){
	v.x = floor(v.x);
	v.y = floor(v.y);
	v.z = floor(v.z);
	v.w = floor(v.w);
}

void ceil(vec3& v){
	v.x = ceil(v.x);
	v.y = ceil(v.y);
	v.z = ceil(v.z);
}
void ceil(vec4& v){
	v.x = ceil(v.x);
	v.y = ceil(v.y);
	v.z = ceil(v.z);
	v.w = ceil(v.w);
}

void round(vec3& v){
	v.x = round(v.x);
	v.y = round(v.y);
	v.z = round(v.z);
}
void round(vec4& v){
	v.x = round(v.x);
	v.y = round(v.y);
	v.z = round(v.z);
	v.w = round(v.w);
}

void abs(vec3& v){
	v.x = abs(v.x);
	v.y = abs(v.y);
	v.z = abs(v.z);
}
void abs(vec4& v){
	v.x = abs(v.x);
	v.y = abs(v.y);
	v.z = abs(v.z);
	v.w = abs(v.w);
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

void print(const vec3& v){
	printf("%f, %f, %f\n", v.x, v.y, v.z);
}
void print(const vec4& v){
	printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w);
}
void print(const mat3& mat){
	printf("%f, %f, %f\n", mat[0], mat[3], mat[6]);
	printf("%f, %f, %f\n", mat[1], mat[4], mat[7]);
	printf("%f, %f, %f\n", mat[2], mat[5], mat[8]);
}
void print(const mat4& mat){
	printf("%f, %f, %f, %f\n", mat[0], mat[4], mat[8] , mat[12]);
	printf("%f, %f, %f, %f\n", mat[1], mat[5], mat[9] , mat[13]);
	printf("%f, %f, %f, %f\n", mat[2], mat[6], mat[10], mat[14]);
	printf("%f, %f, %f, %f\n", mat[3], mat[7], mat[11], mat[15]);
}

void lookAt(const mat4& m, const vec3& eye, const vec3& center, const vec3& _up){
	vec3 forward = center - eye;
	normalize(forward);
	vec3 up = _up;
	normalize(up);
	vec3 side;
	cross(forward, up, side);
	normalize(side);
	cross(side, forward, up);
	m[0] = side.x;
    m[1] = side.y;
    m[2] = side.z;

    m[4] = up.x;
    m[5] = up.y;
    m[6] = up.z;

    m[8]  = -forward.x;
    m[9]  = -forward.y;
    m[10] = -forward.z;
	
	m[12] = -dot(side, eye);
	m[13] = -dot(up, eye);
	m[14] = -dot(forward, eye);
}

void perspective(const mat4& m, const float fov, const float WHaspect, const float near, const float far){
	float sine, cotangent, deltaZ;
	float radians = fov / 2.0f * PI80;
	deltaZ = far - near;
	sine = sin(radians);
	if((deltaZ == 0) || (sine == 0) || (aspect == 0)){
		printf("invalid parameters to hlm::perspective\n");
		return m;
	}
	cotangent  = cos(radians) / sine;
	m[0] = cotangent / aspect;
    m[5] = cotangent;
    m[10] = -(zFar + zNear) / deltaZ;
    m[14] = -1.0f;
    m[11] = -2.0f * zNear * zFar / deltaZ;
    m[15] = 0.0f;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

void ortho(const mat4& m, const float left, const float right, const float top, const float bottom, const float znear, const float zfar){
	m[0] = 2.0f / (right - left);
	m[5] = 2.0f / (top - bottom);
	m[10] = 2.0f / (zfar - znear);
	m[3] = (right + left) / (right - left);
	m[7] = (top + bottom) / (top - bottom);
	m[11] = (zfar + znear) / (zfar - znear);
}

void cross(const vec3& lhs, const vec3& rhs, const vec3& v){
	v.x = lhs.y * rhs.z - lhs.z * rhs.y;
	v.y = lhs.z * rhs.x - lhs.x * rhs.z;
	v.z = lhs.x * rhs.y - lhs.y * rhs.x;
}

void rotate(mat4& in, const float angle, const vec3& v){
	
}
void scale(mat4& in, const vec3& v){
	
}
void translate(mat4& in, const vec3& v){
	
}

vec3 const * value_ptr(const vec3& v){
	return &v.x;
}
vec4 const * value_ptr(const vec4& v){
	return &v.x;
}
mat3 const * value_ptr(const mat3& m){
	return &m[0];
}
mat4 const * value_ptr(const mat4& m){
	return &m[0];
}

}; // hlm
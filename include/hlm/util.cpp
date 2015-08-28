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

vec3 abs(const vec3& v){
	vec3 r;
	r.x = abs(v.x); r.y = abs(v.y);
	r.z = abs(v.z);
	return r;
}

vec4 abs(const vec4& v){
	vec4 r;
	r.x = abs(v.x); r.y = abs(v.y);
	r.z = abs(v.z); r.w = abs(v.w);
	return r;
}

mat3 inverse(const mat3& mat){
	mat3 inv;
	float det;
	
	
	
	if(det == 0){
		return inv;
	}
    det = 1.0f / det;
    inv *= det;
    return inv;
}
/*
0, 3, 6
1, 4, 7
2, 5, 8
*/
mat3 transpose(const mat3& mat){
	mat3 m;
	m[0] = mat[0]; m[1] = mat[3]; m[2] = mat[6];
	m[3] = mat[1]; m[4] = mat[4]; m[5] = mat[7];
	m[6] = mat[2]; m[7] = mat[5]; m[8] = mat[8];
	return m;
}

mat4 inverse(const mat4& m){
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
	
    if(det == 0){
		return inv;
	}
    det = 1.0f / det;
    inv *= det;
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
	m[0]  = mat[0];  m[1]  = mat[4]; m[2]  = mat[8];  m[3]  = mat[12];
	m[4]  = mat[1];  m[5]  = mat[5]; m[6]  = mat[9];  m[7]  = mat[13];
	m[8]  = mat[11]; m[9]  = mat[6]; m[10] = mat[10]; m[11] = mat[14];
	m[12] = mat[3];  m[13] = mat[7]; m[14] = mat[11]; m[15] = mat[15];
	return m;
}

float fract(const float f){
	float i;
	return modf(f, &i);
}

void fract(const vec3& v){
	float i;
	return vec3(modf(v.x, &i), modf(v.y, &i), modf(v.z, &i));
}
void fract(const vec4& v){
	float i;
	return vec4(modf(v.x, &i), modf(v.y, &i), modf(v.z, &i), modf(v.w, &i));
}

vec3 floor(const vec3& v){
	return vec3(floor(v.x), floor(v.y), floor(v.z));
}
vec4 floor(const vec4& v){
	return vec4(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}

vec3 ceil(const vec3& v){
	return vec3(ceil(v.x), ceil(v.y), ceil(v.x));
}
vec4 ceil(const vec4& v){
	return vec4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}

vec3 abs(const vec3& v){
	return vec3(abs(v.x), abs(v.y), abs(v.z));
}
vec4 abs(const vec4& v){
	return vec4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

vec3 normalize(const vec3& v){
	vec3 r;
	float len = length(v);
	r.x /= len;
	r.y /= len;
	r.z /= len;
	return r;
}
vec4 normalize(const vec4& v){
	vec4 r;
	float len = length(v);
	r.x /= len;
	r.y /= len;
	r.z /= len;
	r.w /= len;
	return r;
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

mat4 lookAt(const vec3& eye, const vec3& center, const vec3& _up){
	vec3 forward = normalize(center - eye);
	vec3 up = normalize(_up);
	vec3 side = normalize(cross(forward, up));
	up = cross(side, forward);
	mat4 m;
	m[0] = side.x;
    m[1] = side.y;
    m[2] = side.z];

    m[4] = up.x;
    m[5] = up.y;
    m[6] = up.z;

    m[8]  = -forward.x;
    m[9]  = -forward.y;
    m[10] = -forward.z;
	
	m[12] = -dot(side, eye);
	m[13] = -dot(up, eye);
	m[14] = -dot(forward, eye);
	return m;
}

mat4 perspective(const float fov, const float WHaspect, const float near, const float far){
	mat4 m;
	float sine, cotangent, deltaZ;
	float radians = fov / 2.0f * PI80;
	deltaZ = far - near;
	sine = sin(radians);
	if((deltaZ == 0) || (sine == 0) || (aspect == 0)){
		printf("invalid parameters to hlm::perspective\n");
		return m;
	}
	cotangent  = cos(radians) / sine;
	m[0][0] = cotangent / aspect;
    m[1][1] = cotangent;
    m[2][2] = -(zFar + zNear) / deltaZ;
    m[2][3] = -1.0f;
    m[3][2] = -2.0f * zNear * zFar / deltaZ;
    m[3][3] = 0.0f;
	return m;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

mat4 ortho(const float left, const float right, const float top, const float bottom, const float znear, const float zfar){
	mat4 m;
	m[0] = 2.0f / (right - left);
	m[5] = 2.0f / (top - bottom);
	m[10] = 2.0f / (zfar - znear);
	m[3] = (right + left) / (right - left);
	m[7] = (top + bottom) / (top - bottom);
	m[11] = (zfar + znear) / (zfar - znear);
	return m;
}

vec3 cross(const vec3& lhs, const vec3& rhs){
	vec3 v;
	v.x = lhs.y * rhs.z - lhs.z * rhs.y;
	v.y = lhs.z * rhs.x - lhs.x * rhs.z;
	v.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return v;
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
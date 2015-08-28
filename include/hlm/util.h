#ifndef HLM_UTIL_H
#define HLM_UTIL_H

#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

namespace hlm{
	
constexpr float PI = 3.14159265358979f;
constexpr float PI80 = PI / 180.0f;

float dot(const vec3& lhs, const vec3& rhs);
float dot(const vec4& lhs, const vec4& rhs);

float distance(const vec3& lhs, const vec3& rhs);
float distance(const vec4& lhs, const vec4& rhs);

float length(const vec3& lhs);
float length(const vec4& lhs);

vec3 abs(const vec3& v);
vec3 abs(const vec4& v);

mat3 inverse(const mat3& mat);
mat3 transpose(const mat3& mat);

mat4 inverse(const mat4& mat):
mat4 transpose(const mat4& mat);

float fract(const float f);
vec3 fract(const vec3& v);
vec4 fract(const vec4& v);

vec3 floor(const vec3& v);
vec4 floor(const vec4& v);

vec3 ceil(const vec3& v);
vec4 ceil(const vec4& v);

vec3 abs(const vec3& v);
vec4 abs(const vec4& v);

vec3 normalize(const vec3& v);
vec4 normalize(const vec4& v);

void print(const vec3& v);
void print(const vec4& v);
void print(const mat3& mat);
void print(const mat4& mat);

mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4 perspective(const float fov, const float WHaspect, const float near, const float far);
mat4 ortho(const float left, const float right, const float top, const float bottom, const float znear, const float zfar);

inline float radians(const float degrees){ return degrees * PI80; }

vec3 cross(const vec3& lhs, const vec3& rhs);

vec3 const * value_ptr(const vec3& v);
vec4 const * value_ptr(const vec4& v);
mat3 const * value_ptr(const mat3& m);
mat4 const * value_ptr(const mat4& m);

};

#endif // HLM_UTIL_H
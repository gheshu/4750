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

void abs( vec3& v);
void abs( vec4& v);

bool inverse(const mat3& in, mat3& out);
void transpose( mat3& mat);

bool inverse(const mat4& in, mat4& out);
void transpose( mat4& mat);

float fract(const float f);
void fract( vec3& v);
void fract( vec4& v);

void floor( vec3& v);
void floor( vec4& v);

void ceil( vec3& v);
void ceil( vec4& v);

void round( vec3& v);
void round( vec4& v);

void abs( vec3& v);
void abs( vec4& v);

void normalize( vec3& v);
void normalize( vec4& v);

void print(const vec3& v);
void print(const vec4& v);
void print(const mat3& mat);
void print(const mat4& mat);

void lookAt(const mat4& m, const vec3& eye, const vec3& center, const vec3& up);	// side = m0,1,2, up = m4,5,6, -forward = m8,9,10

inline float radians(const float degrees){ return degrees * PI80; }

void cross(const vec3& lhs, const vec3& rhs, vec3& out);

const float * value_ptr(const vec3& v);
const float * value_ptr(const vec4& v);
const float * value_ptr(const mat3& m);
const float * value_ptr(const mat4& m);

void rotate(mat4& in, const float angle, const vec3& v);
void scale(mat4& in, const vec3& v);
void translate(mat4& in, const vec3& v);

};

#endif // HLM_UTIL_H
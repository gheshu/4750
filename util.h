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

float length(const vec3& v);
float length(const vec4& v);

mat3 inverse(const mat3& in);
mat3 transpose( const mat3& mat);

mat4 inverse(const mat4& in);
mat4 transpose( const mat4& mat);

float fract(const float f);
vec3 fract( const vec3& v);
vec4 fract( const vec4& v);

vec3 floor( const vec3& v);
vec4 floor( const vec4& v);

vec3 ceil( const vec3& v);
vec4 ceil( const vec4& v);

vec3 round( const vec3& v);
vec4 round( const vec4& v);

vec3 abs( const vec3& v);
vec4 abs( const vec4& v);

int clamp(const int low, const int high, const int val);
float clamp(const float low, const float high, const float val);

vec3 normalize( const vec3& v);
vec4 normalize( const vec4& v);

void print(const vec3& v);
void print(const vec4& v);
void print(const mat3& mat);
void print(const mat4& mat);

mat4 lookAt(const vec3& eye, const vec3& at, const vec3& up);	// side = m0,1,2, up = m4,5,6, -forward = m8,9,10

vec3 getForward(const mat4& mat);
vec3 getRight(const mat4& mat);
vec3 getUp(const mat4& mat);
float getPitch(const mat4& mat);
float getYaw(const mat4& mat);
float getRoll(const mat4& mat);

mat4 Wmatrix(const float width, const float height);
mat4 Amatrix(const float hwratio = 9.0f / 16.0f, const float fov = 90.0f);
mat4 Nmatrix(const double znear, const double zfar);

// aspect here is width / height of the window.
// must divide by 4th element of vec4 to normalize your points if using this matrix.
mat4 GLperspective(double fovy, double aspect, double znear, double zfar);

inline float radians(const float degrees){ return degrees * PI80; }

vec3 radians(const vec3& v);
vec4 radians(const vec4& v);

vec3 cross(const vec3& lhs, const vec3& rhs);

const float * value_ptr(vec3& v);
const float * value_ptr(vec4& v);
const float * value_ptr(mat3& m);
const float * value_ptr(mat4& m);

mat4 rotate(const float angle, const vec3& v);
mat4 scale(const vec3& v);
mat4 translate(const vec3& v);

mat4 rotate(const vec4& v);
mat4 scale(const vec4& v);
mat4 translate(const vec4& v);

};

#endif // HLM_UTIL_H
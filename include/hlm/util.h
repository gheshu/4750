#ifndef HLM_UTIL_H
#define HLM_UTIL_H

namespace hlm{

class vec3;
class vec4;
class mat3;
class mat4;

float dot(vec3& lhs, vec3& rhs);
float dot(vec4& lhs, vec4& rhs);

float distance(vec3& lhs, vec3& rhs);
float distance(vec4& lhs, vec4& rhs);

float length(vec3& lhs);
float length(vec4& lhs);

void abs(vec3& v);
void abs(vec4& v);

void inverse(mat3& mat);
void transpose(mat3& mat);

void inverse(mat4& mat):
void transpose(mat4& mat);

float fract(float f);
void fract(vec3& v);
void fract(vec4& v);

void normalize(vec3& v);
void normalize(vec4& v);

void print(vec3& v);
void print(vec4& v);
void print(mat3& mat);
void print(mat4& mat);

mat4 lookAt(vec3& position, vec3& at, vec3& up);
mat4 perspective(float fov, float WHaspect, float near, float far);
mat4 ortho(float left, float right, float top, float bottom, float znear, float zfar);

};

#endif // HLM_UTIL_H
#ifndef VEC3_H
#define VEC3_H

namespace hlm{

class mat3;

class vec3{
public:
float x, y, z;
	vec3(const float x, const float y, const float z);
	vec3();
	~vec3();
	vec3 operator+(const vec3& lhs, const vec3& rhs);
	vec3 operator+(const vec3& v, const float f);
	vec3 operator+(const float f, const vec3& v);
	vec3 operator-(const vec3& lhs, const vec3& rhs);
	vec3 operator-(const vec3& v, const float f);
	vec3 operator-(const float f, const vec3& v);
	vec3 operator*(const vec3& lhs, const vec3& rhs);
	vec3 operator*(const vec3& v, const float f);
	vec3 operator*(const float f, const vec3& v);
	vec3 operator*(mat3& mat, const vec3& v);
	vec3 operator*(const vec3& v, mat3& mat);
	vec3 operator/(const vec3& lhs, const vec3& rhs);
	vec3 operator/(const vec3& v, const float f);
	vec3 operator/(const float f, const vec3& v);
	vec3 operator/(mat3& mat, const vec3& v);
	vec3 operator/(const vec3& v, mat3& mat);
}; // vec3
}; // hlm
#endif // define VEC3_H
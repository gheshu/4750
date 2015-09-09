#ifndef VEC3_H
#define VEC3_H

namespace hlm{
// column major
class mat3;
class vec4;

class vec3{
public:
float x, y, z;
	vec3();
	vec3(const float s);
	vec3(const float x, const float y, const float z);
	vec3(const vec3& other);
	vec3(vec4& other);
	
	inline vec3& operator =(const vec3& v){x = v.x; y = v.y; z = v.z; return *this;};
	vec3& operator+=(const vec3& v);
	vec3& operator+=(const float s);
	vec3& operator-=(const vec3& v);
	vec3& operator-=(const float s);
	vec3& operator*=(const float s);
	vec3& operator/=(const float s);
	
}; // vec3

	const vec3 operator+(const vec3& lhs, const vec3& rhs);
	const vec3 operator+(const vec3& v, const float f);
	const vec3 operator+(const float f, const vec3& v);
	const vec3 operator-(const vec3& lhs, const vec3& rhs);
	const vec3 operator-(const vec3& v, const float f);
	const vec3 operator-(const float f, const vec3& v);
	const vec3 operator*(const vec3& lhs, const vec3& rhs);
	const vec3 operator*(const vec3& v, const float f);
	const vec3 operator*(const float f, const vec3& v);
	const vec3 operator/(const vec3& v, const float f);
	const vec3 operator/(const float f, const vec3& v);
	const vec3 operator*(const mat3& mat, const vec3& v);

}; // hlm
#endif // define VEC3_H
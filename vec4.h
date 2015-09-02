#ifndef VEC4_H
#define VEC4_H

namespace hlm{
// column major
class mat4;

class vec4{
public:
float x, y, z, w;
	vec4();
	vec4(float x, float y, float z, float w);
	vec4(float s);
	vec4(const vec4& other);
	vec4(const vec3& other);
	
	vec4 operator+(const vec4& lhs, const vec4& rhs);
	vec4 operator-(const vec4& lhs, const vec4& rhs);
	vec4 operator*(const vec4& lhs, const vec4& rhs);
	
	vec4 operator+(const float s, const vec4& v);
	vec4 operator-(const float s, const vec4& v);
	vec4 operator*(const float s, const vec4& v);
	vec4 operator/(const float s, const vec4& v);
	
	vec4 operator+(const vec4& v, const float s);
	vec4 operator-(const vec4& v, const float s);
	vec4 operator*(const vec4& v, const float s);
	vec4 operator/(const vec4& v, const float s);
	
	vec4& operator =(const vec4& other);
	vec4& operator+=(const vec4& other);
	vec4& operator-=(const vec4& other);
	
	vec4& operator+=(const float s);
	vec4& operator-=(const float s);
	vec4& operator*=(const float s);
	vec4& operator/=(const float s);
	
	vec4 operator*(mat4& mat, vec4& vec);
	
}; // vec4
}; // hlm

#endif // define VEC4_H
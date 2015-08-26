#include "vec3.h"
#include "mat3.h"

namespace hlm{

vec3::vec3(const float _x, const float _y, const float _z){
	x = _x; y = _y; z = _z;
}

vec3::vec3(){
	x = 0.0f; y = 0.0f; z = 0.0f;
}

vec3 vec3::operator*(const vec3& lhs, const vec3& rhs){
	float x = (lhs.x * rhs.z) - (lhs.z * rhs.y);
	float y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
	float z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
	return vec3(x, y, z);
}

vec3 vec3::operator*(const vec3& v, const float f){
	return vec3(v.x * f, v.y * f, v.z * f);
}

vec3 vec3::operator*(const float f, const vec3& v){
	return vec3(v.x * f, v.y * f, v.z * f);
}

vec3 vec3::operator*(mat3& mat, const vec3& v){
	
}

vec3 vec3::operator*(const vec3& v, mat3& mat){

}

vec3 vec3::operator/(mat3& mat, const vec3& v){

}

vec3 vec3::operator/(const vec3& v, mat3& mat){
}

vec3 vec3::operator/(const vec3& lhs, const vec3& rhs){
	vec3 inverse = vec3(1.0f / lhs.x, 1.0f / lhs.y, 1.0f / lhs.z);
	return inverse * rhs;
}

vec3 vec3::operator/(const vec3& v, const float f){
	return vec3(v.x / f, v.y / f, v.z / f);
}

vec3 vec3::operator/(const float f, const vec3& v){
	return vec3(f / v.x, f / v.y, f / v.z);
}

vec3 vec3::operator+(const vec3& lhs, const vec3& rhs){
	return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

vec3 vec3::operator+(const float f, const vec3& v){
	return vec3(f + v.x, f + v.y, f + v.z);
}

vec3 vec3::operator+(const vec3& v, const float f){
	return vec3(v.x + f, v.y + f, v.z + f);
}

vec3 vec3::operator-(const vec3& lhs, const vec3& rhs){
	return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

vec3 vec3::operator-(const vec3& v, const float f){
	return vec3(v.x - f, v.y - f, v.z - f);
}

vec3 vec3::operator-(const float f, const vec3& v){
	return vec3(f - v.x, f - v.y, f - v.z);
}

};
#include "mat3.h"

#include "vec3.h"
#include <algorithm>

namespace hlm{

mat3::mat3(){
	data[0] = 1.0f; data[1] = 0.0f; data[2] = 0.0f;
	data[3] = 0.0f; data[4] = 1.0f; data[5] = 0.0f;
	data[6] = 0.0f; data[7] = 0.0f; data[8] = 1.0f;
}

mat3::mat3(const float s){
	data[0] = s;    data[1] = 0.0f; data[2] = 0.0f;
	data[3] = 0.0f; data[4] = s;    data[5] = 0.0f;
	data[6] = 0.0f; data[7] = 0.0f; data[8] = s;
}

mat3::mat3(float* array){
	std::copy(array, array + 9, &data[0]);
}

mat3::mat3(mat4& m){
	data[0] = m[0]; data[1] = m[1]; data[2] = m[2];
	data[3] = m[4]; data[4] = m[5]; data[5] = m[6];
	data[6] = m[8]; data[7] = m[9]; data[8] = m[10];
}

mat3& mat3::operator=(const mat3& other){
	std::copy(&other.data[0], &other.data[9], &data[0]);
	return *this;
}

mat3 mat3::operator*(const mat3& lhs, const mat3& rhs){
	mat3 m;
	// COLUMN MAJOR to comply with openGL
	// lhs horizontal
	// rhs vertical
	m[0] = lhs[0] * rhs[0] + lhs[3] * rhs[1] + lhs[6] * rhs[2];
	m[1] = lhs[1] * rhs[0] + lhs[4] * rhs[1] + lhs[7] * rhs[2];
	m[2] = lhs[2] * rhs[0] + lhs[5] * rhs[1] + lhs[8] * rhs[2];
	
	m[3] = lhs[0] * rhs[3] + lhs[3] * rhs[4] + lhs[6] * rhs[5];
	m[4] = lhs[1] * rhs[3] + lhs[4] * rhs[4] + lhs[7] * rhs[5];
	m[5] = lhs[2] * rhs[3] + lhs[5] * rhs[4] + lhs[8] * rhs[5];
	
	m[6] = lhs[0] * rhs[6] + lhs[3] * rhs[7] + lhs[6] * rhs[8];
	m[7] = lhs[1] * rhs[6] + lhs[4] * rhs[7] + lhs[7] * rhs[8];
	m[8] = lhs[2] * rhs[6] + lhs[5] * rhs[7] + lhs[8] * rhs[8];
	return m;
}

mat3 mat3::operator+(const mat3& mat, const float s){
	mat3 m;
	m[0] = s + mat[0]; m[1] = s + mat[1]; m[2] = s + mat[2];
	m[3] = s + mat[3]; m[4] = s + mat[4]; m[5] = s + mat[5];
	m[6] = s + mat[6]; m[7] = s + mat[7]; m[8] = s + mat[8];
	return m;
}

mat3 mat3::operator+(const float s, const mat3& mat){
	mat3 m;
	m[0] = s + mat[0]; m[1] = s + mat[1]; m[2] = s + mat[2];
	m[3] = s + mat[3]; m[4] = s + mat[4]; m[5] = s + mat[5];
	m[6] = s + mat[6]; m[7] = s + mat[7]; m[8] = s + mat[8];
	return m;
}

mat3 mat3::operator+(const mat3& lhs, const mat3& rhs){
	mat3 m;
	m[0] = lhs[0] + rhs[0]; m[1] = lhs[1] + rhs[1]; m[2] = lhs[2] + rhs[2];
	m[3] = lhs[3] + rhs[3]; m[4] = lhs[4] + rhs[4]; m[5] = lhs[5] + rhs[5];
	m[6] = lhs[6] + rhs[6]; m[7] = lhs[7] + rhs[7]; m[8] = lhs[8] + rhs[8];
	return m;
}

mat3 mat3::operator-(const mat3& lhs, const mat3& rhs){
	mat3 m;
	m[0] = lhs[0] - rhs[0]; m[1] = lhs[1] - rhs[1]; m[2] = lhs[2] - rhs[2];
	m[3] = lhs[3] - rhs[3]; m[4] = lhs[4] - rhs[4]; m[5] = lhs[5] - rhs[5];
	m[6] = lhs[6] - rhs[6]; m[7] = lhs[7] - rhs[7]; m[8] = lhs[8] - rhs[8];
	return m;
}

mat3 mat3::operator-(const mat3& mat, const float s){
	mat3 m;
	m[0] = mat[0] - s; m[1] = mat[1] - s; m[2] = mat[2] - s;
	m[3] = mat[3] - s; m[4] = mat[4] - s; m[5] = mat[5] - s;
	m[6] = mat[6] - s; m[7] = mat[7] - s; m[8] = mat[8] - s;
	return m;
}

mat3 mat3::operator-(const float s, const mat3& mat){
	mat3 m;
	m[0] = s + mat[0]; m[1] = s + mat[1]; m[2] = s + mat[2];
	m[3] = s + mat[3]; m[4] = s + mat[4]; m[5] = s + mat[5];
	m[6] = s + mat[6]; m[7] = s + mat[7]; m[8] = s + mat[8];
	return m;
}

mat3 mat3::operator*(const float s, const mat3& mat){
	mat3 m;
	m[0] = s * mat[0]; m[1] = s * mat[1]; m[2] = s * mat[2];
	m[3] = s * mat[3]; m[4] = s * mat[4]; m[5] = s * mat[5];
	m[6] = s * mat[6]; m[7] = s * mat[7]; m[8] = s * mat[8];
	return m;
}

mat3 mat3::operator*(const mat3& mat, const float s){
	mat3 m;
	m[0] = s * mat[0]; m[1] = s * mat[1]; m[2] = s * mat[2];
	m[3] = s * mat[3]; m[4] = s * mat[4]; m[5] = s * mat[5];
	m[6] = s * mat[6]; m[7] = s * mat[7]; m[8] = s * mat[8];
	return m;
}

mat3 mat3::operator/(const float s, const float mat3& mat){
	mat3 m;
	m[0] = s / mat[0]; m[1] = s / mat[1]; m[2] = s / mat[2];
	m[3] = s / mat[3]; m[4] = s / mat[4]; m[5] = s / mat[5];
	m[6] = s / mat[6]; m[7] = s / mat[7]; m[8] = s / mat[8];
	return m;
}

mat3 mat3::operator/(const mat3& mat, const float s){
	mat3 m;
	m[0] = mat[0] / s; m[1] = mat[1] / s; m[2] = mat[2] / s;
	m[3] = mat[3] / s; m[4] = mat[4] / s; m[5] = mat[5] / s;
	m[6] = mat[6] / s; m[7] = mat[7] / s; m[8] = mat[8] / s;
	return m;
}

};
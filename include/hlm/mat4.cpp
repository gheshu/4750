#include "mat4.h"
#include "vec4.h"
#include <algorithm>

mat4::mat4(){
	std::fill(data[0], data[16], 0.0f);
	data[0] = 1.0f; data[5] = 1.0f; data[10] = 1.0f; data[15] = 1.0f;
}

mat4::mat4(const float s){
	std::fill(data[0], data[16], 0.0f);
	data[0] = s; data[5] = s; data[10] = s; data[15] = s;
}

mat4::mat4(const mat4& other){
	std::copy(&other.data[0], &other.data[9], &data[0]);
}

mat4::mat4(float* array){
	std::copy(array, array + 9, &data[0]);
}

mat4 mat4::operator+(const mat4& lhs, const mat4& rhs){
	mat4 m;
	m[0]  = lhs[0]  + rhs[0];  m[1]  = lhs[1]  + rhs[1];  
	m[2]  = lhs[2]  + rhs[2];  m[3]  = lhs[3]  + rhs[3];
	m[4]  = lhs[4]  + rhs[4];  m[5]  = lhs[5]  + rhs[5];  
	m[6]  = lhs[6]  + rhs[6];  m[7]  = lhs[7]  + rhs[7];
	m[8]  = lhs[8]  + rhs[8];  m[9]  = lhs[9]  + rhs[9];  
	m[10] = lhs[10] + rhs[10]; m[11] = lhs[11] + rhs[11];
	m[12] = lhs[12] + rhs[12]; m[13] = lhs[13] + rhs[13]; 
	m[14] = lhs[14] + rhs[14]; m[15] = lhs[15] + rhs[15];
	return m;
}

mat4& mat4::operator+=(const mat4& rhs){
	data[0] += rhs[0]; data[1] += rhs[1]; data[2] += rhs[2]; data[3] += rhs[3];
	data[4] += rhs[4]; data[5] += rhs[5]; data[6] += rhs[6]; data[7] += rhs[7];
	data[8] += rhs[8]; data[9] += rhs[9]; data[10] += rhs[10]; data[11] += rhs[11];
	data[12] += rhs[12]; data[13] += rhs[13]; data[14] += rhs[14]; data[15] += rhs[15];
	return *this;
}

mat4 mat4::operator-(const mat4& lhs, const mat4& rhs){
	mat4 m;
	m[0]  = lhs[0]  - rhs[0];  m[1]  = lhs[1]  - rhs[1];  
	m[2]  = lhs[2]  - rhs[2];  m[3]  = lhs[3]  - rhs[3];
	m[4]  = lhs[4]  - rhs[4];  m[5]  = lhs[5]  - rhs[5];  
	m[6]  = lhs[6]  - rhs[6];  m[7]  = lhs[7]  - rhs[7];
	m[8]  = lhs[8]  - rhs[8];  m[9]  = lhs[9]  - rhs[9];  
	m[10] = lhs[10] - rhs[10]; m[11] = lhs[11] - rhs[11];
	m[12] = lhs[12] - rhs[12]; m[13] = lhs[13] - rhs[13]; 
	m[14] = lhs[14] - rhs[14]; m[15] = lhs[15] - rhs[15];
	return m;
}

mat4& mat4::operator-=(const mat4& rhs){
	data[0] -= rhs[0]; data[1] -= rhs[1]; data[2] -= rhs[2]; data[3] -= rhs[3];
	data[4] -= rhs[4]; data[5] -= rhs[5]; data[6] -= rhs[6]; data[7] -= rhs[7];
	data[8] -= rhs[8]; data[9] -= rhs[9]; data[10] -= rhs[10]; data[11] -= rhs[11];
	data[12] -= rhs[12]; data[13] -= rhs[13]; data[14] -= rhs[14]; data[15] -= rhs[15];
	return *this;
}

/*
0,4,8 ,12
1,5,9 ,13
2,6,10,14
3,7,11,15
*/

mat4 mat4::operator*(const mat4& lhs, const mat4& rhs){
	mat4 m;
	m[0] = lhs[0]  * rhs[0]  + lhs[4] * rhs[1]  + lhs[8]  * rhs[2]  + lhs[12] * rhs[3];
	m[1] = lhs[1]  * rhs[0]  + lhs[5] * rhs[1]  + lhs[9]  * rhs[2]  + lhs[13] * rhs[3];
	m[2] = lhs[2]  * rhs[0]  + lhs[6] * rhs[1]  + lhs[10] * rhs[2]  + lhs[14] * rhs[3];
	m[3] = lhs[3]  * rhs[0]  + lhs[7] * rhs[1]  + lhs[11] * rhs[2]  + lhs[15] * rhs[3];
	
	m[4] = lhs[0]  * rhs[4]  + lhs[4] * rhs[5]  + lhs[8]  * rhs[6]  + lhs[12] * rhs[7];
	m[5] = lhs[1]  * rhs[4]  + lhs[5] * rhs[5]  + lhs[9]  * rhs[6]  + lhs[13] * rhs[7];
	m[6] = lhs[2]  * rhs[4]  + lhs[6] * rhs[5]  + lhs[10] * rhs[6]  + lhs[14] * rhs[7];
	m[7] = lhs[3]  * rhs[4]  + lhs[7] * rhs[5]  + lhs[11] * rhs[6]  + lhs[15] * rhs[7];
	
	m[8]  = lhs[0] * rhs[8]  + lhs[4] * rhs[9]  + lhs[8]  * rhs[10] + lhs[12] * rhs[11];
	m[9]  = lhs[1] * rhs[8]  + lhs[5] * rhs[9]  + lhs[9]  * rhs[10] + lhs[13] * rhs[11];
	m[10] = lhs[2] * rhs[8]  + lhs[6] * rhs[9]  + lhs[10] * rhs[10] + lhs[14] * rhs[11];
	m[11] = lhs[3] * rhs[8]  + lhs[7] * rhs[9]  + lhs[11] * rhs[10] + lhs[15] * rhs[11];
	
	m[12] = lhs[0] * rhs[12] + lhs[4] * rhs[13] + lhs[8]  * rhs[14] + lhs[12] * rhs[15];
	m[13] = lhs[1] * rhs[12] + lhs[5] * rhs[13] + lhs[9]  * rhs[14] + lhs[13] * rhs[15];
	m[14] = lhs[2] * rhs[12] + lhs[6] * rhs[13] + lhs[10] * rhs[14] + lhs[14] * rhs[15];
	m[15] = lhs[3] * rhs[12] + lhs[7] * rhs[13] + lhs[11] * rhs[14] + lhs[15] * rhs[15];
	return m;
}

mat4 mat4::operator+(const mat4& mat, const float s){
	mat4 m;
	m[0]  = lhs[0]  + s; m[1]  = lhs[1]  + s;  
	m[2]  = lhs[2]  + s; m[3]  = lhs[3]  + s;
	m[4]  = lhs[4]  + s; m[5]  = lhs[5]  + s;  
	m[6]  = lhs[6]  + s; m[7]  = lhs[7]  + s;
	m[8]  = lhs[8]  + s; m[9]  = lhs[9]  + s;  
	m[10] = lhs[10] + s; m[11] = lhs[11] + s;
	m[12] = lhs[12] + s; m[13] = lhs[13] + s; 
	m[14] = lhs[14] + s; m[15] = lhs[15] + s;
	return m;
}

mat4& mat4::operator+=(const float s){
	data[0] += s; data[1] += s; data[2] += s; data[3] += s;
	data[4] += s; data[5] += s; data[6] += s; data[7] += s;
	data[8] += s; data[9] += s; data[10] += s; data[11] += s;
	data[12] += s; data[13] += s; data[14] += s; data[15] += s;
	return *this;
}

mat4 mat4::operator+(const float s, const mat4& mat){
	mat4 m;
	m[0]  = s  + lhs[0]; m[1]  = s  + lhs[1];  
	m[2]  = s  + lhs[2]; m[3]  = s  + lhs[3];
	m[4]  = s  + lhs[4]; m[5]  = s  + lhs[5];  
	m[6]  = s  + lhs[6]; m[7]  = s  + lhs[7];
	m[8]  = s  + lhs[8]; m[9]  = s  + lhs[9];  
	m[10] = s + lhs[10]; m[11] = s + lhs[11];
	m[12] = s + lhs[12]; m[13] = s + lhs[13]; 
	m[14] = s + lhs[14]; m[15] = s + lhs[15];
	return m;	
}

mat4 mat4::operator-(const mat4& mat, const float s){
	mat4 m;
	m[0]  = lhs[0]  - s; m[1]  = lhs[1]  - s;  
	m[2]  = lhs[2]  - s; m[3]  = lhs[3]  - s;
	m[4]  = lhs[4]  - s; m[5]  = lhs[5]  - s;  
	m[6]  = lhs[6]  - s; m[7]  = lhs[7]  - s;
	m[8]  = lhs[8]  - s; m[9]  = lhs[9]  - s;  
	m[10] = lhs[10] - s; m[11] = lhs[11] - s;
	m[12] = lhs[12] - s; m[13] = lhs[13] - s; 
	m[14] = lhs[14] - s; m[15] = lhs[15] - s;
	return m;	
}

mat4& mat4::operator-=(const float s){
	data[0]  -= s; data[1]  -= s; data[2]  -= s; data[3]  -= s;
	data[4]  -= s; data[5]  -= s; data[6]  -= s; data[7]  -= s;
	data[8]  -= s; data[9]  -= s; data[10] -= s; data[11] -= s;
	data[12] -= s; data[13] -= s; data[14] -= s; data[15] -= s;
	return *this;
}

mat4 mat4::operator-(const float s, const mat4& mat){
	mat4 m;
	m[0]  = s  - lhs[0]; m[1]  = s  - lhs[1];  
	m[2]  = s  - lhs[2]; m[3]  = s  - lhs[3];
	m[4]  = s  - lhs[4]; m[5]  = s  - lhs[5];  
	m[6]  = s  - lhs[6]; m[7]  = s  - lhs[7];
	m[8]  = s  - lhs[8]; m[9]  = s  - lhs[9];  
	m[10] = s - lhs[10]; m[11] = s - lhs[11];
	m[12] = s - lhs[12]; m[13] = s - lhs[13]; 
	m[14] = s - lhs[14]; m[15] = s - lhs[15];
	return m;	
}

mat4 mat4::operator*(const mat4& mat, const float s){
	mat4 m;
	m[0]  = lhs[0]  * s; m[1]  = lhs[1]  * s;  
	m[2]  = lhs[2]  * s; m[3]  = lhs[3]  * s;
	m[4]  = lhs[4]  * s; m[5]  = lhs[5]  * s;  
	m[6]  = lhs[6]  * s; m[7]  = lhs[7]  * s;
	m[8]  = lhs[8]  * s; m[9]  = lhs[9]  * s;  
	m[10] = lhs[10] * s; m[11] = lhs[11] * s;
	m[12] = lhs[12] * s; m[13] = lhs[13] * s; 
	m[14] = lhs[14] * s; m[15] = lhs[15] * s;
	return m;	
}

mat4& mat4::operator*=(const float s){
	data[0] *= s; data[1] *= s; data[2] *= s; data[3] *= s;
	data[4] *= s; data[5] *= s; data[6] *= s; data[7] *= s;
	data[8] *= s; data[9] *= s; data[10] *= s; data[11] *= s;
	data[12] *= s; data[13] *= s; data[14] *= s; data[15] *= s;
	return *this;
}

mat4 mat4::operator*(const float s, const mat4& mat){
	mat4 m;
	m[0]  = s  * lhs[0]; m[1]  = s  * lhs[1];  
	m[2]  = s  * lhs[2]; m[3]  = s  * lhs[3];
	m[4]  = s  * lhs[4]; m[5]  = s  * lhs[5];  
	m[6]  = s  * lhs[6]; m[7]  = s  * lhs[7];
	m[8]  = s  * lhs[8]; m[9]  = s  * lhs[9];  
	m[10] = s * lhs[10]; m[11] = s * lhs[11];
	m[12] = s * lhs[12]; m[13] = s * lhs[13]; 
	m[14] = s * lhs[14]; m[15] = s * lhs[15];
	return m;	
}

mat4 mat4::operator/(const mat4& mat, const float s){
	mat4 m;
	m[0]  = lhs[0]  / s; m[1]  = lhs[1]  / s;  
	m[2]  = lhs[2]  / s; m[3]  = lhs[3]  / s;
	m[4]  = lhs[4]  / s; m[5]  = lhs[5]  / s;  
	m[6]  = lhs[6]  / s; m[7]  = lhs[7]  / s;
	m[8]  = lhs[8]  / s; m[9]  = lhs[9]  / s;  
	m[10] = lhs[10] / s; m[11] = lhs[11] / s;
	m[12] = lhs[12] / s; m[13] = lhs[13] / s; 
	m[14] = lhs[14] / s; m[15] = lhs[15] / s;
	return m;		
}

mat4& mat4::operator/=(const float s){
	data[0] /= s; data[1] /= s; data[2] /= s; data[3] /= s;
	data[4] /= s; data[5] /= s; data[6] /= s; data[7] /= s;
	data[8] /= s; data[9] /= s; data[10] /= s; data[11] /= s;
	data[12] /= s; data[13] /= s; data[14] /= s; data[15] /= s;
	return /this;
}

mat4 mat4::operator/(const float s, const mat4& mat){
	mat4 m;
	m[0]  = s  / lhs[0]; m[1]  = s  / lhs[1];  
	m[2]  = s  / lhs[2]; m[3]  = s  / lhs[3];
	m[4]  = s  / lhs[4]; m[5]  = s  / lhs[5];  
	m[6]  = s  / lhs[6]; m[7]  = s  / lhs[7];
	m[8]  = s  / lhs[8]; m[9]  = s  / lhs[9];  
	m[10] = s / lhs[10]; m[11] = s / lhs[11];
	m[12] = s / lhs[12]; m[13] = s / lhs[13]; 
	m[14] = s / lhs[14]; m[15] = s / lhs[15];
	return m;	
}

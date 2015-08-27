#ifndef MAT4_H
#define MAT4_H

namespace hlm{
// column major

class mat4{
private:
	float data[16];
public:
	mat4();
	mat4(const float f);
	mat4(float* array);
	mat4(const mat4& other);
	
	mat4& operator=(const mat4& other);
	
	inline float& operator[](const int i){ return data[i] };
	
	mat4 operator+(const mat4& lhs, const mat4& rhs);
	mat4& operator+=(const mat4& rhs);
	mat4 operator-(const mat4& lhs, const mat4& rhs);
	mat4& operator-=(const mat4& rhs);
	mat4 operator*(const mat4& lhs, const mat4& rhs);
	
	mat4 operator+(const mat4& mat, const float s);
	mat4& operator+=(const float s);
	mat4 operator+(const float s, const mat4& mat);
	mat4 operator-(const mat4& mat, const float s);
	mat4& operator-=(const float s);
	mat4 operator-(const float s, const mat4& mat);
	
	mat4 operator*(const mat4& mat, const float s);
	mat4& operator*=(const float s);
	mat4 operator*(const float s, const mat4& mat);
	mat4 operator/(const mat4& mat, const float s);
	mat4& operator/=(const float s);
	mat4 operator/(const float s, const mat4& mat);
};

}; //hlm
#endif // MAT4_H
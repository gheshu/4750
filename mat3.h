#ifndef MAT3_H
#define MAT3_H

namespace hlm{

class vec3;

class mat3{
public:
float data[9];
	mat3(float* array);
	mat3(vec3* a, vec3* b, vec3* c);
	mat3(const float s);
	mat3();
	~mat3(){};
	inline float& operator[](const int i){ return data[i]; };
	mat3& operator=(const mat3& other);
	mat3 operator+(const mat3& mat, const float s);
	mat3 operator+(const float s, const mat& mat);
	mat3 operator+(const mat3& lhs, const mat3& rhs);
	mat3 operator-(const mat3& lhs, const mat3& rhs);
	mat3 operator-(const mat3& mat, const float s);
	mat3 operator-(const float s, const mat3& mat);
	mat3 operator*(const float s, const mat3& mat);
	mat3 operator*(const mat3& mat, const float s);
	mat3 operator/(const float s, const float mat3& mat);
	mat3 operator/(const mat3& mat, const float s);
	
};

};

#endif //MAT3_H
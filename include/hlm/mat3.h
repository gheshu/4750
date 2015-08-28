#ifndef MAT3_H
#define MAT3_H

namespace hlm{
// column major

class mat4;

class mat3{
	float data[9];
public:
	mat3(float* array);
	mat3(const float s);
	mat3();
	mat3(mat4& m);
	
	inline float& operator[](const int i){ return data[i]; };
	
	mat3& operator=(const mat3& other);
	
	mat3 operator+(const mat3& mat, const float s);
	mat3& operator+=(const float s);
	mat3 operator+(const float s, const mat& mat);
	mat3& operator+=(const mat3& mat);
	mat3 operator+(const mat3& lhs, const mat3& rhs);
	mat3 operator*(const mat3& lhs, const mat3& rhs);
	
	mat3 operator-(const mat3& lhs, const mat3& rhs);
	mat3& operator-=(const mat3& mat);
	mat3 operator-(const mat3& mat, const float s);
	mat3& operator-=(const float s);
	mat3 operator-(const float s, const mat3& mat);
	
	mat3 operator*(const float s, const mat3& mat);
	mat3& operator*=(const float s);
	mat3 operator*(const mat3& mat, const float s);
	
	mat3 operator/(const float s, const float mat3& mat);
	mat3 operator/(const mat3& mat, const float s);
	mat3& operator/=(const float s);
	
};

};

/*
EXAMPLE OF HOW OPENGL ADDRESSES MATRIX MEMORY:
static void __gluMakeIdentityf(GLfloat m[16])
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}

SAME AS MAT4:
0, 4, 8,  12,
1, 5, 9,  13,
2, 6, 10, 14,
3, 7, 11, 15

MAT3:
0, 3, 6,
1, 4, 7,
2, 5, 8
*/

#endif //MAT3_H
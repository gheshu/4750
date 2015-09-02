#ifndef MAT4_H
#define MAT4_H

namespace hlm{
// column major

class mat4{
private:
	float data[4][4];
public:
	mat4();
	mat4(const float f);
	mat4(float* array);
	mat4(const mat4& other);
	
	mat4& operator=(const mat4& other);
	
	inline float& operator[][](const int r, const int c){ return data[r][c] };
	
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

#endif // MAT4_H
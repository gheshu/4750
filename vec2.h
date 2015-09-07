#ifndef VEC2_H
#define VEC2_H

namespace hlm{

class vec2{
public:
	float x, y;
	vec2() : x(0.0f), y(0.0f){};
	vec2(const float _x, const float _y) : x(_x), y(_y) {};
};	// vec2

};	// hlm

#endif
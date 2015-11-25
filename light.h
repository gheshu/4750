#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include <vector>
class GLSLProgram;

struct Light{
	hlm::vec3 position, color, falloff;
	Light(const hlm::vec3& pos = hlm::vec3(0.0f), 
		const hlm::vec3& col = hlm::vec3(1.0f), 
		const hlm::vec3& fall = hlm::vec3(0.01f, 0.01f, 1.0f))
		: position(pos), color(col), falloff(fall){};
};

typedef std::vector<Light> LightList;


#endif

#include "light.h"
#include "GLSLProgram.h"

void bindLights(LightList& lights, GLSLProgram& prog){
	prog.setUniform("numLights", std::min(10, lights.size()));
	for(unsigned j = 0; j < lights.size() && j < 10; j++){
		Light& l = lights[j];
		const std::string js = std::to_string(j);
		prog.setUniform(std::string("light[" + js + "].position"), l.position);
		prog.setUniform(std::string("light[" + js + "].color"), l.color);
		prog.setUniform(std::string("light[" + js + "].falloff"), l.falloff);
	}
}
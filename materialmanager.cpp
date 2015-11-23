#include "materialmanager.h"
#include "glsl_program.h"

void MaterialManager::bindMaterial(std::string& name, GLSLProgram& prog){
	auto i = materials[name];
	auto j = textures[i.diffuse];
	auto k = normals[i.normal];
	j.bind(0);
	prog.setUniformInt("diffuse_tex", 0);
	k.bind(1);
	prog.setUniformInt("normal_tex", 1);
	prog.setUniform("uv_scale", i.uv_scale);
	prog.setUniform("uv_offset", i.uv_offset);
	prog.setUniformFloat("spec_exp", i.spec_exp);
	prog.setUniformFloat("spec_str", i.spec_str);
}
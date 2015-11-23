#include "materialmanager.h"
#include "glsl_program.h"

void MaterialManager::bindMaterial(unsigned id, GLSLProgram& prog){
	auto i = materials.get(id);
	if(!i) return;
	auto j = images.get(i->d_id);
	if(!j) return;
	auto k = images.get(i->n_id);
	if(!k) return;
	j->bind(0);
	prog.setUniformInt("diffuse_tex", 0);
	k->bind(1);
	prog.setUniformInt("normal_tex", 1);
	prog.setUniform("uv_scale", i->uv_scale);
	prog.setUniform("uv_offset", i->uv_offset);
	prog.setUniformFloat("spec_exp", i->spec_exp);
	prog.setUniformFloat("spec_str", i->spec_str);
}
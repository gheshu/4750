#include "meshmanager.h"

#include "glsl_program.h"
#include "materialmanager.h"
#include "camera.h"
#include "hlm.h"

void MeshManager::drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights){
	prog.setUniform("eye", cam.getEye());
	bindLights(lights, prog);
	hlm::mat4 VP = cam.getVP();
	std::vector<Mesh*> mesh_list;
	meshes.getValues(mesh_list);
	for(Mesh* i : mesh_list){
		hlm::mat4& M = i->getTransform();
		hlm::mat4 MVP = VP * M;
		hlm::mat3 normMat = hlm::transpose(hlm::inverse(hlm::mat3(M)));
		mats.bindMaterial(i->getMaterial(), prog);
		prog.setUniform("MVP", MVP);
		prog.setUniform("model", M);
		prog.setUniform("normMat", normMat);
	}
}

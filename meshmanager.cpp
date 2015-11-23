#include "meshmanager.h"

#include "glsl_program.h"
#include "materialmanager.h"
#include "camera.h"
#include "light.h"
#include "hlm.h"

void MeshManager::drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights){
	prog.setUniform("eye", cam.getEye());
	bindLights(lights, prog);
	hlm::mat4 VP = cam.getVP();
	for(unsigned i = 0; i < meshes.size(); i++){
		hlm::mat4& M = (*this)[i]->getTransform();
		hlm::mat4 MVP = VP * M;
		hlm::mat3 normMat = hlm::transpose(hlm::inverse(hlm::mat3(M)));
		mats.bindMaterial((*this)[i]->getMaterial(), prog);
		prog.setUniform("MVP", MVP);
		prog.setUniform("model", M);
		prog.setUniform("normMat", normMat);
	}
}

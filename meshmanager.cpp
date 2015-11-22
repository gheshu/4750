#include "meshmanager.h"

#include "GLSLProgram.h"
#include "materialmanager.h"
#include "camera.h"
#include "light.h"
#include <vector>

void MeshManager::drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights){
	prog.setUniform("eye", cam.getEye());
	for(auto j : lights){
		prog.setUniform("light_position", j.position);
		prog.setUniform("light_color", j.color);
		prog.setUniform("light_falloff", j.falloff);
		for(auto i : meshes){
			hlm::mat4 MVP = cam.getVP() * i.getTransform();
			hlm::mat4 normMat = transpose(inverse(mat3(i.getTransform())));
			mats.bindMaterial(i.getMaterial());
			prog.setUniform("model", i.getTransform());
			prog.setUniform("MVP", MVP);
			prog.setUniform("normMat", normMat);
		}
	}

}
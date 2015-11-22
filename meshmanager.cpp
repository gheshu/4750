#include "meshmanager.h"

#include "GLSLProgram.h"
#include "materialmanager.h"
#include "camera.h"
#include "light.h"

void MeshManager::drawAll(GLSLProgram& prog, MaterialManager& mats, Camera& cam, LightList& lights){
	prog.setUniform("eye", cam.getEye());
	bindLights(lights):
	hlm::mat4 VP = cam.getVP();
	for(auto i : meshes){
		hlm::mat4 MVP = VP * i.getTransform();
		hlm::mat3 normMat = transpose(inverse(mat3(i.getTransform())));
		mats.bindMaterial(i.getMaterial());
		prog.setUniform("model", i.getTransform());
		prog.setUniform("MVP", MVP);
		prog.setUniform("normMat", normMat);
	}
}

/*

inside vert shader: 

out vec4 gl_Position;
out vec3 worldPos;
out vec2 uv;

uniform mat4 MVP;
uniform mat4 model;

inside frag shader:

in vec3 worldPos;
in vec4 gl_Position;
in vec2 uv;

out vec4 color;

uniform mat3 normMat;
#define MAX_LIGHTS 10
uniform int numLights;
uniform struct Light{
	vec3 position;
	vec3 color;
	vec3 falloff;
} lights[MAX_LIGHTS];
uniform vec3 eye;
uniform vec2 uv_scaling;
uniform vec2 uv_offset;

*/
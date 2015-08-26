#include "light.h"
#include "glm/gtc/matrix_transform.hpp"

void Light::init(LIGHTTYPE type, glm::vec3& _position){
	if (VP){
		return;
	}
	light_type = type;
	position = _position;
	color = glm::vec3(1.0f);
	attenuation = glm::vec3(1.0f);
	intensity = 1.0f;
	far_plane = 10.0f;
	if (light_type == DIRECTIONAL){
		VP = (glm::mat4*)malloc(sizeof(glm::mat4));
		*VP = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, far_plane) * glm::lookAt(position, glm::vec3(0.0f), glm::vec3(1.0f));
	}
	else if (light_type == POINT){
		VP = (glm::mat4*)malloc(sizeof(glm::mat4) * 6);
		setupCubemapView();
	}
}

void Light::setupCubemapView(){
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, far_plane);
	*(VP + 0) = shadowProj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
	*(VP + 1) = shadowProj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
	*(VP + 2) = shadowProj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	*(VP + 3) = shadowProj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
	*(VP + 4) = shadowProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
	*(VP + 5) = shadowProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));
}

void Light::destroy(){
	free(VP);
	VP = nullptr;
}

void Light::setPosition(glm::vec3& newPosition){
	position = newPosition;
	if (light_type == DIRECTIONAL){
		*VP = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f) * glm::lookAt(position, glm::vec3(0.0f), glm::vec3(1.0f));
	}
	else if (light_type == POINT){
		setupCubemapView();
	}
}
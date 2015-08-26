#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

enum LIGHTTYPE{
	POINT,
	SPOT,
	DIRECTIONAL
};

class Light{
	glm::vec3 position, color, attenuation;
	glm::mat4* VP = nullptr;
	float boundsRadius, intensity, far_plane;
	LIGHTTYPE light_type;
	void setupCubemapView();
public:
	void init(LIGHTTYPE type, glm::vec3& position);
	void destroy();
	void setColor(glm::vec3& newColor) { color = newColor; }
	void setPosition(glm::vec3& newPosition);
	void setAttenuation(glm::vec3& newAttenuation){ attenuation = newAttenuation; }
	void setIntensity(float newIntensity){ intensity = newIntensity; }
	void setFarPlane(float newFar){ far_plane = newFar; }
	glm::mat4* getVPMat(){ return VP; }
	glm::vec3* getPosition() { return &position; }
	glm::vec3* getColor(){ return &color; }
	glm::vec3* getAttenuation(){ return &attenuation; }
	float getBoundsRadius(){ return boundsRadius; }
	float getIntensity(){ return intensity; }
	float getFarPlane() { return far_plane; }
	const LIGHTTYPE getType() const { return light_type; }

	inline bool operator<(const Light& other) const {
		return light_type < other.getType();
	}
};

#endif

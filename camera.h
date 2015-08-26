#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera
{
private:
	glm::mat4 m_projMatrix, m_viewMatrix, m_VP;
	glm::vec3 m_position, m_forward, m_right, m_up;
	float m_fov, m_whratio, m_near, m_far, m_yaw, m_pitch;
public:
	Camera(){};
	~Camera(){};
	void init(float fov, float ratio, float near, float far, glm::vec3& position);
	void updateViewMatrix();
	void setFov(float fov);
	void setPosition(glm::vec3& position);
	void pollInput();
	void moveForward(float amt);
	void moveUp(float amt);
	void moveRight(float amt);
	void pitch(float amt);
	void yaw(float amt);
	float getFov();
	glm::mat4* getVPMat();
	glm::mat4* getProjMat();
	glm::mat4* getViewMat();
	glm::vec3* getPosition();
	glm::vec3* getForward();
	glm::vec3* getRight();
	glm::vec3* getUp();
	void printPosition();
};
#endif

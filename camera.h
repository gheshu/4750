#ifndef CAMERA_H
#define CAMERA_H

#include "hlm/hlm.h"

class Camera
{
private:
/*
	hlm::mat4 m_projMatrix, m_viewMatrix, m_VP;
	hlm::vec3 m_position, m_forward, m_right, m_up;
*/
	float m_fov, m_whratio, m_near, m_far, m_yaw, m_pitch;
public:
	Camera(){};
	~Camera(){};
/*
	void init(float fov, float ratio, float near, float far, hlm::vec3& position);
	void updateViewMatrix();
	void setFov(float fov);
	void setPosition(hlm::vec3& position);
	void pollInput();
	void moveForward(float amt);
	void moveUp(float amt);
	void moveRight(float amt);
	void pitch(float amt);
	void yaw(float amt);
	float getFov();
	hlm::mat4* getVPMat();
	hlm::mat4* getProjMat();
	hlm::mat4* getViewMat();
	hlm::vec3* getPosition();
	hlm::vec3* getForward();
	hlm::vec3* getRight();
	hlm::vec3* getUp();
	void printPosition();
*/
};
#endif

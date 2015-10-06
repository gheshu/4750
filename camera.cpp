#include "camera.h"
#include "math.h"
#include <algorithm>

void Camera::init(){ 
	m_pitch = 0.0f; m_yaw = 0.0f;
	eye = hlm::vec3(0.0f, 0.0f, 0.0f);
	view = hlm::lookAt(eye, hlm::vec3(0.0f, 0.0f, -1.0f), hlm::vec3(0.0f, 1.0f, 0.0f));
}
void Camera::pitch(const float _pitch){
	m_pitch = std::min(std::max(-89.0f, m_pitch + _pitch), 89.0f);
}
void Camera::yaw(const float _yaw){
	m_yaw += _yaw;
	if(m_yaw > 360.0f){
		m_yaw -= 360.0f;
	}
	else if(m_yaw < -360.0f){
		m_yaw += 360.0f;
	}
}
void Camera::moveForward(const float amt){
	eye += hlm::getForward(view) * amt;
}
void Camera::moveRight(const float amt){
	eye += hlm::getRight(view) * amt;
}
void Camera::moveUp(const float amt){
	eye += hlm::getUp(view) * amt;
}
void Camera::update(){
	hlm::vec3 forward;
	forward.x = cos(hlm::radians(m_yaw)) * cos(hlm::radians(m_pitch));
	forward.y = sin(hlm::radians(m_pitch));
	forward.z = sin(hlm::radians(m_yaw)) * cos(hlm::radians(m_pitch));
	view = hlm::lookAt(eye, eye + forward, hlm::vec3(0.0f, 1.0f, 0.0f));
}
#include "camera.h"
#include "math.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "stdio.h"

void Camera::init(float fov, float ratio, float near, float far, glm::vec3& position)
{
	m_fov = fov;
	m_whratio = ratio;
	m_near = near;
	m_far = far;
	m_position = position;
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_whratio, m_near, m_far);
	updateViewMatrix();
}

void Camera::setPosition(glm::vec3& position)
{
	m_position = position;
	
}

void Camera::moveForward(float amt)
{
	m_position += m_forward * amt;
}

void Camera::moveUp(float amt)
{
	m_position += m_up * amt;
}

void Camera::moveRight(float amt)
{
	m_position += m_right * amt;
}

void Camera::pitch(float amt)
{
	m_pitch += amt;
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	else if (m_pitch < -89.0f)
		m_pitch = -89.0f;
}

void Camera::yaw(float amt)
{
	m_yaw -= amt;
	if (m_yaw > 360.0f)
		m_yaw -= 360.0f;
	else if (m_yaw < -360.0f)
		m_yaw += 360.0f;
}

glm::mat4* Camera::getViewMat(){
	return &m_viewMatrix;
}

glm::mat4* Camera::getProjMat(){
	return &m_projMatrix;
}

glm::mat4* Camera::getVPMat(){
	return &m_VP;
}

glm::vec3* Camera::getForward(){
	return &m_forward;
}

glm::vec3* Camera::getRight(){
	return &m_right;
}

glm::vec3* Camera::getUp(){
	return &m_up;
}

void Camera::updateViewMatrix()
{
	m_forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward.y = sin(glm::radians(m_pitch));
	m_forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward = glm::normalize(m_forward);
	m_right = glm::normalize(glm::cross(m_forward, m_up));
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	m_VP = m_projMatrix * m_viewMatrix;
}

void Camera::printPosition(){
	printf("Camera Position: %f, %f, %f\n", m_position.x, m_position.y, m_position.z);
}

void Camera::setFov(float fov)
{
	m_fov = fov;
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_whratio, m_near, m_far);
}

float Camera::getFov()
{
	return m_fov;
}

glm::vec3* Camera::getPosition()
{
	return &m_position;
	
}

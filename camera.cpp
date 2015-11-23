#include "camera.h"
#include <cmath>
#include <algorithm>

void Camera::init(const hlm::vec3& _eye, const hlm::vec3& center, const hlm::vec3& up,
		float fov, double ratio, double near, double far){
	eye = _eye;
	view = hlm::lookAt(eye, center, up);
	proj = hlm::GLperspective(fov, ratio, near, far);
	forward = hlm::getForward(view);
}
void Camera::pitch(const float amt){
	forward += sin(hlm::radians(amt)) * hlm::getUp(view);
}
void Camera::yaw(const float amt){
	forward += sin(hlm::radians(amt)) * hlm::getRight(view);
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
	view = hlm::lookAt(eye, eye + forward, hlm::vec3(0.0f, 1.0f, 0.0f));
}

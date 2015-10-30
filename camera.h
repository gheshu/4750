#ifndef CAMERA_H
#define CAMERA_H

#include "hlm.h"

class Camera{
	hlm::mat4 view;
	hlm::vec3 eye;
	hlm::vec3 forward;
public:
	void init();
	void init(const hlm::vec3& eye, const hlm::vec3& center, const hlm::vec3& up);
	void pitch(const float _pitch);
	void yaw(const float _yaw);
	void moveForward(const float amt);
	void moveRight(const float amt);
	void moveUp(const float amt);
	void update();
	inline const hlm::mat4& getViewMatrix(){ return view; };
	inline const hlm::vec3& getEye(){ return eye; }
	inline const hlm::vec3& getForward() { return forward; }

};

#endif
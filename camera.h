#ifndef CAMERA_H
#define CAMERA_H

#include "hlm.h"

class Camera{
	hlm::mat4 view, proj;
	hlm::vec3 eye;
	hlm::vec3 forward;
public:
	void init();
	void init(const hlm::vec3& eye, const hlm::vec3& center, const hlm::vec3& up,
		float fov, double ratio, double near, double far);
	void pitch(const float _pitch);
	void yaw(const float _yaw);
	void moveForward(const float amt);
	void moveRight(const float amt);
	void moveUp(const float amt);
	void update();
	inline hlm::mat4& getViewMatrix(){ return view; };
	inline hlm::vec3& getEye(){ return eye; }
	inline hlm::vec3& getForward() { return forward; }
	inline hlm::mat4 getVP(){return proj * view;}

};

#endif
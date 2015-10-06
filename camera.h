#ifndef CAMERA_H
#define CAMERA_H

#include "hlm.h"

class Camera{
	hlm::mat4 view;
	hlm::vec3 eye;
	float m_pitch, m_yaw;
public:
	void init();
	void pitch(const float _pitch);
	void yaw(const float _yaw);
	void moveForward(const float amt);
	void moveRight(const float amt);
	void moveUp(const float amt);
	void update();
	inline const hlm::mat4& getView(){return view;};

};

#endif
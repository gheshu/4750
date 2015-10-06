#ifndef CAMERA_H
#define CAMERA_H

#include "hlm.h"
#include "math.h"
#include <algorithm>

class Camera{
	hlm::mat4 view;
	hlm::vec3 eye, forward;
	float m_pitch, m_yaw;
public:
	inline void init(){ 
		m_pitch = 0.0f; m_yaw = 0.0f;
		eye = hlm::vec3(0.0f, 0.0f, 0.0f);
		forward = hlm::vec3(0.0f, 0.0f, -1.0f);
		view = hlm::lookAt(eye, forward, hlm::vec3(0.0f, 1.0f, 0.0f));
	}
	inline void pitch(const float _pitch){
		m_pitch = std::min(std::max(-89.0f, m_pitch + _pitch), 89.0f);
	}
	inline void yaw(const float _yaw){
		m_yaw += _yaw;
		if(m_yaw > 360.0f){
			m_yaw -= 360.0f;
		}
		else if(m_yaw < -360.0f){
			m_yaw += 360.0f;
		}
	}
	inline void moveForward(const float amt){
		eye += forward * amt;
	}
	inline void moveRight(const float amt){
		eye += hlm::getRight(view) * amt;
	}
	inline void moveUp(const float amt){
		eye += hlm::getUp(view) * amt;
	}
	inline void update(){
		forward.x = cos(hlm::radians(m_yaw)) * cos(hlm::radians(m_pitch));
		forward.y = sin(hlm::radians(m_pitch));
		forward.z = sin(hlm::radians(m_yaw)) * cos(hlm::radians(m_pitch));
		view = hlm::lookAt(eye, eye + forward, hlm::vec3(0.0f, 1.0f, 0.0f));
		forward = hlm::getForward(view);
	}
	inline const hlm::mat4& getView(){return view;};

};

#endif
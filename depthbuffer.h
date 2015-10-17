#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

namespace hlm{
	class vec3;
};

class DepthBuffer{
	float* data = nullptr;
	unsigned width, height;
public:
	void init(const unsigned _width, const unsigned _height);
	void destroy();
	float get(const unsigned x, const unsigned y);
	bool top(const hlm::vec3& v);
	bool set(const unsigned x, const unsigned y, const float val);
	bool set(const hlm::vec3& v);
	void parSet(const hlm::vec3& v);
	void clear();
};

#endif
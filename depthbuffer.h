#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

namespace hlm{
	class vec3;
	class vec4;
};

class DepthBuffer{
	float* data = nullptr;
	unsigned width, height;
public:
	void init(const unsigned _width, const unsigned _height);
	void destroy();
	float get(const unsigned x, const unsigned y);
	bool top(const hlm::vec4& v);
	void set(const hlm::vec4& v);
	void clear();
};

#endif
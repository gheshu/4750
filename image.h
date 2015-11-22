#ifndef IMAGE_H
#define IMAGE_H

#include <string>

typedef unsigned char uint_8;
namespace hlm{
	class vec2;
	class vec3;
	class vec4;
};

struct Image{
	int width, height;
	unsigned gl_id = -1;
	uint_8* data = nullptr;
	Image(const std::string& filename);
	~Image();
	void bind(unsigned channel);
};

#endif
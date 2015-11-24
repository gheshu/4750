#ifndef IMAGE_H
#define IMAGE_H

#include <string>

typedef unsigned char uint_8;

struct Image{
	int width, height;
	unsigned gl_id;
	uint_8* data;
	Image(const std::string& filename);
	~Image();
	void bind(unsigned channel);
};

#endif
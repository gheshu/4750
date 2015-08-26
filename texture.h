#ifndef TEXTURE_H
#define TEXTURE_H

#include "myglheaders.h"
#include <string>

struct Image;

struct Texture{
	GLuint tex_id;
public:
	void init();
	void upload(Image* img);
	void uploadFromFile(const std::string& file);
	void bind(GLuint channel_);
	void destroy();
};

#endif
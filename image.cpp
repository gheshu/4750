#include "image.h"
#include <string>
#include <algorithm>
#include "hlm.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "myglheaders.h"

void Image::Image(const std::string& filename){
	data = stbi_load(filename.c_str(), &width, &height, nullptr, 3);
	if (!data){
		printf("image %s could not be loaded\n", filename.c_str());
		return;
	}
	glGenTextures(1, &gl_id);
	glBindTexture(GL_TEXTURE_2D, gl_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	MYGLERRORMACRO
}

void Image::~Image(){
	glDeleteTextures(1, &gl_id);
	stbi_image_free(data);
	data = nullptr;	
	MYGLERRORMACRO
}

void bind(unsigned channel){
	glActiveTexture(GL_TEXTURE0 + channel);
	glBindTexture(GL_TEXTURE_2D, gl_id);
}
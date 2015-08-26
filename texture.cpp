#include "texture.h"

#include "debugmacro.h"
#include <string>
#include "image.h"

void Texture::init(){
	glGenTextures(1, &tex_id);
}

void Texture::upload(Image* img){
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, img->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	MYGLERRORMACRO
}

void Texture::uploadFromFile(const std::string& file){
	Image img;
	img.load(file);
	Texture::upload(&img);
	img.unload();
}

void Texture::bind(GLuint channel){
	glActiveTexture(GL_TEXTURE0 + channel);
	glBindTexture(GL_TEXTURE_2D, tex_id);
}

void Texture::destroy(){
	glDeleteTextures(1, &tex_id);
	MYGLERRORMACRO
}
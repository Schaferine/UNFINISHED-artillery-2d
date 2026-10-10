#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"

class texture {
public:
	GLuint ID;
	GLenum type;
	texture(const char* image, GLenum type, GLenum slot, GLenum formate, GLenum pixelType);

	void texUnit(shader& shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void Delete();
};

#endif
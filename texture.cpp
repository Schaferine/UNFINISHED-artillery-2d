#include "texture.h"

texture::texture(const char* image, GLenum texType, GLenum slot, GLenum formate, GLenum pixelType) {
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(type, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, formate, widthImg, heightImg, 0, formate, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(type, 0);
}

void texture::texUnit(shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.activate();
	glUniform1i(texUni, unit);
}

void texture::bind() {
	glBindTexture(type, ID);
}

void texture::unbind() {
	glBindTexture(type, 0);
}

void texture::Delete() {
	glDeleteTextures(1, &ID);
}
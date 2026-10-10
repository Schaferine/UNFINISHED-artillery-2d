#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numCompo, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.bind();
	glVertexAttribPointer(layout, numCompo, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind() {
	glBindVertexArray(ID);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}
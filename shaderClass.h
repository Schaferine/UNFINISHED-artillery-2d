#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <string>

std::string get_file_contents(const char* filename);

class shader {
public:
	GLuint ID;
	shader(const char* vertexFile, const char* fragmentFile);
	void activate();
	void shaderDelete();
private:
	void errorCheck(unsigned int shader, const char* type);
};

#endif
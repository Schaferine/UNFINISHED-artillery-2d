#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"

struct windowThing {
	int windowHeight = 1000;
	int windowWidth = 1500;
	void setWindowVersion() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
};
int main() {
	glfwInit();
	windowThing window;
	window.setWindowVersion();
	GLFWwindow* windrow = glfwCreateWindow(window.windowWidth, window.windowHeight, "balls", nullptr, nullptr);

	if (windrow == nullptr) {
		std::cout << "window ded, no big souprice" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windrow);
	gladLoadGL();

	GLfloat vertices[] = {
		-0.4f, -0.4f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f, // upper right
		-0.7f, -0.4f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f, // upper left
		-0.7f, -0.7f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f, // lower left
		-0.4f, -0.7f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f	// lower right
	};

	GLuint indices[] = {
		0,1,2,
		2,3,0
	};
	
	glViewport(0, 0, window.windowWidth, window.windowHeight);

	shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	VAO1.unbind();
	EBO1.unbind();
	VBO1.unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	texture Arty("arty.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Arty.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(windrow)) {
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.activate();
		Arty.bind();
		glUniform1f(uniID, 0.5f);
		VAO1.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(windrow);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Arty.Delete();
	shaderProgram.shaderDelete();

	glfwDestroyWindow(windrow);
	glfwTerminate();

	return 0;
}
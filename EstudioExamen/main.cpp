#include "Dependencies\GLEW\glew.h"
#include "Dependencies\GLFW\glfw3.h"
#include "Dependencies\GLM\glm.hpp"
#include <iostream>
#include <time.h>
#include "ShaderLoader.h"
#include "GameModels.h"
#include "Dependencies\SOIL\SOIL2.h"

////////GLOBALS////////
GLuint WIDTH = 1280;
GLuint HEIGHT = 720;
const char* HEADER_INF = "PAT ENGINE V2";
GameModels* gameModels;
GLuint program;
GLFWwindow* window;
//////////////////////

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glfwSwapBuffers(window);
}



void Init() {

	//Security Check
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Inicializacion
	window = glfwCreateWindow(WIDTH, HEIGHT, HEADER_INF, NULL, NULL);

	if(!window){
		glfwSetErrorCallback(error_callback);
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); /*vsync*/
	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_RENDERER);
	printf("Renderer: %s\n", renderer);
	printf("Version: %s\n", version);

	if (glewIsSupported("GL_VERSION_4_5"))
	{
		std::cout << " OpenGL Version is 4.5\n ";
	}
	else
	{
		std::cout << "OpenGL 4.5 not supported\n ";
	}

	glEnable(GL_DEPTH_TEST);

	gameModels = new GameModels();
	gameModels->CreateTriangleModel("triangle1");

	glDepthFunc(GL_LESS);
	ShaderLoader shaderLoader;
	program = shaderLoader.createProgram("vertexShader.vert","fragmentshader.frag");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {
	Init();
	while (!glfwWindowShouldClose(window)) {
		RenderScene();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	delete gameModels;
	glDeleteProgram(program);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


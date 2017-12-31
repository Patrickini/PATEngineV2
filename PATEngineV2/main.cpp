#include "Dependencies\GLEW\glew.h"
#include "Dependencies\GLFW\glfw3.h"
#include "Dependencies\GLM\glm.hpp"
#include <iostream>
#include <time.h>
#include "ShaderLoader.h"
#include "GameModels.h"

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
/*
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main() {

	if (!glfwInit())
	{
		glfwSetErrorCallback(error_callback);
		glfwTerminate();
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		glfwSetErrorCallback(error_callback);
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);

	const GLubyte* version = glGetString(GL_RENDERER);

	printf("Renderer: %s\n", renderer);
	printf("Version: %s\n", version);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	const char* vertex_shader =
		"#version 410\n"
		"in vec3 vp;"
		"void main(){"
		"gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main (){"
		"frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

*/


#include "Dependencies\GLEW\glew.h"
#include "Dependencies\GLFW\glfw3.h"
#include "Dependencies\GLM\glm.hpp"
#include <iostream>
#include <time.h>
#include "ShaderLoader.h"
#include "GameModels.h"
#include "Dependencies\SOIL\SOIL2.h"

////////GLOBALS////////
GLuint WIDTH = 720;
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
	//glClearColor(1.0, 0.0, 0.0, 1.0);

	glBindVertexArray(gameModels->GetModel("quad1"));

	//LoadTx
	GLuint texture;
	int TxW, TxH;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image("T1.JPG", &TxW, &TxH,0, SOIL_LOAD_RGBA );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TxW, TxH, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	
	
	


	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "Tx0"),0);
	//Tri:
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//Quad:
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
	//glViewport
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	//gameModels->CreateTriangleModel("triangle1");
	gameModels->CreateSquareModel("quad1");

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


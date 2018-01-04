#pragma once
#include "Dependencies\GLEW\glew.h"
#include "Dependencies\GLFW\glfw3.h"
#include <iostream>
#include <fstream>
#include <vector>

class ShaderLoader
{
private:
	std::string readShader(char* fileName); //regresa el contenido de un archivo
	GLuint createShader(GLenum shaderType,
						std::string source,
						char* shaderName); //compila el shader
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint createProgram(char* VertexShaderFileName,
						 char* FragmentShaderFileName); //crea ambos shaders y los regresa para ser usados en el renderloop
};


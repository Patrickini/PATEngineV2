#include "ShaderLoader.h"




ShaderLoader::ShaderLoader(void)
{
}
//Leer Archivo y regresar un string
std::string ShaderLoader::readShader(char * fileName)
{
	std::string shaderContent;
	std::ifstream file(fileName, std::ios::in);

	if (!file.good())
	{
		std::cout << "[ERROR] No se puede leer: " << fileName << std::endl;
		std::terminate();
	}


	file.seekg(0, std::ios::end);
	shaderContent.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderContent[0], shaderContent.size());
	file.close();
	return shaderContent;
}

//Crear Shader
GLuint ShaderLoader::createShader(GLenum shaderType, std::string source, char * shaderName)
{
	int compileResult = 0;

	GLuint shader = glCreateShader(shaderType);
	const char* shaderContentPtr = source.c_str();
	const int shaderContentSize = source.size();

	glShaderSource(shader, 1, &shaderContentPtr, &shaderContentSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	
	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "[Error]: al compilar el shader " << shaderName << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
	
}

//Crear programa (programa = contenedor para cada shader)
GLuint ShaderLoader::createProgram(char * VertexShaderFileName, char * FragmentShaderFileName)
{
	
	std::string vertex_shader_code = readShader(VertexShaderFileName);
	std::string fragment_shader_code = readShader(FragmentShaderFileName);

	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertexShader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragmentShader");

	int link_result = 0;

	//Crear el programa y ligarlo al shader
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	//revisar errores
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	return program;
}

ShaderLoader::~ShaderLoader(void)
{
}

/*
/////////////NOTAS///////////
por cada shader{
	glCreateShader (tipo_de_shader) crea un objeto vacio Shader con el tipo de shader deseado
	glShaderSource (shader, numero de arrays de caracteres, string_codigo_Shader,tamañoString) carga el string del shader
	glCompileShader (shader) compila el shader
	glGetShaderiv (shader, GLenum, GLint) Revisa errores y los imprime en consola
}
glCreateProgram() crear programa
glAttatchShader() ligar shaders al programa
glLinkProgram() ligar el programa (crea un ejecutable que correra en el GPU)
glGetProgramiv() revisa errores y los imprime


*/


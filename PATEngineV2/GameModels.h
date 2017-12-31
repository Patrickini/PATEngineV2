#pragma once
#include "Dependencies\GLEW\glew.h"
#include "Dependencies\GLFW\glfw3.h"
#include "ShaderLoader.h"
#include "VertexFormatStruct.h"
#include <vector>
#include <map>

struct Model {
	unsigned int vao;
	std::vector<unsigned int> vbos;
	Model(){}
};

class GameModels
{
public:
	GameModels();
	~GameModels();
	void CreateTriangleModel(const std::string& gameModelName);
	void DeleteModel(const std::string& gameModelName);
	unsigned int GetModel(const std::string& gameModelName);
private:
	//Guardar nuestros modelos y los obtendremos por nombre
	std::map<std::string, Model> GameModelList;
};


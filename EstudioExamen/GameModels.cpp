#include "GameModels.h"



GameModels::GameModels()
{
}


GameModels::~GameModels()
{
	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it) {
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModels::CreateTriangleModel(const std::string &gameModelName)
{
	unsigned int vao, vbo; //Variables

	glGenVertexArrays(1, &vao);// crear buffer y regresar ID para la variable
	glBindVertexArray(vao); //Binding a opengl

	std::vector<VertexFormtat> vertices;
	vertices.push_back(VertexFormtat(glm::vec3(0.25, -0.25, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.25, 0.25, 0.0), glm::vec4(0, 0, 1, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormtat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)0); //en el array especificado arriba (0) mandar los vertices de 3 en 3 para position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)12);//lo mismo pero para color en el (1)

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void GameModels::CreateSquareModel(const std::string &gameModelName)
{
	unsigned int vao, vbo; //Variables

	glGenVertexArrays(1, &vao);// crear buffer y regresar ID para la variable
	glBindVertexArray(vao); //Binding a opengl

	std::vector<VertexFormtat> vertices;
	/*vertices.push_back(VertexFormtat(glm::vec3(-0.25, 0.5, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(-0.25, 0.75, 0.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.25, 0.5, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.25, 0.75, 0.0),glm::vec4(0, 0, 1, 1)));*/

	vertices.push_back(VertexFormtat(glm::vec3(-0.5, -0.5, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(-0.5, 0.5, 0.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.5, -0.5, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.5, 0.5, 0.0), glm::vec4(0, 0, 1, 1)));
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormtat) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)0); //en el array especificado arriba (0) mandar los vertices de 3 en 3 para position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)12);//lo mismo pero para color en el (1)
	

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void GameModels::CreateSquareTxtModel(const std::string &gameModelName)
{
	unsigned int vao, vbo, ebo; //Variables

	glGenVertexArrays(1, &vao);// crear buffer y regresar ID para la variable
	glBindVertexArray(vao); //Binding a opengl

	std::vector<VertexFormtat> vertices;
	/*vertices.push_back(VertexFormtat(glm::vec3(-0.25, 0.5, 0.0), glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(-0.25, 0.75, 0.0), glm::vec4(0, 0, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.25, 0.5, 0.0), glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormtat(glm::vec3(0.25, 0.75, 0.0),glm::vec4(0, 0, 1, 1)));*/

	vertices.push_back(VertexFormtat(glm::vec3(-0.5, -0.5, 0.0), glm::vec4(1, 0, 0, 1),glm::vec2(1.0,1.0)));
	vertices.push_back(VertexFormtat(glm::vec3(-0.5, 0.5, 0.0), glm::vec4(0, 0, 0, 1), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormtat(glm::vec3(0.5, -0.5, 0.0), glm::vec4(0, 1, 0, 1), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormtat(glm::vec3(0.5, 0.5, 0.0), glm::vec4(0, 0, 1, 1), glm::vec2(0.0, 1.0)));

	GLuint indices[] = {
		0,1,3,
		1,2,3
	};
	glGenBuffers(1, &vbo);
	//glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormtat) * 4, &vertices[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	//Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)0); //en el array especificado arriba (0) mandar los vertices de 3 en 3 para position
	//Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)12);//lo mismo pero para color en el (1)
	//Tx
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormtat), (void*)12);


	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void GameModels::DeleteModel(const std::string & gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int GameModels::GetModel(const std::string & gameModelName)
{
	return GameModelList[gameModelName].vao;
}

/*
////////NOTAS/////

	Mandar los vertices al GPU y despues en el renderloop mandarlos al VShader
	Hay que crear objetos antes de entrar al renderloop, de lo contrario sera costoso
	VBO (vertex buffer object)
		Contenedor con un ID que guarda un buffer con nuestros vertices y puede ser accesado en cualquier momento
		VIDA de un vbo: 
			1.-Creacion, 
			2.-Binding, 
			3.-Fill(alocar memoria),
			4.-Delete(cuando no se necesite mas).
			
*/
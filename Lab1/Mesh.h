#pragma once
#include <glm\glm.hpp>
#include <iostream>
#include <GL\glew.h>
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Component.h"
#include "obj_loader.h"


using namespace std;

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	ComponentType getType();
	void draw(Camera* camera);
	void init();
	void loadModel(IndexedModel* model);
	void loadShader(std::string fileName);
	void loadTexture(std::string fileName);
	void update(double deltaTime);

	Texture texture;
	Shader shader;
private:
	
	void initModel(const IndexedModel& model);

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};


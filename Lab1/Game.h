#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include <list>
#include <iterator>
#include "GameObject.h"
#include "Texture.h"
#include "transform.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init();
	void processInput();
	void update();
	void draw();

	Display _gameDisplay;

	Camera camera;

	GameObject* monkey;

	list<GameObject*> gameObjects;

	bool _running = false;

	float counter;


};


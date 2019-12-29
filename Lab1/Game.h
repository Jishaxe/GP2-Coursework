#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "MushroomController.h"
#include "Mesh.h"
#include <list>
#include <iterator>
#include "Resources.h"
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

	const string RESOURCES = "D:\\git\\GP2-Coursework\\res\\";

	Display _gameDisplay;

	Camera camera;
	Resources resources;

	list<GameObject*> gameObjects;

	bool _running = false;

	float counter;


};


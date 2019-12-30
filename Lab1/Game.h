#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Display.h" 
#include "Shader.h"
#include "MushroomController.h"
#include "Mesh.h"
#include <list>
#include <iterator>
#include "Resources.h"
#include "GameObject.h"
#include "Texture.h"
#include "HammerController.h"
#include "transform.h"
#include "BoxCollider.h"
#include "Skybox.h"

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
	void collisions();

	const string RESOURCES = "D:\\git\\GP2-Coursework\\res\\";

	Display _gameDisplay;

	Camera camera;
	Skybox skybox;
	Resources resources;
	InputData input;

	// list of top-level gameobjects (nested GOs are kept inside them)
	list<GameObject*> gameObjects;

	BoxCollider* hammerCollider;



	// list of colliders
	list<BoxCollider*> colliders;

	bool _running = false;

	float counter;
};


#include "Game.h"
#include "GameObject.h"
#include "Camera.h"
#include <iostream>
#include <string>

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Transform transform;

Game::Game()
{
	Display* _gameDisplay = new Display(); //new display
}

Game::~Game()
{
}

void Game::run()
{
	_running = true;
	init(); 
	update();
}

void Game::init()
{
	_gameDisplay.initDisplay(); 

	/*
	monkey = new GameObject();
	Mesh* monkeyMesh = new Mesh();
	monkeyMesh->loadShader("D:\\git\\GP2-Coursework\\res\\shader");
	monkeyMesh->loadModel("D:\\git\\GP2-Coursework\\res\\monkey3.obj");
	monkeyMesh->loadTexture("D:\\git\\GP2-Coursework\\res\\bricks.jpg");
	monkey->addComponent(monkeyMesh);
	*/

	GameObject* hammer = new GameObject();
	Mesh* hammerMesh = new Mesh();

	hammerMesh->loadShader(RESOURCES + "shader");
	hammerMesh->loadModel(resources.getModel("neuro_hammer_obj.obj"));
	hammerMesh->loadTexture(RESOURCES + "neuro_hammer_diffuse.jpg");
	hammer->addComponent(hammerMesh);
	hammer->transform.SetPos(glm::vec3(0, 1, 0));
	hammer->transform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	gameObjects.push_back(hammer);

	int i = 0;
	for (int x = -20; x < 20; x += 10) {
		for (int z = -20; z < 20; z += 10) {
			i++;
			GameObject* plantPot = new GameObject();
			Mesh* plantPotMesh = new Mesh();
			plantPotMesh->loadShader(RESOURCES + "shader");
			plantPotMesh->loadModel(resources.getModel("wall.obj"));
			plantPotMesh->loadTexture(RESOURCES + "plant_pot.jpg");
			plantPot->addComponent(plantPotMesh);

			plantPot->transform.SetPos(glm::vec3(x, 0, z));

			GameObject* mushroom = new GameObject();
			Mesh* mushroomMesh = new Mesh();
			mushroomMesh->loadShader(RESOURCES + "shader");
			mushroomMesh->loadModel(resources.getModel("mushroom.obj"));
			mushroomMesh->loadTexture(RESOURCES + "mushroom.jpg");
			mushroom->addComponent(mushroomMesh);
			mushroom->transform.SetPos(glm::vec3(0, -5, 3));

			plantPot->addChild(mushroom);

			MushroomController* mushroomController = new MushroomController();
			mushroom->addComponent(mushroomController);

			gameObjects.push_back(plantPot);
		}
	}



	camera.initCamera(glm::vec3(-5, 50, -25), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);
	camera.Pitch(70);
	counter = 0.0f;
}

void Game::update() 
{
	_running = true;

	uint32_t last_tick_time = 0;
	float deltaTime = 0;

	while (_running)
	{
		// calculate delta time in seconds
		uint32_t tick_time = SDL_GetTicks();
		deltaTime = (tick_time - last_tick_time) * 0.001;
		last_tick_time = tick_time;

		processInput();

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update(deltaTime);
		}

		draw();
	}
}

void Game::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_running = false;
				break;
		}
	}
	
}


void Game::draw()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->draw(&camera);
	}

	counter = counter + 0.01f;
				
	_gameDisplay.swapBuffer();
} 
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
    Mesh* mesh1();
	Mesh* mesh2();
	Texture* texture();
	Shader* shader();
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

	monkey = new GameObject();
	Mesh* monkeyMesh = new Mesh();
	monkeyMesh->loadShader("D:\\git\\GP2-Coursework\\res\\shader");
	monkeyMesh->loadModel("D:\\git\\GP2-Coursework\\res\\monkey3.obj");
	monkeyMesh->loadTexture("D:\\git\\GP2-Coursework\\res\\bricks.jpg");
	monkey->addComponent(monkeyMesh);

	gameObjects.push_back(monkey);

	camera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void Game::update()
{
	_running = true;

	while (_running)
	{
		processInput();

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update();
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
	
	monkey->transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	monkey->transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	monkey->transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->draw(&camera);
	}

	counter = counter + 0.01f;
				
	_gameDisplay.swapBuffer();
} 
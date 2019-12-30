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

	GameObject* hammer = new GameObject();
	hammer->name = "Hammer";
	Mesh* hammerMesh = new Mesh();

	hammerMesh->loadShader(RESOURCES + "shader");
	hammerMesh->loadModel(resources.getModel("neuro_hammer_obj.obj"));
	hammerMesh->loadTexture(RESOURCES + "neuro_hammer_diffuse.jpg");
	hammer->addComponent(hammerMesh);
	hammer->transform.SetPos(glm::vec3(0, 5, 0));

	HammerController* hammerController = new HammerController();
	hammer->addComponent(hammerController);

	hammerCollider = new BoxCollider(glm::vec3(-1,-1,-1), glm::vec3(1,1,3));
	hammer->addComponent(hammerCollider);

	vector<string> faces{
	RESOURCES + "skybox/right.jpg",
	RESOURCES + "skybox/left.jpg",
	RESOURCES + "skybox/top.jpg",
	RESOURCES + "skybox/bottom.jpg",
	RESOURCES + "skybox/front.jpg",
	RESOURCES + "skybox/back.jpg"
	};

	skybox.init(faces);

	//hammer->transform.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	gameObjects.push_back(hammer);

	int i = 0;
	for (int x = -20; x < 20; x += 10) {
		for (int z = -20; z < 20; z += 10) {
			i++;
			GameObject* plantPot = new GameObject();
			plantPot->name = "PlantPot";

			Mesh* plantPotMesh = new Mesh();
			plantPotMesh->loadShader(RESOURCES + "shader");
			plantPotMesh->loadModel(resources.getModel("wall.obj"));
			plantPotMesh->loadTexture(RESOURCES + "plant_pot.jpg");
			plantPot->addComponent(plantPotMesh);

			plantPot->transform.SetPos(glm::vec3(x, 0, z));

			GameObject* mushroom = new GameObject();
			mushroom->name = "Mushroom";
			Mesh* mushroomMesh = new Mesh();
			mushroomMesh->loadShader(RESOURCES + "shader");
			mushroomMesh->loadModel(resources.getModel("mushroom.obj"));
			mushroomMesh->loadTexture(RESOURCES + "mushroom.jpg");
			mushroom->addComponent(mushroomMesh);
			mushroom->transform.SetPos(glm::vec3(0, -5, 3));

			plantPot->addChild(mushroom);

			MushroomController* mushroomController = new MushroomController();
			mushroom->addComponent(mushroomController);


			BoxCollider* mushroomCollider = new BoxCollider(glm::vec3(-5, -5, -5), glm::vec3(5, 5, 5));
			mushroom->addComponent(mushroomCollider);

			// should probably use a factory to do this automatically
			colliders.push_back(mushroomCollider);

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

		// read SDL input events and adjust InputData 
		processInput();

		/*
		if (input.right) std::cout << "D" << std::endl;
		if (input.left) std::cout << "A" << std::endl;
		if (input.down) std::cout << "S" << std::endl;
		if (input.up) std::cout << "W" << std::endl;
		if (input.space) std::cout << "Space" << std::endl;
		*/

		// Update all the gameobjects
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update(deltaTime, input);
		}

		collisions();


		// Draw all the gameobjects
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
			case SDL_KEYDOWN: // process the wasd and space key up/down events and adjust the InputData accordingly
				switch (evnt.key.keysym.sym) {
				case SDLK_a: 
					input.left = true;
					break;
				case SDLK_d:
					input.right = true;
					break;
				case SDLK_s:
					input.down = true;
					break;
				case SDLK_w:
					input.up = true;
					break;
				case SDLK_SPACE:
					input.space = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (evnt.key.keysym.sym) {
				case SDLK_a:
					input.left = false;
					break;
				case SDLK_d:
					input.right = false;
					break;
				case SDLK_s:
					input.down = false;
					break;
				case SDLK_w:
					input.up = false;
					break;
				case SDLK_SPACE:
					input.space = false;
					break;
				}
				break;

		}
	}
	
}


void Game::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->draw(&camera);
	}

	skybox.draw(&camera);

	counter = counter + 0.01f;
				
	_gameDisplay.swapBuffer();
}

void Game::collisions()
{
	//for (auto a = colliders.begin(); a != colliders.end(); ++a) {
		for (auto b = colliders.begin(); b != colliders.end(); ++b) {
			
			if (hammerCollider->intersect((*b))) {
				hammerCollider->collisionThisFrame = (*b);
				(*b)->collisionThisFrame = hammerCollider;
				std::cout << hammerCollider->gameObject->name << " collided with " << (*b)->gameObject->name << std::endl;

				break;
			}
		}
	//}

}

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
	// set up the SDL display
	_gameDisplay.initDisplay(); 

	// set up the audio manager and load the 4 sounds
	audio.init();
	audio.loadSound(resources.RESOURCES + "sounds\\hammerhit.wav", "hammer hit");
	audio.loadSound(resources.RESOURCES + "sounds\\hammermiss.wav", "hammer miss");
	audio.loadSound(resources.RESOURCES + "sounds\\mushroomhit.wav", "mushroom hit");
	audio.loadSound(resources.RESOURCES + "sounds\\mushroomup.wav", "mushroom up");
	
	// player controls the hammer, load in the mesh and components
	GameObject* hammer = new GameObject();
	hammer->name = "Hammer";
	Mesh* hammerMesh = new Mesh();

	hammerMesh->loadShader(resources.RESOURCES + "shader");
	hammerMesh->loadModel(resources.getModel("neuro_hammer_obj.obj"));
	hammerMesh->loadTexture(resources.RESOURCES + "neuro_hammer_diffuse.jpg");
	hammer->addComponent(hammerMesh);

	// starting position
	hammer->transform.SetPos(glm::vec3(0, 5, 0));

	HammerController* hammerController = new HammerController();
	hammer->addComponent(hammerController);

	// for colliding with the mushrooms
	hammerCollider = new BoxCollider(glm::vec3(-1,-1,-1), glm::vec3(1,1,3));
	hammer->addComponent(hammerCollider);

	AudioSource* hammerAudio = new AudioSource();
	hammerAudio->setAudio(&audio);
	hammer->addComponent(hammerAudio);

	// load the skybox from the 6 cube faces
	vector<string> faces{
	resources.RESOURCES + "skybox/right.jpg",
	resources.RESOURCES + "skybox/left.jpg",
	resources.RESOURCES + "skybox/top.jpg",
	resources.RESOURCES + "skybox/bottom.jpg",
	resources.RESOURCES + "skybox/front.jpg",
	resources.RESOURCES + "skybox/back.jpg"
	};

	skybox.init(faces);

	gameObjects.push_back(hammer);
	
	// populate all the plantpots
	for (int x = -20; x < 20; x += 10) {
		for (int z = -20; z < 20; z += 10) {
			GameObject* plantPot = new GameObject();
			plantPot->name = "PlantPot";

			// plant pot mesh, doesn't do anything
			Mesh* plantPotMesh = new Mesh();
			plantPotMesh->loadShader(resources.RESOURCES + "shader");
			plantPotMesh->loadModel(resources.getModel("wall.obj"));
			plantPotMesh->loadTexture(resources.RESOURCES + "plant_pot.jpg");
			plantPot->addComponent(plantPotMesh);

			// position in a grid
			plantPot->transform.SetPos(glm::vec3(x, 0, z));

			// mushroom that pops out the plantpot
			GameObject* mushroom = new GameObject();
			mushroom->name = "Mushroom";
			Mesh* mushroomMesh = new Mesh();
			mushroomMesh->loadShader(resources.RESOURCES + "shader");
			mushroomMesh->loadModel(resources.getModel("mushroom.obj"));
			mushroomMesh->loadTexture(resources.RESOURCES + "mushroom.jpg");
			mushroom->addComponent(mushroomMesh);
			mushroom->transform.SetPos(glm::vec3(0, -5, 3));

			// Add the mushroom as a child of the plantpot so its position is attached to it
			plantPot->addChild(mushroom);

			MushroomController* mushroomController = new MushroomController();
			mushroom->addComponent(mushroomController);

			AudioSource* mushroomAudio = new AudioSource();
			mushroomAudio->setAudio(&audio);
			mushroom->addComponent(mushroomAudio);

			BoxCollider* mushroomCollider = new BoxCollider(glm::vec3(-5, -5, -5), glm::vec3(5, 5, 5));
			mushroom->addComponent(mushroomCollider);

			// should probably use a factory to do this automatically
			colliders.push_back(mushroomCollider);

			gameObjects.push_back(plantPot);
		}
	}


	// set up camera
	camera.initCamera(glm::vec3(-5, 50, -25), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);
	camera.Pitch(70);

	// initialize all gameobjects and components
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->init();
	}

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

		// Update all the gameobjects
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update(deltaTime, input);
		}

		// checks collisions between every collider in the game
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
	for (auto b = colliders.begin(); b != colliders.end(); ++b) {
			
		if (hammerCollider->intersect((*b))) {
			hammerCollider->collisionThisFrame = (*b);
			(*b)->collisionThisFrame = hammerCollider;
			std::cout << hammerCollider->gameObject->name << " collided with " << (*b)->gameObject->name << std::endl;

			break;
		}
	}
}

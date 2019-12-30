#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "MushroomController.h"

class HammerController :
	public Component
{
private:
	// How much to move the hammer by in a tick by the user (multiplied by dt)
	const float MOVEMENT_PER_TICK = 30;
	const float UP_POSITION = 5;
	const float DOWN_POSITION = 0;
public:
	ComponentType getType();
	void init();
	void update(double deltaTime, InputData input);
	void draw(Camera* camera);
};


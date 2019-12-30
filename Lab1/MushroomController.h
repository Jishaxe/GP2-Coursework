#pragma once
#include "Component.h"

enum MushroomState {
	MOVING_UP, MOVING_DOWN, HOLDING_UP, HOLDING_DOWN
};

class MushroomController :
	public Component
{
private:
	// How much to move the mushroom by in a tick (multiplied by dt)
	const float MOVEMENT_PER_TICK = 10;

	// relative y position when "up"
	const float UP_POSITION = 1; 

	// relative y position when "down"
	const float DOWN_POSITION = -5;

	// how long to stay up for
	const float STAY_UP_FOR = 3;

	// chance per tick of popping up
	const double CHANCE_OF_POPPING_UP = 0.001;
public:
	MushroomState mushroomState = HOLDING_DOWN;
	ComponentType getType();
	void hit(); 
	void init();
	void update(double deltaTime, InputData input);
	void draw(Camera* camera);

private:
	float _timeUpFor = 0; // counter for how long the mushroom has been up for
};


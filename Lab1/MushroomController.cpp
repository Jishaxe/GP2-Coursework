#include "MushroomController.h"
#include <iostream>

ComponentType MushroomController::getType()
{
	return ComponentType::MUSHROOM_CONTROLLER;
}

void MushroomController::init() {

}


void MushroomController::update(double deltaTime) {
	// get current mushroom position
	glm::vec3 *pos = this->gameObject->transform.GetPos();

	// generate a random num between 0 and 1
	float r = ((double)rand() / (RAND_MAX));

	switch (mushroomState) {
		// if the mushroom is in down position..
	case HOLDING_DOWN:
		// if our random chance succeeds, start moving up
		if (CHANCE_OF_POPPING_UP >= r) mushroomState = MOVING_UP; // start moving up if the chance is high enough
		break;
		// if the mushroom is moving up
	case MOVING_UP:
		// if we've hit the up position, start holding up 
		if (pos->y >= UP_POSITION) {
			pos->y = UP_POSITION;
			mushroomState = HOLDING_UP;
		}
		else {
			// otherwise move up
			pos->y += MOVEMENT_PER_TICK * deltaTime;
		}
		break;
	case HOLDING_UP:
		// hold up for a certain amount of time, then start moving down
		_timeUpFor += deltaTime;
		if (_timeUpFor >= STAY_UP_FOR) {
			mushroomState = MOVING_DOWN;
			_timeUpFor = 0;
		}
		break;
	case MOVING_DOWN:
		// opposite of moving up
		if (pos->y <= DOWN_POSITION) {
			pos->y = DOWN_POSITION;
			mushroomState = HOLDING_DOWN;
		}
		else {
			pos->y -= MOVEMENT_PER_TICK * deltaTime;
		}
		break;
	}
}

void MushroomController::draw(Camera* camera) {

}
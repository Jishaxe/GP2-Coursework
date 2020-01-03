#include "HammerController.h"

ComponentType HammerController::getType()
{
	return HAMMER_CONTROLLER;
}

void HammerController::init()
{
	audioSource = (AudioSource*)(gameObject->getComponent(AUDIO_SOURCE));
}

void HammerController::update(double deltaTime, InputData input)
{
	glm::vec3* position = gameObject->transform.GetPos();
	float movement = MOVEMENT_PER_TICK * deltaTime;

	// if we aint holding space, move about according to WASD
	if (!input.space) {
		if (input.right) position->x -= movement;
		if (input.left) position->x += movement;
		if (input.up) position->z += movement;
		if (input.down) position->z -= movement;
		position->y = UP_POSITION;
		isDown = false;
	}
	else {
		// otherwise hold down position
		position->y = DOWN_POSITION;

		bool shouldPlaySound = false;
		if (!isDown) shouldPlaySound = true;
		isDown = true;

		bool collided = false;
		// check to see if the hammer collided with anything this frame
		BoxCollider* collider = (BoxCollider*)(gameObject->getComponent(BOX_COLLIDER));
		if (collider->collisionThisFrame != nullptr) {
			GameObject* collidedGO = collider->collisionThisFrame->gameObject;
			MushroomController* mushroom = (MushroomController*)(collidedGO->getComponent(MUSHROOM_CONTROLLER));

			// if the mushroom that was collided with is in HOLDING_UP state, hit it down
			if (mushroom->mushroomState == HOLDING_UP) {
				if (shouldPlaySound) audioSource->play("hammer hit");
				mushroom->hit();
				collided = true;
			}
		}

		if (!collided && shouldPlaySound) audioSource->play("hammer miss");
	}
}

void HammerController::draw(Camera * camera)
{
}

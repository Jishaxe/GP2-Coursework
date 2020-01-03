#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "InputData.h"

class InputData;
class GameObject;

enum ComponentType {
	MESH, MUSHROOM_CONTROLLER, HAMMER_CONTROLLER, BOX_COLLIDER, AUDIO_SOURCE
};

class Component
{
public:
	Component();
	~Component();

	GameObject* gameObject;
	virtual ComponentType getType() = 0;
	virtual void init() = 0;
	virtual void update(double deltaTime, InputData input) = 0;
	virtual void draw(Camera* camera) = 0;
};


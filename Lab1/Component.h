#pragma once

#include "GameObject.h"
#include "Camera.h"

class GameObject;

enum ComponentType {
	MESH, MUSHROOM_CONTROLLER
};

class Component
{
public:
	Component();
	~Component();

	GameObject* gameObject;
	virtual ComponentType getType() = 0;
	virtual void init() = 0;
	virtual void update(double deltaTime) = 0;
	virtual void draw(Camera* camera) = 0;
};


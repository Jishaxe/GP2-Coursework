#pragma once

#include "GameObject.h"
#include "Camera.h"

class GameObject;

enum ComponentType {
	MESH
};

class Component
{
public:
	Component();
	~Component();

	GameObject* gameObject;
	virtual ComponentType getType() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw(Camera* camera) = 0;
};


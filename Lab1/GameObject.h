#pragma once
#include "Component.h"
#include "transform.h"
#include <list> 
#include <iterator> 

using namespace std;
class Component;
class InputData;
enum ComponentType;

// Doesn't do anything by itself - simply contains a bag of components. init(), update() and draw() are called on all components.
class GameObject
{
public:
	GameObject();
	~GameObject();

	std::string name;

	// initialize all components
	void init();

	// update all components
	void update(double deltaTime, InputData input);

	// draw all components
	void draw(Camera* camera);

	// add a component to this gameobject
	void addComponent(Component* component);

	// add a child gameobject
	void addChild(GameObject* child);

	// gets the model matrix of this gameobject, recursively multiplying by parent transform if needed
	glm::mat4 getModelMatrix();

	// transform of gameobject
	Transform transform;

	// get a component by ComponentType (better to store a reference though)
	Component* getComponent(ComponentType type);

	GameObject* parent = nullptr; // parent gameobject, if it has one
private:
	// list of components
	list <Component*> _components;
	list <GameObject*> _children; // children gameobjects
};


#pragma once
#include "Component.h"
#include "transform.h"
#include <list> 
#include <iterator> 

using namespace std;
class Component;
enum ComponentType;

// Doesn't do anything by itself - simply contains a bag of components. init(), update() and draw() are called on all components.
class GameObject
{
public:
	GameObject();
	~GameObject();

	// initialize all components
	void init();

	// update all components
	void update();

	// draw all components
	void draw(Camera* camera);

	// add a component to this gameobject
	void addComponent(Component* component);

	// transform of gameobject
	Transform transform;

	// get a component by ComponentType (better to store a reference though)
	Component* getComponent(ComponentType type);

private:
	// list of components
	list <Component*> _components;
};


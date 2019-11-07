#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::init()
{

}

void GameObject::update()
{
	// iterates through all the components and calls update()
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		(*it)->update();
	}
}

void GameObject::draw(Camera* camera)
{
	// iterates through all the components and calls draw()
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		(*it)->draw(camera);
	}
}

void GameObject::addComponent(Component * component)
{
	component->gameObject = this;
	_components.push_back(component);
}


Component * GameObject::getComponent(ComponentType type)
{
	// just returns the first component that matches the given ComponentType
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		if ((*it)->getType() == type) return *it;
	}

	return nullptr;
}

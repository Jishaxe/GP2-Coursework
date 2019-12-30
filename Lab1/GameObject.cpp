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

glm::mat4 GameObject::getModelMatrix() {
	glm::mat4 matrix = transform.GetModel();

	// if this gameobject has a parent, recursively multiply the matrix of each parent until the root (parent is nullptr)
	if (parent != nullptr) {
		matrix *= parent->getModelMatrix();
	}

	return matrix;
}

void GameObject::update(double deltaTime, InputData input)
{
	// iterates through all the components and calls update()
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		(*it)->update(deltaTime, input);
	}

	// iterates through all the child gameobjects and calls update()
	for (auto it = _children.begin(); it != _children.end(); ++it) {
		(*it)->update(deltaTime, input);
	}
}

void GameObject::draw(Camera* camera)
{
	// iterates through all the components and calls draw()
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		(*it)->draw(camera);
	}

	// iterates through all the child gameobjects and calls update()
	for (auto it = _children.begin(); it != _children.end(); ++it) {
		(*it)->draw(camera);
	}
}


void GameObject::addChild(GameObject* child) {
	_children.push_back(child);
	child->parent = this;
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

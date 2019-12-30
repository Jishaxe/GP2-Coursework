#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec3 minbounds, glm::vec3 maxbounds) {
	this->minbounds = minbounds;
	this->maxbounds = maxbounds;
}

bool BoxCollider::intersect(BoxCollider* other) {
	// Find out the bounds multiplied by the transform matrices

	glm::vec4 aMinBounds = this->gameObject->getModelMatrix() * glm::vec4(this->minbounds, 1);
	glm::vec4 aMaxBounds = this->gameObject->getModelMatrix() * glm::vec4(this->maxbounds, 1);

	glm::vec4 bMinBounds = other->gameObject->getModelMatrix() * glm::vec4(other->minbounds, 1);
	glm::vec4 bMaxBounds = other->gameObject->getModelMatrix() * glm::vec4(other->maxbounds, 1);

	return (aMinBounds.x <= bMaxBounds.x && aMaxBounds.x >= bMinBounds.x) &&
		(aMinBounds.y <= bMaxBounds.y && aMaxBounds.y >= bMinBounds.y) &&
		(aMinBounds.z <= bMaxBounds.z && aMaxBounds.z >= bMinBounds.z);
}

ComponentType BoxCollider::getType()
{
	return BOX_COLLIDER;
}

void BoxCollider::init()
{
}

void BoxCollider::update(double deltaTime, InputData input)
{
}

void BoxCollider::draw(Camera * camera)
{
}
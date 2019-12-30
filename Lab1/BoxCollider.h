#pragma once
#include "Component.h"
class BoxCollider : public Component
{
public: 
	BoxCollider(glm::vec3 minbounds, glm::vec3 maxbounds);

	// true if this intersects with the other boxcollider
	bool intersect(BoxCollider* b);

	// collision in this frame, nullptr if none
	BoxCollider* collisionThisFrame = nullptr;
	glm::vec3 minbounds;
	glm::vec3 maxbounds;

	ComponentType getType();
	void init();
	void update(double deltaTime, InputData input);
	void draw(Camera* camera);
};


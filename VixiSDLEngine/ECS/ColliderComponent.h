#pragma once
#include <string>
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

	}
	
	void Update() override
	{

		collider.x = transform->position.x;
		collider.y = transform->position.y;
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;

	}

};
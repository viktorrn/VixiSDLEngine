#pragma once
#include <string>
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tag)
	{
		this->tag = tag;
	}

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}
	
	void Update() override
	{
		collider.x = static_cast<int>(transform->position.x + 0.5f);
		collider.y = static_cast<int>(transform->position.y + 0.5f);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

};
#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;

	void Init()override 
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void Update() override
	{



	}
};

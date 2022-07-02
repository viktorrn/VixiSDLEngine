#pragma once
#include "Vector2D.h"
#include "Components.h"
#include "Game.h"

class CameraComponent : public Component
{
public:
	Entity* target;
	Vector2D position;
	Vector2D screenSize;
	Vector2D bounds;
	int scale = 1;


	CameraComponent() = default;

	void Init() override
	{
		screenSize.Zero();
		position.Zero();
	}

	void UpdateScreenSize(int screenWidth, int screenHeight) 
	{
		screenSize.x = screenWidth;
		screenSize.y = screenHeight;
		std::cout << "screen " << screenSize.x << " " << screenSize.y << std::endl;
	}

	void AdjustToMap(int mapWidth, int mapHeight) 
	{
		bounds.x = mapWidth - screenSize.x/Game::drawScale;
		bounds.y = mapHeight - screenSize.y/ Game::drawScale;
		std::cout << "bounds " << bounds.x << " " << bounds.y << std::endl;
	}

	void setTarget(Entity* target)
	{
		this->target = target;
	}

	void Update() override
	{
		position.x = (target->getComponent<TransformComponent>().position.x - screenSize.x/2) ;
		position.y = (target->getComponent<TransformComponent>().position.y - screenSize.y/2) ;

		if (position.x < 0)
			position.x = 0;
		if (position.y < 0)
			position.y = 0;
		if (position.x > bounds.x)
			position.x = bounds.x;
		if (position.y > bounds.y)
			position.y = bounds.y;

	}
};
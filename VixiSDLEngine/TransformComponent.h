#pragma once
#include "Components.h";
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = Game::tileSize;
	int width = Game::tileSize;
	int scale = 1;

	float speed = 256.0f;

	TransformComponent()
	{
		position.Zero();
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void Init() override
	{
		velocity.Zero();
	}

	void Update() override
	{
		position.x += velocity.x * speed * Game::delta * static_cast<float>(scale) * Game::drawScale;
		position.y += velocity.y * speed * Game::delta * static_cast<float>(scale) * Game::drawScale;
	}
};
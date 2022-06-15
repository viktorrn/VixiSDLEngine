#pragma once
#include "Components.h";
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = Game::tileSize;
	int width = Game::tileSize;
	int scale = 1;

	float speed = 32.0f;

	TransformComponent()
	{
		position.y = 0.0f;
		position.x = 0.0f;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(int w, int h)
	{
		position.y = 0.0f;
		position.x = 0.0f;
		this->height = w;
		this->width = h;
	}
	TransformComponent(float x, float y, int w, int h)
	{
		position.x = x;
		position.y = y;
		this->height = w;
		this->width = h;
	}

	void Init() override
	{
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	void Update() override
	{
		position += (velocity *= Vector2D(speed * Game::delta, speed * Game::delta) );
	}
};
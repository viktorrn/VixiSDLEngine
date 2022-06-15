#pragma once
#include "Components.h"
#include "../Game.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int width, height;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}
	
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void SetTexture(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width * transform->scale;
		srcRect.h = transform->height * transform->scale;
		
	}

	void Update() override
	{
		destRect.x = (int)(floor(transform->position.x+0.5));
		destRect.y = (int)(floor(transform->position.y+0.5));
		destRect.w = transform->width * transform->scale;
		destRect.h = Game::tileSize * 2;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
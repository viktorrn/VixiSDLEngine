#pragma once
#include "Components.h"
#include "../Game.h"
#include "../Managers/TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	int width, height;

	bool animated = false;
	int frames = 0;
	int speed = 60;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}

	SpriteComponent(const char* path, int nFrames, int nSpeed)
	{
		animated = true;
		frames = nFrames-1;
		speed = nSpeed;
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
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			
		}

		destRect.x = static_cast<int>(transform->position.x+0.5f) * Game::drawScale;
		destRect.y = static_cast<int>(transform->position.y+0.5f) * Game::drawScale;
		destRect.w = transform->width * transform->scale * Game::drawScale;
		destRect.h = transform->height * transform->scale * Game::drawScale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

};
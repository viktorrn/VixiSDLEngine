#pragma once
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	CameraComponent* camera;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D positon;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path, int scale)
	{
		texture = TextureManager::LoadTexture(path);

		positon.x = xpos;
		positon.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = Game::tileSize;

		destRect.x = xpos * Game::drawScale;
		destRect.y = ypos * Game::drawScale;
		destRect.w = destRect.h = Game::tileSize * Game::drawScale * scale;
	}

	void AddCamera(CameraComponent* cam)
	{
		camera = cam;
	}

	void Update() override
	{
		int cx, cy;
		cx = cy = 0;

		if (camera != nullptr)
		{
			cx = camera->position.x;
			cy = camera->position.y;
		}

		destRect.x = (positon.x - cx) * Game::drawScale;
		destRect.y = (positon.y - cy) * Game::drawScale;
	}

	void Draw() override
	{
		if (camera != nullptr)
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};

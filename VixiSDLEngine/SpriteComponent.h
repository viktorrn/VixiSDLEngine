#pragma once
#include "Components.h"
#include "Game.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Animation.h"
#include <map>
#include <string>

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	CameraComponent* camera;
	std::string textureID;
	SDL_Rect srcRect, destRect;

	int width, height;

	bool animated = false;
	const char* currentAnimation;
	int tick = 0;
	int frames = 0;
	int speed = 60;

public:

	int animationIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTexture(path);
	}

	SpriteComponent(std::string ID, bool isAnimated)
	{
		animated = isAnimated;

		Animation still(0, 1, 1000);
		Animation idle(1, 4, 250);
		Animation walk(2, 4, 250);

		animations.emplace("Still",still);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		
		SetTexture(ID);
	}
	
	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture);
	}

	void SetTexture(const std::string ID )
	{
		textureID = ID;
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width * transform->scale;
		srcRect.h = transform->height * transform->scale;
	}

	void AddCamera(CameraComponent* cam) 
	{
		camera = cam;
	}

	void Update() override
	{
		tick += static_cast<int>(Game::delta * 1000.0f);

		if (animated)
		{

			srcRect.x = srcRect.w * static_cast<int>((tick / speed) % frames);
			
		}
		
		srcRect.y = animationIndex*srcRect.h;

		int cx, cy; 
		cx = cy= 0;

		if (camera != nullptr)
		{
			cx = camera->position.x;
			cy = camera->position.y;
		}

		destRect.x = (static_cast<int>(transform->position.x + 0.5f) - cx);
		destRect.y = (static_cast<int>(transform->position.y+0.5f) - cy);
		destRect.w = transform->width * transform->scale * Game::drawScale;
		destRect.h = transform->height * transform->scale * Game::drawScale;
	}

	void Draw() override
	{
		if(camera!= nullptr)
		TextureManager::Draw(Game::assets->GetTexture(textureID), srcRect, destRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		currentAnimation = animName;
		
		frames = animations[animName].frames;
		animationIndex = animations[animName].index;
		speed = animations[animName].speed;

		if(currentAnimation != animName)
			tick = 0;

	}

};
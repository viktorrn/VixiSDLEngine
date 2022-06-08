#pragma once
#include "libDependecies.h"
class GameObject
{

public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int w, int h, int scale);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;
	int scale = 2;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;


};


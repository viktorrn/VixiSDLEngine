#pragma once
#include "libDependecies.h"
class GameObject
{

public:
	GameObject(const char* texturesheet, int x, int y, int w, int h);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;


};


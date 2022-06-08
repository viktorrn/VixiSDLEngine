#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int w, int h, int scale)
{
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texturesheet, ren);
	ypos = y;
	xpos = x;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.h = h;
	srcRect.w = w;

	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

GameObject::~GameObject()
{

}

void GameObject::Update() 
{
	//xpos++;
	//ypos++;
	
}

void GameObject::Render()
{

	destRect.x = xpos;
	destRect.y = ypos;

	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

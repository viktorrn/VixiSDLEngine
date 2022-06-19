#include "GameObject.h"
#include "Managers/TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h)
{
	objTexture = TextureManager::LoadTexture(texturesheet);
	ypos = y;
	xpos = x;

	srcRect.x = 0;
	srcRect.y = 0;

	srcRect.h = h;
	srcRect.w = w;

	destRect.w = srcRect.w * Game::drawScale;
	destRect.h = srcRect.h * Game::drawScale;
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

	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

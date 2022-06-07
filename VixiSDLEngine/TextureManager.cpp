#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    SDL_Surface* tmp = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    return tex;
}

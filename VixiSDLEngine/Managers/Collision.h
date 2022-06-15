#pragma once
#include "SDL.h"

class Collisons
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recb);
};
#pragma once
#include "SDL.h"


class ColliderComponent;

class Collisons
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
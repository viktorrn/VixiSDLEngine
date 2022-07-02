#include "Collision.h"
#include "ColliderComponent.h"

bool Collisons::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
        )
    {
        return true;
    }
    return false;
}

bool Collisons::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        return true;
    }
    return false;
}

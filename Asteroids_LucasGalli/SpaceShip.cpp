#include "SpaceShip.h"

void playerMovement(Vector2& pos, float& radius, float& playerAngle, float& acceleration)
{

    Vector2 direction;
    Vector2 dirNormalizado = { 0,0 };

    float speed = 100.0f;

    direction = Vector2Subtract(GetMousePosition(), pos);

    if (direction.x > 0)
    {
        playerAngle = atan(direction.y / direction.x) * 60;
    }
    else
    {
        playerAngle = (atan(direction.y / direction.x) * 60) + 180;
    }

    if (acceleration > 0.0f && !IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        acceleration -= 0.05f;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (pos.x < GetMouseX() - radius or pos.x > GetMouseX() + radius or pos.y < GetMouseY() - radius or pos.y > GetMouseY() + radius)
        {
            dirNormalizado = Vector2Normalize(direction);
            acceleration += 0.2f;
        }
    }
    if (acceleration > 5)
    {
        acceleration = 5;
    }

    pos.x += dirNormalizado.x * GetFrameTime() * speed * acceleration;
    pos.y += dirNormalizado.y * GetFrameTime() * speed * acceleration;
}
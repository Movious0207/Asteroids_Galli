#include "SpaceShip.h"

void playerMovement(Vector2& pos, float& radius, float& playerAngle, float& accelerationX, float& accelerationY,Vector2& direction,Vector2& normalDir, float speed)
{

    direction = Vector2Subtract(GetMousePosition(), pos);

    if (!IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        if (direction.x > 0)
        {
            playerAngle = atan(direction.y / direction.x) * 60;
        }
        else
        {
            playerAngle = (atan(direction.y / direction.x) * 60) + 180;
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        if (pos.x < GetMouseX() - radius || pos.x > GetMouseX() + radius || pos.y < GetMouseY() - radius || pos.y > GetMouseY() + radius)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                normalDir = Vector2Normalize(direction);
            }
            if (normalDir.x < 0)
            {
                accelerationX -= 0.2f;
            }
            if (normalDir.x > 0)
            {
                accelerationX += 0.2f;
            }
            if (normalDir.y < 0)
            {
                accelerationY -= 0.2f;
            }
            if (normalDir.y > 0)
            {
                accelerationY += 0.2f;
            }
        }
    }
    if (accelerationX > 5)
    {
        accelerationX = 5;
    }
    if (accelerationX < -5)
    {
        accelerationX = -5;
    }
    if (accelerationY > 5)
    {
        accelerationY = 5;
    }
    if (accelerationY < -5)
    {
        accelerationY = -5;
    }

    if (accelerationX > 0.0f && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        accelerationX -= 0.05f;
    }
    if (accelerationX < 0.0f && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        accelerationX += 0.05f;
    }
    if (accelerationY > 0.0f && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        accelerationY -= 0.05f;
    }
    if (accelerationY < 0.0f && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        accelerationY += 0.05f;
    }

    pos.x += abs(normalDir.x) * GetFrameTime() * speed * accelerationX;
    pos.y += abs(normalDir.y) * GetFrameTime() * speed * accelerationY;

    if (pos.x < 0)
    {
        pos.x = screenWidth;
    }
    if (pos.x > screenWidth)
    {
        pos.x = 0;
    }
    if (pos.y < 0)
    {
        pos.y = screenHeight;
    }
    if (pos.y > screenHeight)
    {
        pos.y = 0;
    }
}

void bulletLogic(Bullet bullet[], float& accelerationX, float& accelerationY, Vector2& direction, float speed, Vector2 playerPos)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (!bullet[i].active)
            {
                bullet[i].active = true;
                bullet[i].velocity = Vector2Normalize(direction);
                bullet[i].position.x = playerPos.x;
                bullet[i].position.y = playerPos.y;
                break;
            }
        }
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullet[i].active)
        {
            bullet[i].position.x += bullet[i].velocity.x * GetFrameTime() * speed * 5;
            bullet[i].position.y += bullet[i].velocity.y * GetFrameTime() * speed * 5;

            if (bullet[i].position.x > 1024 || bullet[i].position.x < 0)
            {
                bullet[i].active = false;
            }
            if (bullet[i].position.y > 768 || bullet[i].position.y < 0)
            {
                bullet[i].active = false;
            }
        }
    }
}

void bulletDraw(Bullet bullets[])
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            continue;
        }
        DrawCircleLines((int)bullets[i].position.x, (int)bullets[i].position.y, 20, RAYWHITE);
    }
}
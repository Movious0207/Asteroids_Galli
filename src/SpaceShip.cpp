#include "SpaceShip.h"

void player::Movement(Vector2& pos, float& radius, float& playerAngle, float acceleration,Vector2& direction,Vector2& normalDir, Vector2& velocity)
{
    direction = Vector2Subtract(GetMousePosition(), pos);
    normalDir = Vector2Normalize(direction);

    if (direction.x > 0)
    {
        playerAngle = atan(direction.y / direction.x) * 60;
    }
    else
    {
        playerAngle = (atan(direction.y / direction.x) * 60) + 180;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        if (pos.x < GetMouseX() - radius || pos.x > GetMouseX() + radius || pos.y < GetMouseY() - radius || pos.y > GetMouseY() + radius)
        {

            velocity.x += normalDir.x * acceleration * GetFrameTime();
            velocity.y += normalDir.y * acceleration * GetFrameTime();


        }
    }


    pos.x += GetFrameTime() * velocity.x;
    pos.y += GetFrameTime() * velocity.y;

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

void bullet::Logic(Bullet bullet[], Vector2& direction, float bulletSpeed, Vector2 playerPos, Sound shoot)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (!bullet[i].active)
            {
                PlaySound(shoot);
                if (direction.x < 0)
                {
                    bullet[i].angle = atan(direction.y / direction.x) * 60;
                }
                else
                {
                    bullet[i].angle = (atan(direction.y / direction.x) * 60) + 180;
                }
                bullet[i].active = true;
                bullet[i].velocity = Vector2Normalize(direction);
                bullet[i].position.x = playerPos.x - wizardRec.width / 2;
                bullet[i].position.y = playerPos.y - wizardRec.height / 2;
                break;
            }
        }
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullet[i].active)
        {
            bullet[i].position.x += bullet[i].velocity.x * GetFrameTime() * bulletSpeed * 5;
            bullet[i].position.y += bullet[i].velocity.y * GetFrameTime() * bulletSpeed * 5;

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

void bullet::Draw(Bullet bullets[], Texture fireball)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            continue;
        }
        DrawTexturePro(fireball, { 0,0,1287,954 }, { bullets[i].position.x + bullets[i].size.x/2 ,  bullets[i].position.y + bullets[i].size.y / 2 , bullets[i].size.x, bullets[i].size.y }, { bullets[i].size.x / 2 , bullets[i].size.y / 2 }, bullets[i].angle, RAYWHITE);
    }
}
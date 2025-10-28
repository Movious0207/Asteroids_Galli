#include "Asteroid.h"

void AsteroidSpawner(Asteroid asteroids[], int amount, float& spawnTime)
{
    spawnTime += GetFrameTime();
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < MAX_ASTEROIDS; j++)
        {
            if (!asteroids[j].active)
            {
                asteroids[j].active = true;
                asteroids[j].size = AsteroidSize::LARGE;
                asteroids[j].position = { (float)(rand() % 1024), 0 };

                float angle = (float)(rand() % 360);
                asteroids[j].velocity = { cosf(angle) * 100, sinf(angle) * 100 };
                break;
            }
        }
    }
}

float GetAsteroidRadius(AsteroidSize size) 
{
    switch (size) 
    {
    case AsteroidSize::LARGE: 
        return 60;
    case AsteroidSize::MEDIUM:
        return 35;
    case AsteroidSize::SMALL:
        return 20;
    default: return 0;
    }
}

void SplitAsteroid(Asteroid* asteroids, int index)
{
    Asteroid& a = asteroids[index];

    if (!a.active)
    {
        return;
    }

    AsteroidSize newSize = AsteroidSize::NONE;
    float newSpeed = 0;

    if (a.size == AsteroidSize::LARGE)
    {
        newSize = AsteroidSize::MEDIUM;
        newSpeed = 150;
    }
    else if (a.size == AsteroidSize::MEDIUM)
    {
        newSize = AsteroidSize::SMALL;
        newSpeed = 200;
    }
    else
    {
        a.active = false;
        return;
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].active) 
        {
            asteroids[i].active = true;
            asteroids[i].size = newSize;
            asteroids[i].position = a.position;

            float angle = (float)(rand() % 360);
            asteroids[i].velocity = { cosf(angle) * newSpeed, sinf(angle) * newSpeed };

            for (int j = i + 1; j < MAX_ASTEROIDS; j++) {
                if (!asteroids[j].active) {
                    asteroids[j].active = true;
                    asteroids[j].size = newSize;
                    asteroids[j].position = a.position;

                    float angle2 = (float)(rand() % 360);;
                    asteroids[j].velocity = { cosf(angle2) * newSpeed, sinf(angle2) * newSpeed };
                    break;
                }
            }
            break;
        }
    }

    a.active = false;
}

void AsteroidLogic(Asteroid asteroids[], Bullet bullet[])
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].active)
        {
            continue;
        }
        asteroids[i].position.x += asteroids[i].velocity.x * GetFrameTime();
        asteroids[i].position.y += asteroids[i].velocity.y * GetFrameTime();

        if (asteroids[i].position.x < 0)
        {
            asteroids[i].position.x = screenWidth;
        }
        if (asteroids[i].position.x > screenWidth)
        {
            asteroids[i].position.x = 0;
        }
        if (asteroids[i].position.y < 0)
        {
            asteroids[i].position.y = screenHeight;
        }
        if (asteroids[i].position.y > screenHeight)
        {
            asteroids[i].position.y = 0;
        }
        if (asteroids[i].active)
        {
            for (int j = 0; j < MAX_BULLETS; j++)
            {
                if (bullet[j].active)
                {
                    float distX = bullet[j].position.x - asteroids[i].position.x;
                    float distY = bullet[j].position.y - asteroids[i].position.y;
                    float distance_sq = (distX * distX) + (distY * distY);

                    bool colliding = distance_sq <= (10.0f + GetAsteroidRadius(asteroids[i].size)) * (10.0f + GetAsteroidRadius(asteroids[i].size));
                    if (colliding)
                    {
                        SplitAsteroid(asteroids, i);
                        bullet[j].active = false;
                    }
                }
            }
        }
    }
}

void AsteroidDraw(Asteroid asteroids[])
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].active)
        {
            continue;
        }
        DrawCircleLines((int)asteroids[i].position.x, (int)asteroids[i].position.y, GetAsteroidRadius(asteroids[i].size), RAYWHITE);
    }
}
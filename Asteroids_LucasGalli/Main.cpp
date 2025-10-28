#include <iostream>
#include "Asteroid.h"

int main()
{
    srand(time(nullptr));

    Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

    Bullet bullets[MAX_BULLETS] = { 0 };

    Vector2 pos = { 400, 225 };

    Vector2 direction;
    Vector2 normalDir = { 0,0 };

    float playerAngle = 0.0f;
    float radius = 30.0f;
    float accelerationX = 0.0f;
    float accelerationY = 0.0f;
    float speed = 100.0f;
    int amount = 10;
    float spawnTime = 0;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);      

    AsteroidSpawner(asteroids, amount, spawnTime);

    while (!WindowShouldClose())  
    {

        AsteroidLogic(asteroids, bullets);

        playerMovement(pos, radius, playerAngle, accelerationX,accelerationY,direction,normalDir, speed);

        bulletLogic(bullets, accelerationX, accelerationY,direction,speed, pos);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawCircleLines((int)pos.x,(int)pos.y,radius,RAYWHITE);

        AsteroidDraw(asteroids);

        bulletDraw(bullets);

        EndDrawing();
    }

    CloseWindow();     

    return 0;   
   
}
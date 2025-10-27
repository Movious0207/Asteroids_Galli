#include <iostream>
#include "Asteroid.h"

int main()
{

    Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

    asteroids[0].active = true;
    asteroids[0].size = AsteroidSize::LARGE;
    asteroids[0].position = { 400, 300 };
    asteroids[0].velocity = { 100, 100 };

    Bullet bullets[MAX_BULLETS] = { 0 };

    const int screenWidth = 1024;
    const int screenHeight = 768;

    Vector2 pos = { 400, 225 };

    Vector2 direction;
    Vector2 normalDir = { 0,0 };

    float playerAngle = 0.0f;
    float radius = 50.0f;
    float accelerationX = 0.0f;
    float accelerationY = 0.0f;
    float speed = 100.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);      

    while (!WindowShouldClose())  
    {

        AsteroidLogic(asteroids, screenWidth, screenHeight, bullets);

        playerMovement(pos, radius, playerAngle, accelerationX,accelerationY,direction,normalDir, speed);

        bulletLogic(bullets, accelerationX, accelerationY,direction,speed, pos);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawPolyLines(pos,3,radius,playerAngle,RAYWHITE);

        AsteroidDraw(asteroids);

        bulletDraw(bullets);

        EndDrawing();
    }

    CloseWindow();     

    return 0;   
   
}
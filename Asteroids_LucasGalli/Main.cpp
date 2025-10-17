#include <iostream>
#include "SpaceShip.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vector2 pos = { 400, 225 };

    float playerAngle = 0.0f;
    float radius = 50.0f;
    float acceleration = 0.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);      

    while (!WindowShouldClose())  
    {

        playerMovement(pos, radius, playerAngle, acceleration);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawPolyLines(pos,3,radius,playerAngle,RAYWHITE);

        EndDrawing();
    }

    CloseWindow();     

    return 0;   
   
}
#include <iostream>
#include <raylib.h>
#include <raymath.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vector2 pos = { 400, 225 };

    float playerAngle = 0.0f;

    Vector2 direction;

    float radius = 50.0f;
    float speed = 100.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);      

    while (!WindowShouldClose())  
    {
        direction = Vector2Subtract(GetMousePosition(), pos);

        direction.x = GetMouseX() - pos.x;
        direction.y = GetMouseY() - pos.y;

        Vector2 dirNormalizado = Vector2Normalize(direction);

        if (direction.x > 0)
        {
            playerAngle = atan(direction.y / direction.x) * 60;
        }
        else
        {
            playerAngle = (atan(direction.y / direction.x) * 60) + 180;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            pos.x += dirNormalizado.x * GetFrameTime() * speed;
            pos.y += dirNormalizado.y * GetFrameTime() * speed;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        DrawPolyLines(pos,3,50,playerAngle,RAYWHITE);

        EndDrawing();
    }

    CloseWindow();     

    return 0;   
   
}
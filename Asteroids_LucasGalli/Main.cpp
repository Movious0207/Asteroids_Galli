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
    Vector2 dirNormalizado = { 0,0 };

    float radius = 50.0f;
    float speed = 100.0f;
    float acceleration = 0.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);      

    while (!WindowShouldClose())  
    {
        direction = Vector2Subtract(GetMousePosition(), pos);

        direction.x = GetMouseX() - pos.x;
        direction.y = GetMouseY() - pos.y;

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
            dirNormalizado = Vector2Normalize(direction);
            acceleration += 0.2f;
        }
        if (acceleration > 5)
        {
            acceleration = 5;
        }

        pos.x += dirNormalizado.x * GetFrameTime() * speed * acceleration;
        pos.y += dirNormalizado.y * GetFrameTime() * speed * acceleration;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawPolyLines(pos,3,radius,playerAngle,RAYWHITE);

        EndDrawing();
    }

    CloseWindow();     

    return 0;   
   
}
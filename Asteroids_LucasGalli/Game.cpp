#include "Game.h"

void Game(GameState& screen, Vector2& mouse)
{

    Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

    Bullet bullets[MAX_BULLETS] = { 0 };

    Vector2 pos = { 400, 225 };

    Vector2 direction;
    Vector2 normalDir = { 0,0 };
    Vector2 velocity = { 0 };

    float bulletSpeed = 200;
    float playerAngle = 0.0f;
    float radius = 30.0f;
    float acceleration = 500;
    int asteroidAmount = 10;
    float spawnTime = 0;
    int lives = 5;
    bool isPaused = false;
    bool levelStart = true;
    bool isPlaying = true;
    int buttonWidth = screenWidth / 5;
    int buttonHeight = screenHeight / 12;

    while (screen == GameState::Game)
    {
        mouse = GetMousePosition();

        if (!isPaused)
        {
            if (levelStart)
            {
                AsteroidSpawner(asteroids, asteroidAmount, spawnTime);
                levelStart = false;
            }
            AsteroidLogic(asteroids, bullets);

            if (isPlaying)
            {
                Conditions(pos, radius, lives, asteroids, isPlaying);

                playerMovement(pos, radius, playerAngle, acceleration, direction, normalDir, velocity);

                bulletLogic(bullets, direction, bulletSpeed, pos);
            }
            else
            {
                if (lives <= 0)
                {
                    lives = 0;
                }
                if (IsKeyPressed(KEY_SPACE))
                {
                    screen = GameState::Menu;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                isPaused = true;
            }

            if (WindowShouldClose() && !isPaused)
            {
                screen = GameState::Quit;
            }

            BeginDrawing();

            ClearBackground(BLACK);
            if (isPlaying)
            {
                DrawPolyLines(pos, 3, radius, playerAngle, RAYWHITE);
            }
            else if (lives <= 0)
            {
                DrawText("YOU LOST!",screenWidth/2 - 200,screenHeight/2-20,70,RAYWHITE);
                DrawText("PRESS SPACE TO RETURN TO MENU", screenWidth / 2 - 300, screenHeight / 2 + 200, 30, RAYWHITE);
            }
            else
            {
                DrawText("YOU WON!", screenWidth / 2 - 200, screenHeight / 2 - 20, 70, RAYWHITE);
                DrawText("PRESS SPACE TO RETURN TO MENU", screenWidth / 2 - 300, screenHeight / 2 + 200, 30, RAYWHITE);
            }

            AsteroidDraw(asteroids);

            bulletDraw(bullets);

            EndDrawing();
        }
        else
        {
            if (mouse.x > buttonWidth * 2 && mouse.x < buttonWidth * 3 && mouse.y >buttonHeight * 7 && mouse.y < buttonHeight * 8)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    isPaused = false;
                }
            }
            if (mouse.x > buttonWidth * 2 && mouse.x < buttonWidth * 3 && mouse.y >buttonHeight * 8.5 && mouse.y < buttonHeight * 9.5)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = GameState::Menu;
                }
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                isPaused = false;
            }
            if (WindowShouldClose() && isPaused)
            {
                screen = GameState::Quit;
            }
            BeginDrawing();

            ClearBackground(BLACK);
            if (isPlaying)
            {
                DrawPolyLines(pos , 3, radius,playerAngle , RAYWHITE);
            }

            AsteroidDraw(asteroids);

            bulletDraw(bullets);

            DrawRectangle(buttonWidth * 2, buttonHeight * 7, buttonWidth, buttonHeight, GRAY);

            DrawRectangle(buttonWidth * 2, (int)(buttonHeight * 8.5), buttonWidth, buttonHeight, GRAY);

            EndDrawing();
        }
    }
}

void Conditions(Vector2& pos,float radius,int& lives, Asteroid asteroids[], bool& isPlaying)
{
    isPlaying = false;
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active)
        {
            isPlaying = true;

            float distX = asteroids[i].position.x - pos.x;
            float distY = asteroids[i].position.y - pos.y;
            float distance_sq = (distX * distX) + (distY * distY);

            bool colliding = distance_sq <= (radius + GetAsteroidRadius(asteroids[i].size)) * (radius + GetAsteroidRadius(asteroids[i].size));
            if (colliding)
            {
                lives--;
                pos.x = screenWidth / 2;
                pos.y = screenHeight / 2;
                asteroids[i].active = false;
            }
        }
    }
    if (lives <= 0)
    {
        isPlaying = false;
    }
}
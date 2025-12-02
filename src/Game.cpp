#include "Game.h"

void Game(GameState& screen, Vector2& mouse, Texture background)
{
    Sound smallHit = LoadSound("res/smallHit.wav");
    Sound mediumHit = LoadSound("res/mediumHit.wav");
    Sound bigHit = LoadSound("res/bigHit.wav");
    Sound shoot = LoadSound("res/shoot.wav");
    Sound takeDmg = LoadSound("res/takeDmg.wav");
    Texture fireball = LoadTexture("res/fireball.png");
    Texture wizard = LoadTexture("res/wizard.png");
    Texture smallSlime = LoadTexture("res/smallSlime.png");
    Texture mediumSlime = LoadTexture("res/MediumSlime.png");
    Texture bigSlime = LoadTexture("res/bigSlime.png");

    Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

    Bullet bullets[MAX_BULLETS] = { 0 };

    Vector2 pos = { 400, 225 };

    Vector2 direction;
    Vector2 normalDir = { 0,0 };
    Vector2 velocity = { 0 };

    Rectangle wizardRec = {0,0, 60,40};

    float bulletSpeed = 200;
    float playerAngle = 0.0f;
    float radius = 30.0f;
    float acceleration = 500;
    int asteroidAmount = 5;
    float spawnTime = 0;
    float respawnTimer = 0;
    bool isInvinsible = false;
    int lives = 5;
    int score = 0;
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
            wizardRec.x = pos.x;
            wizardRec.y = pos.y;

            AsteroidSpawner(asteroids, asteroidAmount, spawnTime);

            AsteroidLogic(asteroids, bullets, score, smallHit, mediumHit, bigHit);

            if (isPlaying)
            {
                if (respawnTimer<= 0)
                {
                    Conditions(pos, radius, lives, asteroids, isPlaying, asteroidAmount, respawnTimer, takeDmg);
                }
                else
                {
                    respawnTimer -= GetFrameTime();
                }

                playerMovement(pos, radius, playerAngle, acceleration, direction, normalDir, velocity);

                bulletLogic(bullets, direction, bulletSpeed, pos, shoot);
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

            DrawTextureEx(background, { 0, 0 }, 0, 0.9, WHITE);

            if (isPlaying)
            {
                DrawTexturePro(wizard, {0,0,50,40}, wizardRec, {40,10}, playerAngle - 5, WHITE);
                bulletDraw(bullets, fireball);
            }
            else
            {
                DrawText("YOU LOST!",screenWidth/2 - 200,screenHeight/2-20,70,RAYWHITE);
                DrawText("PRESS SPACE TO RETURN TO MENU", screenWidth / 2 - 300, screenHeight / 2 + 200, 30, RAYWHITE);
            }

            DrawText(TextFormat("Lives: %d", lives), 5, 5, 20, WHITE);
            DrawText(TextFormat("Score: %d", score), screenWidth-200, 5, 20, WHITE);
            if (respawnTimer > 0)
            {
                DrawText(TextFormat("Invisibility: %d", (int)respawnTimer), buttonWidth / 2, 5, 20, WHITE);
            }
            AsteroidDraw(asteroids, smallSlime, mediumSlime, bigSlime);

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

            DrawTextureEx(background, { 0, 0 }, 0, 0.9, WHITE);



            if (isPlaying)
            {
                DrawTexturePro(wizard, { 0,0,50,40 }, wizardRec, { 40,10 }, playerAngle - 5, WHITE);
            }

            AsteroidDraw(asteroids,smallSlime, mediumSlime, bigSlime);

            bulletDraw(bullets, fireball);

            DrawRectangle(buttonWidth * 2, buttonHeight * 7, buttonWidth, buttonHeight, GRAY);
            
            DrawText("Resume", (int)(buttonWidth * 2.3), (int)(buttonHeight * 7.3), 20, BLACK);

            DrawRectangle(buttonWidth * 2, (int)(buttonHeight * 8.5), buttonWidth, buttonHeight, GRAY);

            DrawText("Menu", (int)(buttonWidth * 2.3), (int)(buttonHeight * 8.8), 20, BLACK);
            EndDrawing();
        }
    }
}

void Conditions(Vector2& pos,float radius,int& lives, Asteroid asteroids[], bool& isPlaying, int& amount, float& invisibleTime, Sound takeDmg)
{
    int counter = 0;
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active)
        {
            counter++;
            float distX = asteroids[i].position.x - pos.x;
            float distY = asteroids[i].position.y - pos.y;
            float distance_sq = (distX * distX) + (distY * distY);

            bool colliding = distance_sq <= (radius + GetAsteroidRadius(asteroids[i].size)) * (radius + GetAsteroidRadius(asteroids[i].size));
            if (colliding)
            {
                lives--;
                PlaySound(takeDmg);
                pos.x = screenWidth / 2;
                pos.y = screenHeight / 2;
                asteroids[i].active = false;
                invisibleTime = 3;
            }
        }
    }
    if (counter <= 2)
    {
        isPlaying = true;
        amount += 5;
    }
    if (lives <= 0)
    {
        isPlaying = false;
    }
}
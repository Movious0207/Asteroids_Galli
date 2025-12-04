#include "Game.h"

static void Reset();
static void Conditions(Vector2& pos, float radius, Asteroid asteroids[], int& amount, float& invisibleTime, Sound takeDmg);

static bool isPaused = false;
static bool isGameStarted = false;
static bool isPlaying = true;

static int lives = 5;

void Game::GamePlay(GameState& screen, Vector2& mouse, Texture background)
{
    static Sound smallHit = LoadSound("res/smallHit.wav");
    static Sound mediumHit = LoadSound("res/mediumHit.wav");
    static Sound bigHit = LoadSound("res/bigHit.wav");
    static Sound shoot = LoadSound("res/shoot.wav");
    static Sound takeDmg = LoadSound("res/takeDmg.wav");
    static Texture fireball = LoadTexture("res/fireball.png");
    static Texture wizard = LoadTexture("res/wizard.png");
    static Texture smallSlime = LoadTexture("res/smallSlime.png");
    static Texture mediumSlime = LoadTexture("res/MediumSlime.png");
    static Texture bigSlime = LoadTexture("res/bigSlime.png");
    Asteroid asteroids[MAX_ASTEROIDS] = { 0 };

    Bullet bullets[MAX_BULLETS] = { 0 };

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].size = { 40,20 };
    }

    Vector2 pos = { screenWidth / 2, screenHeight / 2 };

    Vector2 direction;
    Vector2 normalDir = { 0,0 };
    Vector2 velocity = { 0 };

    float bulletSpeed = 200;
    float playerAngle = 0.0f;
    float radius = 30.0f;
    float acceleration = 500;
    float spawnTime = 0;
    float respawnTimer = 0;
    int asteroidAmount = 5;
    int score = 0;
    static int buttonWidth = screenWidth / 5;
    static int buttonHeight = screenHeight / 12;

    while (screen == GameState::Game)
    {
        mouse = GetMousePosition();

        if (WindowShouldClose())
        {
            screen = GameState::Quit;
        }


        if (isGameStarted)
        {
            if (!isPaused)
            {
                wizardRec.x = pos.x;
                wizardRec.y = pos.y;

                Asteroids::Spawner(asteroids, asteroidAmount, spawnTime);

                Asteroids::Logic(asteroids, bullets, score, smallHit, mediumHit, bigHit);

                if (isPlaying)
                {
                    if (respawnTimer <= 0)
                    {
                        Conditions(pos, radius, asteroids, asteroidAmount, respawnTimer,takeDmg);
                    }
                    else
                    {
                        respawnTimer -= GetFrameTime();
                    }

                    player::Movement(pos, radius, playerAngle, acceleration, direction, normalDir, velocity);

                    bullet::Logic(bullets, direction, bulletSpeed, pos, shoot);
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
                        Reset();
                    }
                }

                if (IsKeyPressed(KEY_ESCAPE))
                {
                    isPaused = true;
                }

                BeginDrawing();

                DrawTextureEx(background, { 0, 0 }, 0, 0.9f, WHITE);

                if (isPlaying)
                {
                    DrawTexturePro(wizard, { 0,0,50,40 }, wizardRec, { 25,20 }, playerAngle, WHITE);
                    bullet::Draw(bullets, fireball);
                }
                else
                {
                    DrawText("YOU LOST!", screenWidth / 2 - 200, screenHeight / 2 - 20, 70, RAYWHITE);
                    DrawText("PRESS SPACE TO RETURN TO MENU", screenWidth / 2 - 300, screenHeight / 2 + 200, 30, RAYWHITE);
                }

                DrawText(TextFormat("Lives: %d", lives), 5, 5, 20, WHITE);
                DrawText(TextFormat("Score: %d", score), screenWidth - 200, 5, 20, WHITE);
                if (respawnTimer > 0)
                {
                    DrawText(TextFormat("Invisibility: %d", (int)respawnTimer), buttonWidth / 2, 5, 20, WHITE);
                }
                Asteroids::Draw(asteroids, smallSlime, mediumSlime, bigSlime);

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
                        Reset();
                    }
                }

                if (IsKeyPressed(KEY_ESCAPE))
                {
                    isPaused = false;
                }

                BeginDrawing();

                DrawTextureEx(background, { 0, 0 }, 0, 0.9f, WHITE);

                if (isPlaying)
                {
                    DrawTexturePro(wizard, { 0,0,50,40 }, wizardRec, { wizardRec.width / 2, wizardRec.height / 2 }, playerAngle, WHITE);
                }

                Asteroids::Draw(asteroids, smallSlime, mediumSlime, bigSlime);

                bullet::Draw(bullets, fireball);

                DrawText("PAUSED", (int)(screenWidth / 2) - 100, (int)(screenHeight / 3), 50, WHITE);

                DrawRectangle(buttonWidth * 2, buttonHeight * 7, buttonWidth, buttonHeight, WHITE);

                DrawText("Resume", (int)(buttonWidth * 2.3), (int)(buttonHeight * 7.3), 20, BLACK);

                DrawRectangle(buttonWidth * 2, (int)(buttonHeight * 8.5), buttonWidth, buttonHeight, WHITE);

                DrawText("Menu", (int)(buttonWidth * 2.3), (int)(buttonHeight * 8.8), 20, BLACK);
                EndDrawing();
            }
        }
        else
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                screen = GameState::Menu;
            }

            BeginDrawing();

            DrawTextureEx(background, { 0, 0 }, 0, 0.9f, GRAY);

            DrawText("HOW TO PLAY", screenWidth / 2 - 160, screenHeight / 4, 50, WHITE);

            DrawText("RIGHT CLICK to move towards your mouse", screenWidth / 2 - 200, screenHeight / 2 - 100, 20, WHITE);
            DrawText("LEFT CLICK to shoot in the direction of your mouse", screenWidth / 2 - 250, screenHeight / 2, 20, WHITE);
            DrawText("DESTROY ASTEROIDS to gain POINTS", screenWidth / 2 - 170, screenHeight / 2 + 100, 20, WHITE);
            DrawText("LEFT CLICK to START", screenWidth / 2 - 220, screenHeight / 2 + 200, 40, WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isGameStarted = true;
            }

            EndDrawing();


        }
    }
}

static void Conditions(Vector2& pos, float radius, Asteroid asteroids[], int& amount, float& invisibleTime, Sound takeDmg)
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

            bool colliding = distance_sq <= (radius + Asteroids::GetRadius(asteroids[i].size)) * (radius + Asteroids::GetRadius(asteroids[i].size));
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

static void Reset()
{
    lives = 5;
    isPaused = false;
    isGameStarted = false;
    isPlaying = true;
}
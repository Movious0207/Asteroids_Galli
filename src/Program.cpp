#include "Program.h"

int program::Start()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    Vector2 mouse = GetMousePosition();

    GameState actualScreen = GameState::Menu;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    InitAudioDevice();

    SetMasterVolume(1.0f);

    Texture background = LoadTexture("res/background.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (actualScreen)
        {
        case GameState::Menu:
            SetExitKey(KEY_ESCAPE);
            Menu::Logic(actualScreen, mouse, background);
            break;
        case GameState::Game:
            SetExitKey(KEY_NULL);
            Game::GamePlay(actualScreen, mouse, background);
            break;
        case GameState::Credits:
            SetExitKey(KEY_ESCAPE);
            Credits::Logic(actualScreen, mouse, background);
            break;
        case GameState::Quit:
            CloseAudioDevice();
            CloseWindow();
            
            return 0;
            break;
        default:
            break;
        }
    }
    CloseAudioDevice();
    CloseWindow();
}
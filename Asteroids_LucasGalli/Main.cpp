#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Credits.h"

int main()
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
            MainMenu(actualScreen, mouse, background);
            break;
        case GameState::Game:
            Game(actualScreen, mouse, background);
            break;
        case GameState::Credits:
            Credits(actualScreen, mouse, background);
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

    return 0;
}
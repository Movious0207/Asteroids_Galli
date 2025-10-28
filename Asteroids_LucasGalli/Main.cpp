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

    SetTargetFPS(60);      


    while (!WindowShouldClose())  
    {
        switch (actualScreen)
        {
        case GameState::Menu:
            MainMenu(actualScreen, mouse);
            break;
        case GameState::Game:
            Game(actualScreen, mouse);
            break;
        case GameState::Credits:
            Credits(actualScreen, mouse);
            break;
        case GameState::Quit:

            CloseWindow();

            return 0;
            break;
        default:
            break;
        }
    }
    CloseWindow();

    return 0;
}
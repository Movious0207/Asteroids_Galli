#include "Menu.h"

void MainMenu(GameState& screen, Vector2& mouse)
{
	int buttonWidth = screenWidth/5;
	int buttonHeight = screenHeight/12;

	while (screen == GameState::Menu)
	{
		mouse = GetMousePosition();

		if (mouse.x > buttonWidth * 2 && mouse.x < buttonWidth * 3 && mouse.y >buttonHeight * 7 && mouse.y < buttonHeight * 8)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				screen = GameState::Game;
			}
		}
		if (mouse.x > buttonWidth * 2 && mouse.x < buttonWidth * 3 && mouse.y >buttonHeight * 8.5 && mouse.y < buttonHeight * 9.5)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				screen = GameState::Credits;
			}
		}
		if (mouse.x > buttonWidth * 2 && mouse.x < buttonWidth * 3 && mouse.y >buttonHeight * 10 && mouse.y < buttonHeight * 11)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				screen = GameState::Quit;
			}
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangle(buttonWidth * 2, buttonHeight * 7, buttonWidth, buttonHeight, WHITE);

		DrawRectangle(buttonWidth * 2, buttonHeight * 8.5, buttonWidth, buttonHeight, WHITE);

		DrawRectangle(buttonWidth * 2, buttonHeight * 10, buttonWidth, buttonHeight, WHITE);

		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
#include "Menu.h"

void MainMenu(GameState& screen, Vector2& mouse)
{
	float buttonWidth = screenWidth/5;
	float buttonHeight = screenHeight/12;

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

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 7), (int)buttonWidth, (int)buttonHeight, WHITE);

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 8.5), (int)buttonWidth, (int)buttonHeight, WHITE);

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 10), (int)buttonWidth, (int)buttonHeight, WHITE);

		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
#include "Credits.h"

void Credits(GameState& screen, Vector2& mouse)
{
	while (screen == GameState::Credits)
	{
		int buttonSize = 70;

		mouse = GetMousePosition();

		if (mouse.x > 10 && mouse.x < buttonSize + 10 && mouse.y > 10 && mouse.y < buttonSize + 10)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				screen = GameState::Menu;
			}
		}

		BeginDrawing();
		
		ClearBackground(BLACK);

		DrawRectangle(10, 10, buttonSize, buttonSize, WHITE);
		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
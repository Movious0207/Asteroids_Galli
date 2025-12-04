#include "credits.h"

void Credits::Logic(GameState& screen, Vector2& mouse, Texture background)
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
		
		DrawTextureEx(background, { 0,0}, 0, 0.9f, WHITE);

		DrawText("CREDITS", screenWidth / 2 - 130, screenHeight / 11, 60, WHITE);
		DrawText("ART", screenWidth / 2 -40, screenHeight / 5 + 50, 40, WHITE);
		DrawText("All by Angie Tabasso (Estudiante primer ano Arte y animacion para videojuegos)", screenWidth / 8, screenHeight / 4 + 50, 20, WHITE);
		DrawText("SOUND EFFECTS", screenWidth / 2 - 160, screenHeight / 3 + 70, 40, WHITE);
		DrawText("All by miself using bfxr", screenWidth / 3 + 60, screenHeight / 3 + 120, 20, WHITE);
		DrawText("MUSIC", screenWidth / 2 - 40, screenHeight / 2 + 70, 40, WHITE);
		DrawText("Game and Menu Music by Gaston A-P from Pixabay", screenWidth / 4, screenHeight / 2 + 110, 20, WHITE);

		DrawRectangle(10, 10, buttonSize, buttonSize, WHITE);
		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
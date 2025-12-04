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

		DrawText("CREDITS", screenWidth / 2 - 130, screenHeight / 5, 60, WHITE);
		DrawText("ART", screenWidth / 2 - 40, (screenHeight / 5) * 2, 40, WHITE);
		DrawText("All by Angie Tabasso (Estudiante primer ano Arte y animacion para videojuegos) (itch: https://birritadulce.itch.io)", screenWidth / 8, static_cast<int>((screenHeight / 5) * 2.5f), 15, WHITE);
		DrawText("SOUND EFFECTS", screenWidth / 2 - 160, (screenHeight / 5) * 3, 40, WHITE);
		DrawText("All by miself using bfxr (https://www.bfxr.net)", screenWidth / 4, static_cast<int>((screenHeight / 5) * 3.5f), 20, WHITE);
		DrawText("MUSIC", screenWidth / 2 - 60, (screenHeight / 5) * 4, 40, WHITE);
		DrawText("Game and Menu Music by Gaston A-P from Pixabay ", screenWidth / 4, static_cast<int>((screenHeight / 5) * 4.3f), 20, WHITE);
		DrawText("Game: https://pixabay.com/es/music/video-juegos-game-music-loop-19-153393/", screenWidth / 4 - 100, static_cast<int>((screenHeight / 5) * 4.5f), 20, WHITE);
		DrawText("Menu: https://pixabay.com/es/music/video-juegos-game-music-loop-18-153392/", screenWidth / 4 - 100, static_cast<int>((screenHeight / 5) * 4.7f), 20, WHITE);

		DrawRectangle(10, 10, buttonSize, buttonSize, WHITE);
		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
#include "menu.h"

void Menu::Logic(GameState& screen, Vector2& mouse, Texture background)
{
	Texture titleCard = LoadTexture("res/titleCard.png");

	Music menuMusic = LoadMusicStream("res/menuMusic.mp3");
	SetMusicVolume(menuMusic, 1.0f);

	float buttonWidth = screenWidth/5;
	float buttonHeight = screenHeight/12;

	while (screen == GameState::Menu)
	{
		if (!IsMusicStreamPlaying(menuMusic))
		{
			PlayMusicStream(menuMusic);
		}

		UpdateMusicStream(menuMusic);

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

		DrawTextureEx(background, { 0, 0 }, 0, 0.9f, WHITE);

		DrawTextureEx(titleCard, { 100, 0 }, 0, 0.5f, WHITE);

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 7), (int)buttonWidth, (int)buttonHeight, WHITE);

		DrawText("Play", (int)(buttonWidth * 2.3f), (int)(buttonHeight * 7.3f), 20, BLACK);

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 8.5f), (int)buttonWidth, (int)buttonHeight, WHITE);

		DrawText("Credits", (int)(buttonWidth * 2.3f), (int)(buttonHeight * 8.8f), 20, BLACK);

		DrawRectangle((int)(buttonWidth * 2), (int)(buttonHeight * 10), (int)buttonWidth, (int)buttonHeight, WHITE);

		DrawText("Quit", (int)(buttonWidth * 2.3f), (int)(buttonHeight * 10.3f), 20, BLACK);

		EndDrawing();

		if (WindowShouldClose())
		{
			screen = GameState::Quit;
		}
	}
}
#pragma once
#include "Asteroid.h"

void Game(GameState& screen, Vector2& mouse, Texture background);

void Conditions(Vector2& pos, float radius, int& lives, Asteroid asteroids[], bool& isPlaying, int& amount, float& invisibleTime, Sound takeDmg);

#pragma once
#include "Asteroid.h"

void Game(GameState& screen, Vector2& mouse);

void Conditions(Vector2& pos, float radius, int& lives, Asteroid asteroids[], bool& isPlaying);

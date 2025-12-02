#pragma once
#include "Constants.h"
#include "Asteroid.h"

void playerMovement(Vector2& pos, float& radius, float& playerAngle, float acceleration, Vector2& direction, Vector2& normalDir, Vector2& velocity);

void bulletLogic(Bullet bullet[], Vector2& direction, float bulletSpeed, Vector2 playerPos, Sound shoot);

void bulletDraw(Bullet bullet[], Texture fireball);
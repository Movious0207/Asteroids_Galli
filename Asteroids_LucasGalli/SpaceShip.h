#pragma once
#include "Constants.h"
#include "Asteroid.h"

void playerMovement(Vector2& pos, float& radius, float& playerAngle, float& accelerationX, float& accelerationY, Vector2& direction, Vector2& normalDir, float speed);

void bulletLogic(Bullet bullet[], float& accelerationX, float& accelerationY, Vector2& direction, float speed, Vector2 playerPos);

void bulletDraw(Bullet bullet[]);
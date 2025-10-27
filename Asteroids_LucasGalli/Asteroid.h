#pragma once
#include "SpaceShip.h"


float GetAsteroidRadius(AsteroidSize size);

void SplitAsteroid(Asteroid* asteroids, int index);

void AsteroidLogic(Asteroid asteroids[], int screenWidth, int screenHeight, Bullet bullet[]);

void AsteroidDraw(Asteroid asteroids[]);
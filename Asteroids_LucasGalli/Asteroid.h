#pragma once
#include "SpaceShip.h"

void AsteroidSpawner(Asteroid asteroids[], int& amount, float& spawnTime);

float GetAsteroidRadius(AsteroidSize size);

void SplitAsteroid(Asteroid* asteroids, int index);

void AsteroidLogic(Asteroid asteroids[], Bullet bullet[], int& score, Sound small, Sound medium, Sound big);

void AsteroidDraw(Asteroid asteroids[], Texture smallSlime, Texture mediumSlime, Texture bigSlime);
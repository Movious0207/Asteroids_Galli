#pragma once
#include "spaceShip.h"

namespace Asteroids
{
	void Spawner(Asteroid asteroids[], int& amount, float& spawnTime);

	void Logic(Asteroid asteroids[], Bullet bullet[], int& score, Sound small, Sound medium, Sound big);

	float GetRadius(AsteroidSize size);

	void Draw(Asteroid asteroids[], Texture smallSlime, Texture mediumSlime, Texture bigSlime);
}
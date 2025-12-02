#pragma once
#include "SpaceShip.h"

namespace Asteroids
{
	void Spawner(Asteroid asteroids[], int& amount, float& spawnTime);

	void Split(Asteroid* asteroids, int index);

	void Logic(Asteroid asteroids[], Bullet bullet[], int& score, Sound small, Sound medium, Sound big);

	float GetRadius(AsteroidSize size);

	void Draw(Asteroid asteroids[], Texture smallSlime, Texture mediumSlime, Texture bigSlime);
}
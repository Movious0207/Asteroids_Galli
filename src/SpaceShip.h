#pragma once

#include "Constants.h"
#include "Asteroid.h"

namespace player
{
	void Movement(Vector2& pos, float& radius, float& playerAngle, float acceleration, Vector2& direction, Vector2& normalDir, Vector2& velocity);
}

namespace bullet
{
	void Logic(Bullet bullet[], Vector2& direction, float bulletSpeed, Vector2 playerPos, Sound shoot);

	void Draw(Bullet bullet[], Texture fireball);
}
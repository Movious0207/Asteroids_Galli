#pragma once
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <ctime>

const int screenWidth = 1024;
const int screenHeight = 768;

const int MAX_BULLETS = 100;
const int MAX_ASTEROIDS = 100;

struct Bullet
{
	Vector2 position;
	Vector2 velocity;
    float angle;
	int size;
	bool active;
};

enum class AsteroidSize { LARGE, MEDIUM, SMALL, NONE };

struct Asteroid
{
    Vector2 position;
    Vector2 velocity;
    AsteroidSize size;
    bool active;
};

enum class GameState
{
    Menu = 1, Game, Credits, Quit
};
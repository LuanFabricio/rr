#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include "raylib.h"

#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080
#define MAX_FUEL 5000

#define ENEMIES_CAPACITY 255

static const float GAME_SPEED = 275.0f;

static const Vector2 player_size = {
	.x = 64.f,
	.y = 64.f,
};

static const Vector2 max_enemy_size = {
	.x = 42.f,
	.y = 42.f,
};

static const Vector2 min_enemy_size = {
	.x = 10.f,
	.y = 10.f,
};

static const Vector2 fuel_size = {
	.x = 28.f * 1.5f,
	.y = 42.f * 1.5f,
};

#endif // __CONSTANTS_H

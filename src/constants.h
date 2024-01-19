#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include "raylib.h"

#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

#define ENEMIES_CAPACITY 255

static const Vector2 player_size = {
	.x = 42.f,
	.y = 42.f,
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
	.x = 28.f,
	.y = 42.f,
};

#endif // __CONSTANTS_H

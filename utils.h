#ifndef __UTILS_H
#define __UTILS_H

#include "raylib.h"
#include "raymath.h"

#define GAME_WIDTH 1024
#define GAME_HEIGHT 720

Vector2 screen_center_point();

#endif // __UTILS_H
#ifdef UTILS_IMPLEMENTATION

Vector2 screen_center_point()
{
	return CLITERAL(Vector2) {
		.x = GAME_WIDTH / 2.f,
		.y = GAME_HEIGHT / 2.f,
	};
}

#endif // UTILS_IMPLEMENTATION

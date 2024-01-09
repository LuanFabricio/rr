#ifndef __UTILS_H
#define __UTILS_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define GAME_WIDTH 1024
#define GAME_HEIGHT 720

#define CREATE_FUNCTION_PTR(signature, name, args, return)\
	typedef return (*name##_t)args;\
	signature name##_t name =  NULL

Vector2 screen_center_point();
Vector2 random_game_point();
float random_float();

#endif // __UTILS_H
#ifdef UTILS_IMPLEMENTATION

Vector2 screen_center_point()
{
	return CLITERAL(Vector2) {
		.x = GAME_WIDTH / 2.f,
		.y = GAME_HEIGHT / 2.f,
	};
}

Vector2 random_game_point()
{
	return CLITERAL(Vector2) {
		.x = rand() % GAME_WIDTH,
		.y = rand() % GAME_HEIGHT,
	};
}

float random_float()
{
	return rand() / (double)RAND_MAX;
}

#endif // UTILS_IMPLEMENTATION

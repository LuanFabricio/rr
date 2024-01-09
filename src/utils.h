#ifndef __UTILS_H
#define __UTILS_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define RR_UTILS static

#define GAME_WIDTH 1024
#define GAME_HEIGHT 720

#define UNUSED_VAR(x) (void)(x)

#define CREATE_FUNCTION_PTR(signature, name, args, return)\
	typedef return (*name##_t)args;\
	signature name##_t name =  NULL

#ifdef UTILS_IMPLEMENTATION
#ifndef __UTILS_IMPLEMENTATION
#define __UTILS_IMPLEMENTATION

// TODO: Move functions to specific files
RR_UTILS Vector2 screen_center_point()
{
	return CLITERAL(Vector2) {
		.x = GAME_WIDTH / 2.f,
		.y = GAME_HEIGHT / 2.f,
	};
}

RR_UTILS Vector2 random_game_point()
{
	return CLITERAL(Vector2) {
		.x = (float)(rand() % GAME_WIDTH),
		.y = (float)(rand() % GAME_HEIGHT),
	};
}

RR_UTILS float random_float()
{
	return rand() / (double)RAND_MAX;
}

#endif // UTILS_IMPLEMENTATION
#endif // __UTILS_IMPLEMENTATION

#endif // __UTILS_H

#ifndef __UTILS_H
#define __UTILS_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "constants.h"

#define RR_UTILS static

#define UNUSED_VAR(x) (void)(x)

#define CREATE_FUNCTION_TYPE(name, args, return) typedef return (*name##_t)args;
#define CREATE_FUNCTION_PTR(signature, name) signature name##_t name =  NULL;

#ifdef UTILS_IMPLEMENTATION
#ifndef __UTILS_IMPLEMENTATION
#define __UTILS_IMPLEMENTATION

#ifdef SCREEN_UTILS
RR_UTILS Vector2 screen_center_point()
{
	return CLITERAL(Vector2) {
		.x = GAME_WIDTH / 2.f,
		.y = GAME_HEIGHT / 2.f,
	};
}
#endif

#ifdef RANDOM_UTILS
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
#endif // RANDOM_UTILS

#ifdef MOUSE_UTILS
RR_UTILS Vector2 get_game_mouse()
{
	Vector2 mouse = GetMousePosition();

	// Normalizing the mouse to current screen
	mouse.x /= (float)GetScreenWidth();
	mouse.y /= (float)GetScreenHeight();

	// Transforming to game screen
	mouse.x *= (float)GAME_WIDTH;
	mouse.y *= (float)GAME_HEIGHT;

	return mouse;
}
#endif // MOUSE_UTILS

#endif // UTILS_IMPLEMENTATION
#endif // __UTILS_IMPLEMENTATION

#endif // __UTILS_H

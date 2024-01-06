#ifndef __UTILS_H
#define __UTILS_H

#include "raylib.h"

#define GAME_MAX_X 20
#define GAME_MIN_X -20
#define GAME_MAX_Y 20
#define GAME_MIN_Y -20

Vector2 project_game_to_screen(Vector2 point);

#endif // __UTILS_H

#ifdef UTILS_IMPLEMENTATION

Vector2 project_game_to_screen(Vector2 point)
{
	Vector2 p = CLITERAL(Vector2){
		.x = (point.x/(GAME_MAX_X - GAME_MIN_X)) * GetScreenWidth(),
		.y = (point.y/(GAME_MAX_Y - GAME_MIN_Y)) * GetScreenHeight(),
	};

	return p;
}

#endif // UTILS_IMPLEMENTATION

#ifndef __PLAYER_H
#define __PLAYER_H

#include "raylib.h"
#include <stdbool.h>

#define __HOTRELOAD_IMPLEMENTATION
#include "hotreload.h"

// #include "utils.h"

typedef struct {
	Vector2 pos, size;
	float fuel;
} Ship;


#endif // __PLAYER_H

#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION


#define RR_PLAYER static

RR_PLAYER Ship player = {0};
RR_PLAYER void* player_shared_ptr = NULL;

typedef void (*player_start_t)(Ship*);
RR_PLAYER player_start_t player_start =  NULL;

typedef void (*player_draw_t)(Ship*);
RR_PLAYER player_draw_t player_draw =  NULL;

typedef void (*player_move_t)(Ship*);
RR_PLAYER player_move_t player_move =  NULL;

typedef void (*player_display_fuel_t)(Ship);
RR_PLAYER player_display_fuel_t player_display_fuel = NULL;

RR_PLAYER void reset_player_function()
{

	const char* file_path =  "build/objs/player.so";

	player_shared_ptr = hr_reset_file(file_path, player_shared_ptr);

	player_start = (player_start_t)hr_reset_function(player_shared_ptr, "player_start");
	player_draw = (player_draw_t)hr_reset_function(player_shared_ptr, "player_draw");
	player_move = (player_move_t)hr_reset_function(player_shared_ptr, "player_move");
	player_display_fuel = (player_display_fuel_t)hr_reset_function(player_shared_ptr, "player_display_fuel");
}

#endif // PLAYER_IMPLEMENTATION

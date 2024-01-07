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

#define CREATE_FUNCTION_PTR(name, args, return)\
	typedef return (*name##_t)args;\
	RR_PLAYER name##_t name =  NULL

CREATE_FUNCTION_PTR(player_start, (Ship*), void);

CREATE_FUNCTION_PTR(player_draw_game, (Ship), void);

CREATE_FUNCTION_PTR(player_update, (Ship*), void);

CREATE_FUNCTION_PTR(player_draw_ui, (Ship), void);

#undef CREATE_FUNCTION_PTR

typedef void (*player_display_fuel_t)(Ship);
RR_PLAYER player_display_fuel_t player_display_fuel = NULL;

RR_PLAYER void reset_player_function()
{

	const char* file_path =  "build/objs/player.so";

	player_shared_ptr = hr_reset_file(file_path, player_shared_ptr);

	player_start = (player_start_t)hr_reset_function(player_shared_ptr, "player_start");
	player_draw_game = (player_draw_game_t)hr_reset_function(player_shared_ptr, "player_draw_game");
	player_update = (player_update_t)hr_reset_function(player_shared_ptr, "player_update");
	player_draw_ui = (player_draw_ui_t)hr_reset_function(player_shared_ptr, "player_draw_ui");
	player_display_fuel = (player_display_fuel_t)hr_reset_function(player_shared_ptr, "player_display_fuel");
}

#endif // PLAYER_IMPLEMENTATION

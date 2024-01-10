#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdbool.h>
#include "raylib.h"
#include "fuel.h"
#include "types.h"

// #include "utils.h"

#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

#define RR_PLAYER static
RR_PLAYER void* player_shared_ptr = NULL;

static Player_Functions player_functions = {
	.start = NULL,
	.draw_game = NULL,
	.update = NULL,
	.draw_ui = NULL,
};

RR_PLAYER void reset_player_function()
{

	const char* file_path =  "build/objs/player.so";

	player_shared_ptr = hr_reset_file(file_path, player_shared_ptr);

	player_functions.start = (player_start_t)hr_reset_function(player_shared_ptr, "player_start");
	player_functions.draw_game = (player_draw_game_t)hr_reset_function(player_shared_ptr, "player_draw_game");
	player_functions.update = (player_update_t)hr_reset_function(player_shared_ptr, "player_update");
	player_functions.draw_ui = (player_draw_ui_t)hr_reset_function(player_shared_ptr, "player_draw_ui");
}

#else

void player_start(Ship *player);
void player_update(Ship* player);
void player_draw_game(const Ship player);
void player_draw_ui(const Ship player);

static Player_Functions player_functions = {
	.player_start = player_start,
	.player_draw_game = player_draw_game,
	.player_update = player_update,
	.player_draw_ui = player_draw_ui,
};

#endif // PLAYER_IMPLEMENTATION

#endif // __PLAYER_H

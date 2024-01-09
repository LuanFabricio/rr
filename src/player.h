#ifndef __PLAYER_H
#define __PLAYER_H

#include <stdbool.h>
#include "raylib.h"
#include "fuel.h"

// #include "utils.h"

typedef struct {
	Vector2 pos, size;
	float fuel;
} Ship;


#endif // __PLAYER_H

#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

#define RR_PLAYER static
RR_PLAYER void* player_shared_ptr = NULL;

CREATE_FUNCTION_PTR(RR_PLAYER, player_start, (Ship*), void);
CREATE_FUNCTION_PTR(RR_PLAYER, player_draw_game, (Ship), void);
CREATE_FUNCTION_PTR(RR_PLAYER, player_update, (Ship*, Fuel_Container*), void);
CREATE_FUNCTION_PTR(RR_PLAYER, player_draw_ui, (Ship), void);

RR_PLAYER void reset_player_function()
{

	const char* file_path =  "build/objs/player.so";

	player_shared_ptr = hr_reset_file(file_path, player_shared_ptr);

	player_start = (player_start_t)hr_reset_function(player_shared_ptr, "player_start");
	player_draw_game = (player_draw_game_t)hr_reset_function(player_shared_ptr, "player_draw_game");
	player_update = (player_update_t)hr_reset_function(player_shared_ptr, "player_update");
	player_draw_ui = (player_draw_ui_t)hr_reset_function(player_shared_ptr, "player_draw_ui");
}

#else

void player_start(Ship *player);
void player_update(Ship* player, Fuel_Container* container);
void player_draw_game(const Ship player);
void player_draw_ui(const Ship player);

#endif // PLAYER_IMPLEMENTATION

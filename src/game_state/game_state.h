#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include "../types.h"

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "../../hotreload.h"

static GameState_Functions gamestate_functions = {
	.update = NULL,
};

static void* gamestate_shared_ptr = NULL;

static void reset_gamestate_function()
{
	const char* file_path = "build/objs/game_state.so";

	gamestate_shared_ptr = hr_reset_file(file_path, gamestate_shared_ptr);

	gamestate_functions.update = (gamestate_update_t)hr_reset_function(gamestate_shared_ptr, "gamestate_update");
	gamestate_functions.apply = (gamestate_apply_t)hr_reset_function(gamestate_shared_ptr, "gamestate_apply");
}

#else

void gamestate_update(GameState *game_state, GameVars *game_vars);
void gamestate_apply(const GameState *game_state, const GameFunctions *game_fn, GameVars *game_vars);

static GameState_Functions gamestate_functions = {
	.update = gamestate_update,
	.apply = gamestate_apply,
};

#endif // DEBUG

#endif // __GAME_STATE_H

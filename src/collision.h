#ifndef __COLLISION_H
#define __COLLISION_H

#include "types.h"

#define RR_COLLISION static

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

static Collision_Functions collision_functions = {
	.check_player = NULL,
};

void *collision_shared_ptr = NULL;

void reset_collision_function()
{
	const char* file_path =  "build/objs/collision.so";
	collision_shared_ptr = hr_reset_file(file_path, collision_shared_ptr);

	collision_functions.check_player = (collision_check_player_t)hr_reset_function(collision_shared_ptr, "collision_check_player");
}
#else
void collision_check_player(Ship *player, Fuel_Container *container, const Fuel_Functions *fuel_func);

static Collision_Functions collision_functions = {
	.check_player = collision_check_player,
};

#endif // DEBUG

#endif // __COLLISION_H

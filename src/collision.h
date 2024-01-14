#ifndef __COLLISION_H
#define __COLLISION_H

#include "types.h"

#define RR_COLLISION static

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

static Collision_Functions collision_functions = {
	.check_player_fuel = NULL,
};

void *collision_shared_ptr = NULL;

void reset_collision_function()
{
	const char* file_path =  "build/objs/collision.so";
	collision_shared_ptr = hr_reset_file(file_path, collision_shared_ptr);

	collision_functions.check_player_fuel = (collision_check_player_fuel_t)hr_reset_function(collision_shared_ptr, "collision_check_player_fuel");
	collision_functions.check_player_enemies = (collision_check_player_enemies_t)hr_reset_function(collision_shared_ptr, "collision_check_player_enemies");
}
#else
void collision_check_player_fuel(Ship *player, Fuel_Container *container, const Fuel_Functions *fuel_func);
void collision_check_player_enemies(Ship *player, Enemies *enemies, const Enemy_Functions *enemy_func);

static Collision_Functions collision_functions = {
	.check_player_fuel = collision_check_player_fuel,
	.check_player_enemies = collision_check_player_enemies,
};

#endif // DEBUG

#endif // __COLLISION_H

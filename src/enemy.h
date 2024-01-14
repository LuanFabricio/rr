#ifndef __ENEMY_H
#define __ENEMY_H

#include <stdlib.h>
#include "types.h"

static Enemies enemies = { .size = 0 };

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"

#include "utils.h"

static Enemy_Functions enemy_functions = {
	.draw = NULL,
	.draw_arr = NULL,
	.spawn = NULL,
};

void *enemy_shared_ptr = NULL;

void reset_enemy_function()
{
	const char* file_path = "build/objs/enemy.so";
	enemy_shared_ptr = hr_reset_file(file_path, enemy_shared_ptr);

	enemy_functions.draw = (enemy_draw_t)hr_reset_function(enemy_shared_ptr, "enemy_draw");
	enemy_functions.draw_arr = (enemy_draw_arr_t)hr_reset_function(enemy_shared_ptr, "enemy_draw_arr");
	enemy_functions.spawn = (enemy_spawn_t)hr_reset_function(enemy_shared_ptr, "enemy_spawn");
	enemy_functions.spawn_random = (enemy_spawn_random_t)hr_reset_function(enemy_shared_ptr, "enemy_spawn_random");
	enemy_functions.destroy = (enemy_destroy_t)hr_reset_function(enemy_shared_ptr, "enemy_destroy");
}

#else

void enemy_draw(const Ship* enemy);
void enemy_draw_arr(const Enemies* enemies);
void enemy_spawn_random(Enemies* enemies);
void enemy_spawn(Enemies* enemies, Ship new_enemy);
void enemy_destroy(Enemies* enemies, size_t enemy_index);

static Enemy_Functions enemy_functions = {
	.draw = enemy_draw,
	.draw_arr = enemy_draw_arr,
	.spawn = enemy_spawn,
	.spawn_random = enemy_spawn_random,
	.destroy = enemy_destroy,
};

#endif // DEBUG

#endif //  __ENEMY_H

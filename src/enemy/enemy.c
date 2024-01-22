#include <stdio.h>
#include <assert.h>
#include "raylib.h"
#include "../constants.h"

#define UTILS_IMPLEMENTATION
#define RANDOM_UTILS
#include "../utils.h"

#include "../types.h"

#define ENEMY_COLOR CLITERAL(Color){ 255, 0, 255, 255 }

#define MIN_Y_SPAWN -420.f

void enemy_spawn(Enemies *enemies, Ship new_enemy)
{
	assert(enemies->size < ENEMIES_CAPACITY);

	enemies->data[enemies->size] = new_enemy;
	enemies->size += 1;
}

void enemy_spawn_random(Enemies *enemies)
{
	Vector2 enemy_size = {
		.x = min_enemy_size.x + random_float() * max_enemy_size.x,
		.y = min_enemy_size.x + random_float() * max_enemy_size.x,
	};

	Ship enemy = {
		.pos = random_game_point(),
		.size = enemy_size,
	};
	enemy.pos.y = -enemy.size.y + random_float() * MIN_Y_SPAWN;

	enemy_spawn(enemies, enemy);
}

void enemy_destroy(Enemies* enemies, size_t enemy_index)
{
	assert(enemies->size > enemy_index);
	assert(enemies->size > 0);

	enemies->size -= 1;
	enemies->data[enemy_index] = enemies->data[enemies->size];
}

void enemy_update(Enemies *enemies)
{
	for (size_t i =  0; i < enemies->size; i++) {
		enemies->data[i].pos.y += 275.f * GetFrameTime();

		if (enemies->data[i].pos.y >= GAME_HEIGHT) {
			enemy_destroy(enemies, i);
			i--;
		}
	}
}

void enemy_draw(const Ship * enemy)
{
	DrawRectangleV(enemy->pos, enemy->size, ENEMY_COLOR);
}

void enemy_draw_arr(const Enemies *enemies)
{
	for (size_t i = 0; i < enemies->size; i++) {
		enemy_draw(&enemies->data[i]);
	}
}

#ifndef __TYPES_H
#define __TYPES_H

#include <stdlib.h>
#include "raylib.h"
#include "utils.h"

// ======================================= FUEL =======================================

typedef struct {
	Vector2 pos;
	float content;
} Fuel;

#define CONTAINER_CAPACITY 255

typedef struct {
	Fuel fuel[CONTAINER_CAPACITY];
	size_t size;
} Fuel_Container;

CREATE_FUNCTION_TYPE(fuel_spawn, (Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_draw, (const Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_destroy, (Fuel_Container*, size_t), void);

typedef struct {
	fuel_spawn_t spawn;
	fuel_draw_t draw;
	fuel_destroy_t destroy;
} Fuel_Functions;

// ======================================= PLAYER =======================================

typedef struct {
	Vector2 pos, size;
	float fuel;
} Ship;

CREATE_FUNCTION_TYPE(player_start, (Ship*), void);
CREATE_FUNCTION_TYPE(player_draw_game, (Ship), void);
CREATE_FUNCTION_TYPE(player_update, (Ship*), void);
CREATE_FUNCTION_TYPE(player_draw_ui, (Ship), void);

typedef struct {
	player_start_t start;
	player_draw_game_t draw_game;
	player_update_t update;
	player_draw_ui_t draw_ui;
} Player_Functions;

// ======================================= COLLISION =======================================

CREATE_FUNCTION_TYPE(collision_check_player, (Ship *player, Fuel_Container *container, const Fuel_Functions *fuel_func), void);

typedef struct {
	collision_check_player_t check_player;
} Collision_Functions;

#endif // __TYPES_H

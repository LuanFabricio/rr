#ifndef __TYPES_H
#define __TYPES_H

#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "utils.h"
#include "constants.h"

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

CREATE_FUNCTION_TYPE(fuel_load_texture, (void), void);
CREATE_FUNCTION_TYPE(fuel_spawn, (Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_draw, (const Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_destroy, (Fuel_Container*, size_t), void);

typedef struct {
	fuel_load_texture_t load_texture;
	fuel_spawn_t spawn;
	fuel_draw_t draw;
	fuel_destroy_t destroy;
} Fuel_Functions;

// ======================================= PLAYER =======================================

typedef struct {
	Vector2 pos, size;
	float fuel;
	bool alive;
	Texture2D texture;
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

// ======================================= ENEMY =======================================

typedef struct {
	Ship data[ENEMIES_CAPACITY];
	size_t size;
} Enemies;

CREATE_FUNCTION_TYPE(enemy_draw, (const Ship*), void);
CREATE_FUNCTION_TYPE(enemy_draw_arr, (const Enemies*), void);
CREATE_FUNCTION_TYPE(enemy_spawn, (Enemies*, Ship), void);
CREATE_FUNCTION_TYPE(enemy_spawn_random, (Enemies*), void);
CREATE_FUNCTION_TYPE(enemy_destroy, (Enemies*, size_t), void);
CREATE_FUNCTION_TYPE(enemy_update, (Enemies*), void);

typedef struct {
	enemy_draw_t draw;
	enemy_draw_arr_t draw_arr;
	enemy_spawn_t spawn;
	enemy_spawn_random_t spawn_random;
	enemy_destroy_t destroy;
	enemy_update_t update;
} Enemy_Functions;

// ======================================= COLLISION =======================================

CREATE_FUNCTION_TYPE(collision_check_player_fuel, (Ship *player, Fuel_Container *container, const Fuel_Functions *fuel_func), void);
CREATE_FUNCTION_TYPE(collision_check_player_enemies, (Ship *player, Enemies *enemies, const Enemy_Functions *enemy_func), void);

typedef struct {
	collision_check_player_fuel_t check_player_fuel;
	collision_check_player_enemies_t check_player_enemies;
} Collision_Functions;

// ======================================= GAME =======================================


typedef struct {
	Player_Functions player_fn;
	Fuel_Functions fuel_fn;
	Enemy_Functions enemy_fn;
	Collision_Functions collision_fn;
} GameFunctions;

typedef struct {
	Ship player;
	Fuel_Container container;
	Enemies enemies;
	RenderTexture2D screen_texture;
} GameVars;

// ======================================= GAME STATE =======================================

typedef enum {
	MENU = 0,
	PLAY = 1,
	DEAD = 2,
} GameStateEnum;

typedef struct {
	GameStateEnum current_state;
} GameState;

CREATE_FUNCTION_TYPE(gamestate_update, (GameState *game_state, GameVars *game_vars), void);
CREATE_FUNCTION_TYPE(gamestate_apply, (GameState *game_state, const GameFunctions *game_fn, GameVars *game_vars), void);

typedef struct {
	gamestate_update_t update;
	gamestate_apply_t apply;
} GameState_Functions;


#endif // __TYPES_H

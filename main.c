#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include "src/types.h"

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "hotreload.h"
#else
#define PLAYER_IMPLEMENTATION
#endif // DEBUG
#include "src/player/player.h"
#include "src/game_state/game_state.h"
#include "src/collision/collision.h"
#include "src/fuel/fuel.h"
#include "src/enemy/enemy.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE_NAME "River raider"

void draw_middle_line()
{
	int half_width = GAME_WIDTH >> 1;
	int half_height = GAME_HEIGHT >> 1;

	DrawLine(half_width, 0, half_width, GAME_HEIGHT, RAYWHITE);
	DrawLine(0, half_height, GAME_WIDTH, half_height, RAYWHITE);
}

int main(void)
{
#ifdef DEBUG
	const reset_func_t reset_functions[] = {
		&reset_player_function,
		&reset_fuel_function,
		&reset_collision_function,
		&reset_enemy_function,
		&reset_gamestate_function,
	};
	hr_init(CALC_SIZEOF(reset_functions), reset_functions);
	hr_reset_all();
#endif // DEBUG

	Ship player = {0};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
	SetTargetFPS(75);
	srand(time(NULL));

	RenderTexture2D screen = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

	fuel_functions.load_texture();
	player_functions.start(&player);
	Vector2 ball_velocity = CLITERAL(Vector2){ .x = 250.f, .y = 250.f };
	Vector2 ball_pos = CLITERAL(Vector2){ .x = 42.f, .y = 42.f };

	Fuel_Container container = {0};
	container.size = 0;

	enemy_functions.spawn_random(&enemies);
	enemy_functions.spawn_random(&enemies);
	enemy_functions.spawn_random(&enemies);
	enemy_functions.spawn_random(&enemies);

	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);

	fuel_functions.destroy(&container, 1);
	fuel_functions.destroy(&container, 0);
	fuel_functions.destroy(&container, 100);

	GameState gamestate = {0};
	gamestate.current_state = MENU;

	GameFunctions game_fn = {
		.player_fn = player_functions,
		.enemy_fn = enemy_functions,
		.fuel_fn = fuel_functions,
		.collision_fn = collision_functions,
	};

	GameVars game_vars = {
		.player = player,
		.enemies = enemies,
		.container = container,
		.screen_texture = screen,
	};

	game_fn.enemy_fn.load_texture();

	SetExitKey(KEY_NULL);

	while (!WindowShouldClose()) {
		// player_functions.update(&player);
		gamestate_functions.update(&gamestate, &game_vars);

		if (IsKeyPressed(KEY_T)) {
			enemy_functions.spawn_random(&game_vars.enemies);
			enemy_functions.spawn_random(&game_vars.enemies);
			enemy_functions.spawn_random(&game_vars.enemies);
			enemy_functions.spawn_random(&game_vars.enemies);
		}

		if (IsKeyPressed(KEY_Y)) {
			fuel_functions.spawn(&game_vars.container);
		}

#ifdef DEBUG
		if (IsKeyPressed(KEY_R)) {
			hr_reset_all();
			game_fn.enemy_fn.load_texture();
			player_functions.start(&player);
			fuel_functions.load_texture();
		}
#endif // DEBUG

		gamestate_functions.apply(&gamestate, &game_fn, &game_vars);

		continue;

		BeginTextureMode(screen);

		ClearBackground(BLACK);

		fuel_functions.draw(&container);
		player_functions.draw_game(player);
		enemy_functions.draw_arr(&enemies);
		DrawCircleV(ball_pos, 42, RED);

		player_functions.draw_ui(player);
		draw_middle_line();

		EndTextureMode();

		BeginDrawing();

		DrawTexturePro(
			screen.texture,
			CLITERAL(Rectangle){ .x = 0, .y = 0, .width = screen.texture.width, .height = -screen.texture.height },
			CLITERAL(Rectangle){ .x = 0, .y = 0, .width = GetScreenWidth(), .height = GetScreenHeight() },
			CLITERAL(Vector2){ 0, 0 },
			0,
			WHITE
		);

		EndDrawing();

		ball_pos = Vector2Add(ball_pos, Vector2Scale(ball_velocity, GetFrameTime()));

		if (ball_pos.x < 42 || ball_pos.x >= GAME_WIDTH - 42) {
			ball_velocity.x = -ball_velocity.x;
		}

		if (ball_pos.y < 42 || ball_pos.y >= GAME_HEIGHT - 42) {
			ball_velocity.y = -ball_velocity.y;
		}

		collision_functions.check_player_fuel(&player, &container, &fuel_functions);
		collision_functions.check_player_enemies(&player, &enemies, &enemy_functions);

		enemy_functions.update(&enemies);
	}

	UnloadRenderTexture(screen);

#ifdef DEBUG
	hr_end();
#endif // DEBUG

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"
#include "src/collision.h"
#include "src/fuel.h"

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "hotreload.h"
#else
#define PLAYER_IMPLEMENTATION
#endif // DEBUG
#include "./src/player.h"

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
	};
	hr_init(CALC_SIZEOF(reset_functions), reset_functions);
	hr_reset_all();
#endif // DEBUG

	Ship player = {0};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
	SetTargetFPS(120);

	RenderTexture2D screen = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

	player_functions.start(&player);
	Vector2 ball_velocity = CLITERAL(Vector2){ .x = 250.f, .y = 250.f };
	Vector2 ball_pos = CLITERAL(Vector2){ .x = 42.f, .y = 42.f };

	Fuel_Container container = {0};
	container.size = 0;

	srand(time(NULL));
	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);
	fuel_functions.spawn(&container);

	fuel_functions.destroy(&container, 1);
	fuel_functions.destroy(&container, 0);
	fuel_functions.destroy(&container, 100);

	while (!WindowShouldClose()) {
		player_functions.update(&player);

#ifdef DEBUG
		if (IsKeyPressed(KEY_R)) {
			hr_reset_all();
		}
#endif // DEBUG

		BeginTextureMode(screen);

		ClearBackground(BLACK);

		fuel_functions.draw(&container);
		player_functions.draw_game(player);
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

		collision_functions.check_player(&player, &container, &fuel_functions);
	}

	UnloadRenderTexture(screen);

#ifdef DEBUG
	hr_end();
#endif // DEBUG

	return 0;
}

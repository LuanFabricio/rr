#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "hotreload.h"
#else
#define PLAYER_IMPLEMENTATION
#endif // DEBUG
#include "./src/player.h"

#include "./src/utils.h"

#define SCREEN_WIDTH GAME_WIDTH
#define SCREEN_HEIGHT GAME_HEIGHT
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
	};
	hr_init(CALC_SIZEOF(reset_functions), reset_functions);
	hr_reset_all();
#endif // DEBUG

	Ship player = {0};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);

	RenderTexture2D screen = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

	player_start(&player);
	Vector2 ball_velocity = CLITERAL(Vector2){ .x = 0.05f, .y = 0.05f };
	Vector2 ball_pos = CLITERAL(Vector2){ .x = 42.f, .y = 42.f };

	while (!WindowShouldClose()) {
		player_update(&player);

#ifdef DEBUG
		if (IsKeyPressed(KEY_R)) {
			hr_reset_all();
		}
#endif // DEBUG

		BeginTextureMode(screen);

		ClearBackground(BLACK);

		player_draw_game(player);
		DrawCircleV(ball_pos, 42, RED);

		player_draw_ui(player);
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

		printf("player.pos = { %.02f, %.02f }\n", player.pos.x, player.pos.y);

		ball_pos = Vector2Add(ball_pos, ball_velocity);

		if (ball_pos.x < 42 || ball_pos.x >= GAME_WIDTH - 42) {
			ball_velocity.x = -ball_velocity.x;
		}

		if (ball_pos.y < 42 || ball_pos.y >= GAME_HEIGHT - 42) {
			ball_velocity.y = -ball_velocity.y;
		}
	}

	UnloadRenderTexture(screen);

#ifdef DEBUG
	hr_end();
#endif // DEBUG

	return 0;
}

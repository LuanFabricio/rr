#include <stdio.h>
#include "hotreload.h"
#include "raylib.h"
#include "raymath.h"

#include "utils.h"
#include "player.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE_NAME "River raider"

#define PLAYER_COLOR BLUE

void draw_middle_line()
{
	int half_width = GAME_WIDTH >> 1;
	int half_height = GAME_HEIGHT >> 1;

	DrawLine(half_width, 0, half_width, GAME_HEIGHT, RAYWHITE);
	DrawLine(0, half_height, GAME_WIDTH, half_height, RAYWHITE);
}

int main(void)
{
	const reset_func_t reset_functions[] = {
		&reset_player_function,
	};
	hr_init(CALC_SIZEOF(reset_functions), reset_functions);
	hr_reset_all();

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);

	RenderTexture2D screen = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

	player_start(&player);
	Vector2 ball_velocity = CLITERAL(Vector2){ .x = 0.05f, .y = 0.05f };
	Vector2 ball_pos = CLITERAL(Vector2){ .x = 42.f, .y = 42.f };

	while (!WindowShouldClose()) {
		player_update(&player);

		if (IsKeyPressed(KEY_R)) {
			hr_reset_all();
		}

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

		ball_pos = Vector2Add(ball_pos, ball_velocity);

		if (ball_pos.x < 42 || ball_pos.x >= GAME_WIDTH - 42) {
			ball_velocity.x = -ball_velocity.x;
		}

		if (ball_pos.y < 42 || ball_pos.y >= GAME_HEIGHT - 42) {
			ball_velocity.y = -ball_velocity.y;
		}
	}

	UnloadRenderTexture(screen);
	hr_end();

	return 0;
}

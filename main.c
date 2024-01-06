#include <stdio.h>
#include "hotreload.h"
#include "raylib.h"
#include "raymath.h"

#include "player.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TITLE_NAME "River raider"

#define PLAYER_COLOR BLUE

void draw_middle_line()
{
	int half_width = GetScreenWidth() >> 1;
	int half_height = GetScreenHeight() >> 1;

	DrawLine(half_width, 0, half_width, GetScreenHeight(), RAYWHITE);
	DrawLine(0, half_height, GetScreenWidth(), half_height, RAYWHITE);
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

	player_start(&player);
	Vector2 ball_velocity = CLITERAL(Vector2){ .x = 0.05f, .y = 0.05f };
	Vector2 ball_pos = CLITERAL(Vector2){ .x = 42.f, .y = 42.f };

	while (!WindowShouldClose()) {
		player_move(&player);
		if (IsKeyPressed(KEY_R)) {
			hr_reset_all();
		}

		BeginDrawing();
		ClearBackground(BLACK);

		player_draw(&player);
		DrawCircleV(ball_pos, 42, RED);

		player_display_fuel(player);
		draw_middle_line();

		EndDrawing();

		ball_pos = Vector2Add(ball_pos, ball_velocity);

		if (ball_pos.x < 42 || ball_pos.x >= GetScreenWidth() - 42) {
			ball_velocity.x = -ball_velocity.x;
		}

		if (ball_pos.y < 42 || ball_pos.y >= GetScreenHeight() - 42) {
			ball_velocity.y = -ball_velocity.y;
		}
	}

	hr_end();

	return 0;
}

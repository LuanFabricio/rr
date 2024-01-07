#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define PLAYER_IMPLEMENTATION
#include "player.h"
#define UTILS_IMPLEMENTATION
#include "utils.h"
#define PLAYER_COLOR BLUE

#define MAX_FUEL 50000

// Inner functions declarations
void _player_display_fuel(Ship player);
void _player_move(Ship* player);

// Extern functions implementation

void player_start(Ship *player)
{
	player->size = CLITERAL(Vector2){42.f, 42.f};

	player->pos.x = (GAME_MAX_X + GAME_MIN_X) / 2.f;
	player->pos.y = (GAME_MAX_Y + GAME_MIN_Y) / 2.f;

	player->fuel = MAX_FUEL;
}

void player_draw_game(const Ship player)
{
	Vector2 half_size = CLITERAL(Vector2) {
		.x = player.size.x / 2.f,
		.y = player.size.y / 2.f,
	};
	Vector2 player_pos = project_game_to_screen(player.pos);

	DrawRectangleV(Vector2Subtract(player_pos, half_size), player.size, PLAYER_COLOR);
}

void player_draw_ui(Ship player)
{
	_player_display_fuel(player);
}

void player_update(Ship* player)
{
	if (player->fuel > 0) {
		player->fuel -= 0.5f;
	} else {
		player->fuel = 0;
	}

	_player_move(player);
}

// Inner functions implementation

void _player_display_fuel(Ship player)
{
	// Debug implementation
	const size_t BUFFER_SIZE = 255;
	const size_t FONT_SIZE = 32;

	char* fuel_text = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	snprintf(fuel_text, BUFFER_SIZE, "Fuel remaning: %.02f", player.fuel);

	int width = MeasureText(fuel_text, FONT_SIZE);
	int pos_x = (GetScreenWidth() - width) >> 1;
	int pos_y = FONT_SIZE;

	DrawText(fuel_text, pos_x, pos_y, FONT_SIZE, RAYWHITE);

	free(fuel_text);

	// Final implementation
	float fuel = Normalize(player.fuel, 0, MAX_FUEL) * -PI - PI;

	Vector2 start = {
		.x = (GAME_MAX_X + GAME_MIN_X) / 2.f,
		.y = GAME_MIN_Y + 5.f,
	};

	printf("start.x = %.02f\nstart.y = %.02f\n", start.x, start.y);

	Vector2 end = {
		.x  = cosf(fuel),
		.y  = -sinf(fuel),
	};
	end = Vector2Scale(end, 3.f);
	end = Vector2Add(end, start);

	DrawLineEx(project_game_to_screen(start), project_game_to_screen(end), 3.5f, RAYWHITE);
}

void _player_move(Ship* player)
{
	Vector2 acceleration = Vector2Zero();

	if (IsKeyDown(KEY_W)) {
		acceleration.y -= 1;
	}

	if (IsKeyDown(KEY_S)) {
		acceleration.y += 1;
	}

	if (IsKeyDown(KEY_A)) {
		acceleration.x -= 1;
	}

	if (IsKeyDown(KEY_D)) {
		acceleration.x += 1;
	}

	const float speed = 0.005f;
	acceleration = Vector2Normalize(acceleration);
	acceleration = Vector2Scale(acceleration, speed);

	player->pos = Vector2Add(player->pos, acceleration);
}

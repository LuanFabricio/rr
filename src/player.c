#include <stdio.h>
#include <stdlib.h>
#include "fuel.h"
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
void _player_check_fuel_collision(Ship* player, Fuel_Container *container);

// Extern functions implementation

void player_start(Ship *player)
{
	player->size = CLITERAL(Vector2){ 42.f, 42.f };

	const Vector2 screen_center = screen_center_point();
	player->pos.x = screen_center.x - player->size.x / 2.f;
	player->pos.y = screen_center.y - player->size.y / 2.f;

	player->fuel = MAX_FUEL;
}

void player_draw_game(const Ship player)
{
	DrawRectangleV(player.pos, player.size, PLAYER_COLOR);
}

void player_draw_ui(Ship player)
{
	_player_display_fuel(player);

	DrawFPS(15, 15);
}

void player_update(Ship* player, Fuel_Container* container)
{
	if (player->fuel > 0) {
		player->fuel -= 0.5f;
	} else {
		player->fuel = 0;
	}

	_player_move(player);
	_player_check_fuel_collision(player, container);
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
	int pos_x = (GAME_WIDTH - width) >> 1;
	int pos_y = FONT_SIZE >> 1;

	DrawText(fuel_text, pos_x, pos_y, FONT_SIZE, RAYWHITE);

	free(fuel_text);

	// Final implementation
	float fuel_radians = Normalize(player.fuel, 0, MAX_FUEL) * -PI - PI;

	const Vector2 center = screen_center_point();
	Vector2 start = {
		.x = center.x,
		.y = 125.f,
	};

	Vector2 end = {
		.x  = cosf(fuel_radians),
		.y  = -sinf(fuel_radians),
	};

	const float mag = 75.f;
	end = Vector2Scale(end, mag);
	end = Vector2Add(end, start);

	DrawLineEx(start, end, 3.5f, RAYWHITE);
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

	const float speed = 300.f;
	acceleration = Vector2Scale(Vector2Normalize(acceleration), speed * GetFrameTime());

	player->pos = Vector2Add(player->pos, acceleration);

	const Vector2 min_pos = CLITERAL(Vector2){ 0.f, 0.f };
	const Vector2 max_pos = CLITERAL(Vector2){ GAME_WIDTH - player->size.x, GAME_HEIGHT - player->size.y };
	player->pos = Vector2Clamp(player->pos, min_pos, max_pos);
}

void _player_check_fuel_collision(Ship* player, Fuel_Container *container);

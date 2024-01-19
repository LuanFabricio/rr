#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define UTILS_IMPLEMENTATION
#define SCREEN_UTILS
#include "../utils.h"
#include "../types.h"
#include "../constants.h"

#define PLAYER_COLOR BLUE
#define MAX_FUEL 5000
#define PLAYER_FUEL_DECAY 0.25f
#define FUEL_INDICATOR_MAGNITUDE 105.f

// Inner functions declarations
void _player_display_fuel(Ship player);
void _player_move(Ship* player);
Texture2D _player_load_texture();

// Extern functions implementation

void player_start(Ship *player)
{

	player->fuel = MAX_FUEL;
	player->alive = true;

	player->texture = _player_load_texture();
	player->size.x = player->texture.width;
	player->size.y = player->texture.height;

	const Vector2 screen_center = screen_center_point();
	player->pos.x = screen_center.x - player->size.x / 2.f;
	player->pos.y = screen_center.y - player->size.y / 2.f;
}

void player_draw_game(const Ship player)
{
	DrawTextureV(player.texture, player.pos, RAYWHITE);
	// DrawRectangleV(player.pos, player.size, PLAYER_COLOR);
}

void player_draw_ui(Ship player)
{
	_player_display_fuel(player);

	DrawFPS(15, 15);
}

void player_update(Ship* player)
{
	if (player->fuel > 0) {
		player->fuel -= PLAYER_FUEL_DECAY;
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

	end = Vector2Scale(end, FUEL_INDICATOR_MAGNITUDE);
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

Texture2D _player_load_texture()
{
	Image img = LoadImage("./assets/ship/ship.png");
	ImageResizeNN(&img, player_size.x, player_size.y);
	Texture2D tex = LoadTextureFromImage(img);
	UnloadImage(img);

	return tex;
}

#include <stdio.h>
#include "raylib.h"

#define UTILS_IMPLEMENTATION
#define SCREEN_UTILS
#include "../utils.h"

#include "../types.h"

// Inner functions declaration
void _draw_scene_on_texture(const GameFunctions *game_fn, const GameVars *game_vars);
void _draw_scene_on_screen(const GameFunctions *game_fn, const GameVars *game_vars);

// Extern functions
void gamestate_update(GameState *game_state)
{
	game_state->current_state = PLAY;
}

void gamestate_apply(const GameState *game_state, const GameFunctions *game_fn, GameVars *game_vars)
{
	switch (game_state->current_state) {
		case PLAY: {
			printf("Enemies: %zu\n", game_vars->enemies.size);
			game_fn->player_fn.update(&game_vars->player);

			_draw_scene_on_texture(game_fn, game_vars);
			_draw_scene_on_screen(game_fn, game_vars);

			game_fn->collision_fn.check_player_fuel(&game_vars->player, &game_vars->container, &game_fn->fuel_fn);
			game_fn->collision_fn.check_player_enemies(&game_vars->player, &game_vars->enemies, &game_fn->enemy_fn);

			game_fn->enemy_fn.update(&game_vars->enemies);
		}
		break;

		case MENU: {
			_draw_scene_on_texture(game_fn, game_vars);

			BeginTextureMode(game_vars->screen_texture);

			Vector2 center = screen_center_point();
			const char* text = "Teste";
			const int text_font = 32;
			size_t text_padding = MeasureText(text, text_font) >> 1;
			DrawText(text, center.x - text_padding, center.y, text_font, RAYWHITE);

			EndTextureMode();

			_draw_scene_on_screen(game_fn, game_vars);
		}
		break;

		case DEAD:
		default:
			break;
	}
}

void _draw_scene_on_texture(const GameFunctions *game_fn, const GameVars *game_vars)
{
	BeginTextureMode(game_vars->screen_texture);

	ClearBackground(BLACK);

	game_fn->fuel_fn.draw(&game_vars->container);
	game_fn->player_fn.draw_game(game_vars->player);
	game_fn->enemy_fn.draw_arr(&game_vars->enemies);

	EndTextureMode();
}

void _draw_scene_on_screen(const GameFunctions *game_fn, const GameVars *game_vars)
{
	float screen_width = game_vars->screen_texture.texture.width;
	float screen_height = -game_vars->screen_texture.texture.height;
	BeginDrawing();

	DrawTexturePro(
		game_vars->screen_texture.texture,
		CLITERAL(Rectangle){ .x = 0, .y = 0, .width = screen_width, .height = screen_height },
		CLITERAL(Rectangle){ .x = 0, .y = 0, .width = GetScreenWidth(), .height = GetScreenHeight() },
		CLITERAL(Vector2){ 0, 0 },
		0,
		WHITE
	);

	EndDrawing();

}

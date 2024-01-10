#include "raylib.h"

#include "types.h"
#include "constants.h"

void collision_check_player(Ship *player, Fuel_Container *container, const Fuel_Functions *fuel_func)
{
	const Rectangle player_rec = {
		.x = player->pos.x,
		.y = player->pos.y,
		.width = player->size.x,
		.height = player->size.y,
	};

	Rectangle other_rec = {
		.x = 0, .y = 0,
		.width = fuel_size.x,
		.height = fuel_size.y,
	};

	for (size_t i = 0; i < container->size; i++) {
		other_rec.x = container->fuel[i].pos.x;
		other_rec.y = container->fuel[i].pos.y;

		if (CheckCollisionRecs(player_rec, other_rec)) {
			fuel_func->destroy(container, i);
		}
	}
}

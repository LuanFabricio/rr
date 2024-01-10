#include <raylib.h>

#include "constants.h"
#define UTILS_IMPLEMENTATION
#define RANDOM_UTILS
#include "utils.h"
#include "types.h"

#define MIN_SPAWN_FUEL 15.f
#define MAX_SPAWN_FUEL 3500.f
#define FUEL_COLOR RED

void fuel_spawn(Fuel_Container *container)
{
	if (container->size >= CONTAINER_CAPACITY) {
		return;
	}

	Vector2 pos = random_game_point();
	float fuel = random_float() * MAX_SPAWN_FUEL + MIN_SPAWN_FUEL;

	container->fuel[container->size] = CLITERAL(Fuel) {
		.pos = pos,
		.content = fuel,
	};

	container->size += 1;
}

void fuel_draw(const Fuel_Container *container)
{
	for (size_t i = 0; i < container->size; i++) {
		DrawRectangleV(container->fuel[i].pos, fuel_size, FUEL_COLOR);
	}
}

void fuel_destroy(Fuel_Container *container, size_t index)
{
	if (container->size <= index || container->size == 0) {
		return;
	}

	container->size -= 1;
	if (container->size > 0) {
		container->fuel[index] = container->fuel[container->size];
	}
}

#ifndef __FUEL_H
#define __FUEL_H

#include <stdlib.h>
#include "raylib.h"

typedef struct {
	Vector2 pos;
	float content;
} Fuel;

#define CONTAINER_CAPACITY 255

typedef struct {
	Fuel fuel[CONTAINER_CAPACITY];
	size_t size;
} Fuel_Container;

#ifndef DEBUG

void fuel_spawn(Fuel_Container *container);
void fuel_destroy(Fuel_Container *container, size_t index);
void fuel_draw(const Fuel_Container* container);

#else

#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

#define RR_FUEL static

CREATE_FUNCTION_PTR(RR_FUEL, fuel_spawn, (Fuel_Container *), void);
CREATE_FUNCTION_PTR(RR_FUEL, fuel_draw, (Fuel_Container *), void);
CREATE_FUNCTION_PTR(RR_FUEL, fuel_destroy, (Fuel_Container*, size_t), void);

static void *fuel_shared_ptr = NULL;
RR_FUEL void reset_fuel_function()
{
	const char* file_path =  "build/objs/fuel.so";

	fuel_shared_ptr = hr_reset_file(file_path, fuel_shared_ptr);

	fuel_spawn = (fuel_spawn_t)hr_reset_function(fuel_shared_ptr, "fuel_spawn");
	fuel_draw = (fuel_draw_t)hr_reset_function(fuel_shared_ptr, "fuel_draw");
	fuel_destroy = (fuel_destroy_t)hr_reset_function(fuel_shared_ptr, "fuel_destroy");
}

#endif // DEBUG

#endif // __FUEL_H

#ifndef __FUEL_H
#define __FUEL_H

#include <stdlib.h>
#include "raylib.h"
#include "../types.h"

#ifndef DEBUG

void fuel_spawn(Fuel_Container *container);
void fuel_destroy(Fuel_Container *container, size_t index);
void fuel_draw(const Fuel_Container* container);

static Fuel_Functions fuel_functions = {
	.spawn = fuel_spawn,
	.draw = fuel_draw,
	.destroy = fuel_destroy,
};

#else
#ifndef __FUEL_IMPLEMENTATION
#define __FUEL_IMPLEMENTATION

#define __HOTRELOAD_IMPLEMENTATION
#include "../../hotreload.h"

#define RR_FUEL static

static Fuel_Functions fuel_functions = {
	.spawn = NULL,
	.draw = NULL,
	.destroy = NULL,
};

static void *fuel_shared_ptr = NULL;
RR_FUEL void reset_fuel_function()
{
	const char* file_path =  "build/objs/fuel.so";

	fuel_shared_ptr = hr_reset_file(file_path, fuel_shared_ptr);

	fuel_functions.spawn = (fuel_spawn_t)hr_reset_function(fuel_shared_ptr, "fuel_spawn");
	fuel_functions.draw = (fuel_draw_t)hr_reset_function(fuel_shared_ptr, "fuel_draw");
	fuel_functions.destroy = (fuel_destroy_t)hr_reset_function(fuel_shared_ptr, "fuel_destroy");
}

#endif // __FUEL_IMPLEMENTATION
#endif // DEBUG

#endif // __FUEL_H

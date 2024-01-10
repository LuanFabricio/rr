#ifndef __FUEL_H
#define __FUEL_H

#include <stdlib.h>
#include "raylib.h"
#include "types.h"

#include "utils.h"
CREATE_FUNCTION_TYPE(fuel_spawn, (Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_draw, (Fuel_Container *), void);
CREATE_FUNCTION_TYPE(fuel_destroy, (Fuel_Container*, size_t), void);

#ifndef DEBUG

void fuel_spawn(Fuel_Container *container);
void fuel_destroy(Fuel_Container *container, size_t index);
void fuel_draw(const Fuel_Container* container);

#else
#ifndef __FUEL_IMPLEMENTATION
#define __FUEL_IMPLEMENTATION

#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"

#define RR_FUEL static

CREATE_FUNCTION_PTR(RR_FUEL, fuel_spawn);
CREATE_FUNCTION_PTR(RR_FUEL, fuel_draw);
CREATE_FUNCTION_PTR(RR_FUEL, fuel_destroy);

static void *fuel_shared_ptr = NULL;
RR_FUEL void reset_fuel_function()
{
	const char* file_path =  "build/objs/fuel.so";

	fuel_shared_ptr = hr_reset_file(file_path, fuel_shared_ptr);

	fuel_spawn = (fuel_spawn_t)hr_reset_function(fuel_shared_ptr, "fuel_spawn");
	fuel_draw = (fuel_draw_t)hr_reset_function(fuel_shared_ptr, "fuel_draw");
	fuel_destroy = (fuel_destroy_t)hr_reset_function(fuel_shared_ptr, "fuel_destroy");
}

#endif // __FUEL_IMPLEMENTATION
#endif // DEBUG

#endif // __FUEL_H

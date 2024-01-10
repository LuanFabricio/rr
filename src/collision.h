#ifndef __COLLISION_H
#define __COLLISION_H

#include "types.h"

#define RR_COLLISION static

#ifdef DEBUG
#define __HOTRELOAD_IMPLEMENTATION
#include "../hotreload.h"
#include "utils.h"

CREATE_FUNCTION_TYPE(collision_check_player, (Ship *player, Fuel_Container *container), void);
CREATE_FUNCTION_PTR(RR_COLLISION, collision_check_player);

void *collision_shared_ptr = NULL;

void reset_collision_function()
{
	const char* file_path =  "build/objs/collision.so";
	collision_shared_ptr = hr_reset_file(file_path, collision_shared_ptr);
	collision_check_player = (collision_check_player_t)hr_reset_function(collision_shared_ptr, "collision_check_player");
}
#else
void collision_check_player(Ship *player, Fuel_Container *container);
#endif // DEBUG

#endif // __COLLISION_H

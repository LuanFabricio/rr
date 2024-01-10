#ifndef __TYPES_H
#define __TYPES_H

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

typedef struct {
	Vector2 pos, size;
	float fuel;
} Ship;

#endif // __TYPES_H

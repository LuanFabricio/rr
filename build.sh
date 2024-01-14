#!/bin/bash

mkdir -p build
mkdir -p build/objs

CC=gcc
CFLAGS="-Wall -Wextra -g"
CLINKS="-lm -lraylib"

set -xe

if [[ $1 == "release" ]]; then
	$CC $CFLAGS -c -o build/objs/player.o src/player.c  $CLINKS
	$CC $CFLAGS -c -o build/objs/fuel.o src/fuel.c $CLINKS
	$CC $CFLAGS -c -o build/objs/collision.o src/collision.c $CLINKS
	$CC $CFLAGS -c -o build/objs/enemy.o src/enemy.c $CLINKS

	OBJS="build/objs/player.o build/objs/fuel.o build/objs/collision.o"
	$CC $CFLAGS -o build/main main.c $OBJS $CLINKS
else
	$CC $CFLAGS -g -fPIC -shared -o build/objs/player.so src/player.c $CLINKS -D DEBUG &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/fuel.so src/fuel.c $CLINKS -D DEBUG &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/collision.so src/collision.c -D DEBUG $CLINKS &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/enemy.so src/enemy.c -D DEBUG $CLINKS &

	$CC $CFLAGS -o build/main main.c $CLINKS -D DEBUG
fi

#!/bin/bash

mkdir -p build
mkdir -p build/objs

CC=gcc
CFLAGS="-Wall -Wextra -g"
CLINKS="-lm -lraylib"

set -xe

if [[ $1 == "release" ]]; then
	$CC $CFLAGS -c -o build/objs/player.o src/player/player.c  $CLINKS
	$CC $CFLAGS -c -o build/objs/fuel.o src/fuel/fuel.c $CLINKS
	$CC $CFLAGS -c -o build/objs/collision.o src/collision/collision.c $CLINKS
	$CC $CFLAGS -c -o build/objs/enemy.o src/enemy/enemy.c $CLINKS
	$CC $CFLAGS -c -o build/objs/game_state.o src/game_state/game_state.c $CLINKS

	OBJS="build/objs/player.o build/objs/fuel.o"
	OBJS=$OBJS" build/objs/enemy.o"
	OBJS=$OBJS" build/objs/collision.o build/objs/game_state.o"

	$CC $CFLAGS -o build/main main.c $OBJS $CLINKS
else
	$CC $CFLAGS -g -fPIC -shared -o build/objs/player.so src/player/player.c $CLINKS -D DEBUG &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/fuel.so src/fuel/fuel.c $CLINKS -D DEBUG &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/collision.so src/collision/collision.c -D DEBUG $CLINKS &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/enemy.so src/enemy/enemy.c -D DEBUG $CLINKS &
	$CC $CFLAGS -g -fPIC -shared -o build/objs/game_state.so src/game_state/game_state.c -D DEBUG $CLINKS &

	$CC $CFLAGS -o build/main main.c $CLINKS -D DEBUG
fi

#!/bin/bash

mkdir -p build
mkdir -p build/objs

CC=gcc
CFLAGS="-Wall -Wextra -g"
CLINKS="-lm -lraylib"

set -xe

if [[ $1 == "release" ]]; then
	$CC $CFLAGS -c -o build/objs/game.o src/player.c  $CLINKS
	$CC $CFLAGS -c -o build/objs/fuel.o src/fuel.c $CLINKS

	OBJS="build/objs/player.o build/objs/fuel.o"
	$CC $CFLAGS -o build/main main.c $OBJS $CLINKS
else
	$CC -g -fPIC -shared -o build/objs/player.so src/player.c $CLINKS -D DEBUG &
	$CC -g -fPIC -shared -o build/objs/fuel.so src/fuel.c $CLINKS -D DEBUG &
	$CC $CFLAGS -o build/main main.c $CLINKS -D DEBUG
fi

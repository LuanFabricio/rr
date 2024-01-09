#!/bin/bash

CC=gcc
CFLAGS="-Wall -Wextra"
CLINKS="-lm -lraylib"

set -xe

if [[ $1 == "release" ]]; then
	$CC $CFLAGS -c -o build/objs/player.o src/player.c $CLINKS
	$CC $CFLAGS -o build/main main.c build/objs/player.o $CLINKS
else
	$CC $CFLAGS -fPIC -shared -o build/objs/player.so src/player.c $CLINKS &
	$CC $CFLAGS -o build/main main.c $CLINKS -D DEBUG
fi

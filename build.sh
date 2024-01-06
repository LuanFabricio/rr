#!/bin/bash

CC=gcc
CFLAGS="-Wall -Wextra"
CLINKS="-lm -lraylib"

set -xe
$CC $CFLAGS -fPIC -shared -o build/objs/player.so player.c $CLINKS

if [[ $1 != "debug" ]]; then
	$CC $CFLAGS -o build/main main.c $CLINKS
fi

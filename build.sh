#!/usr/bin/sh

# set -xe

NAME='a.out'
LIBS='-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf'

gcc sauce/*.c nara/*.c -I nara $LIBS -o $NAME

[ -f $NAME ] && ./$NAME


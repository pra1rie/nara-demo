#!/usr/bin/sh

# set -xe

NAME='a.out'
LIBS='-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf'

# lmao
cd nara
./build.sh
cd ..

gcc sauce/*.c -I nara/include -Lnara -lnara $LIBS -o $NAME

[ -f $NAME ] && ./$NAME


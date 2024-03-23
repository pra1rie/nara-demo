#!/usr/bin/bash

NARA="../nara/"
LIBS="-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf"

gcc sauce/*.c $NARA/*.c -I$NARA $LIBS

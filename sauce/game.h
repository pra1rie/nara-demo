#pragma once
#include <SDL2/SDL.h>
#include "nara.h"

#define TILESIZE 32
#define ZOOM 4

struct demo_game {
	Window window;
	SDL_Texture *texture;
	Font gui_font;
	char gui_text[255];
	bool running;
};

extern struct demo_game game;

void start_game();
void update_game();


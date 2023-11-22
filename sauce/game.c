#include "game.h"
#include "nara.h"

#include <SDL2/SDL.h>

#define TILESIZE 32
#define ZOOM 3

static struct {
	Sprite sprite;
	SDL_Rect rect;
	SDL_Rect rect_copy;
	int speed;
	
	enum {
		PLAYER_IDLE,
		PLAYER_WALK,
		NUM_PLAYER_STATES,
	} state;
	SpriteRange range[NUM_PLAYER_STATES];
} player;

static struct {
	Font font;
	char dope_text[100];
} gui;

static void
init_gui()
{
	SDL_Color color = {240, 240, 240, 255};
	gui.font = fontNew("data/hack.ttf", 24, color);
}

static void
update_gui()
{
	sprintf(gui.dope_text, " {%d, %d} ",
			player.rect.x, player.rect.y);
	SDL_SetRenderDrawColor(global.render, 24, 24, 36, 255);
	fontWrite(&gui.font, gui.dope_text, 0, 0);
}

static void
init_player()
{
	player.sprite = spriteNew("data/player.png", TILESIZE, TILESIZE);
	player.range[PLAYER_IDLE] = (SpriteRange) {0, 1, 36, 0};
	player.range[PLAYER_WALK] = (SpriteRange) {2, 6, 6, 0};
	player.state = PLAYER_IDLE;

	// bruh.
	int pos_x = (global.width  / 2 / ZOOM - (TILESIZE / 2));
	int pos_y = (global.height / 2 / ZOOM - (TILESIZE / 2));

	player.rect = (SDL_Rect) {pos_x, pos_y, TILESIZE, TILESIZE};
	player.rect_copy = player.rect;
	player.speed = 2;
}

static void
update_player()
{
	player.rect_copy = player.rect;
	player.state = PLAYER_IDLE;

	if (getKey(SDL_SCANCODE_LEFT)) {
		player.rect.x -= player.speed;
		player.sprite.flip = SDL_FLIP_HORIZONTAL;
	}
	if (getKey(SDL_SCANCODE_RIGHT)) {
		player.rect.x += player.speed;
		player.sprite.flip = SDL_FLIP_NONE;
	}
	if (getKey(SDL_SCANCODE_UP)) {
		player.rect.y -= player.speed;
	}
	if (getKey(SDL_SCANCODE_DOWN)) {
		player.rect.y += player.speed;
	}

	if (player.rect_copy.x != player.rect.x ||
			player.rect_copy.y != player.rect.y) {
		player.state = PLAYER_WALK;
	}

	spriteAnimate(&player.sprite, &player.range[player.state]);

	SDL_Rect rect = (SDL_Rect) {
		player.rect.x * ZOOM,
		player.rect.y * ZOOM,
		player.rect.w * ZOOM,
		player.rect.h * ZOOM,
	};
	
	spriteRender(&player.sprite, &rect);
}

void
update_game()
{
	SDL_SetRenderDrawColor(global.render, 90, 60, 78, 0);
	SDL_RenderClear(global.render);
	update_player();
	update_gui();
}

void
start_game()
{
	init_player();
	init_gui();
}


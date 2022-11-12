#include "game.h"
#include "nara.h"

#include <SDL2/SDL.h>

#define wn global.window
#define rn global.window.render
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
	fontWrite(&gui.font, "Sample Text", 24, 24);
}

static void
init_player()
{
	player.sprite = spriteNew("data/player.png");
	player.speed = 6;
	player.rect = (SDL_Rect) {120, 120, global.tileWidth, global.tileHeight};
	player.rect_copy = player.rect;

	player.range[PLAYER_IDLE] = (SpriteRange) {0, 1, 36, 0};
	player.range[PLAYER_WALK] = (SpriteRange) {2, 6, 6, 0};

	player.state = PLAYER_IDLE;
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
		player.rect.x, // * ZOOM,
		player.rect.y, // * ZOOM,
		player.rect.w * ZOOM,
		player.rect.h * ZOOM,
	};
	
	spriteRender(&player.sprite, &rect);
}

void
update_game()
{
	SDL_SetRenderDrawColor(rn, 90, 60, 78, 0);
	SDL_RenderClear(rn);
	update_player();
	update_gui();
}

void
start_game()
{
	init_player();
	init_gui();
}


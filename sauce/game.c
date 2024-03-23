#include "game.h"
#include "nara.h"

#include <SDL2/SDL.h>

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

static void
update_gui()
{
	sprintf(game.gui_text, " {%d, %d} ", player.rect.x, player.rect.y);

	SDL_Rect rect = { 0, 0, 200, game.gui_font.size + 6 };

	SDL_SetRenderDrawColor(game.window.render, 24, 24, 36, 255);
	SDL_RenderFillRect(game.window.render, &rect);
	fontWrite(&game.gui_font, game.window.render, game.gui_text, 0, 0);
}

static void
init_player()
{
	player.sprite = spriteNew("./data/player.png", TILESIZE, TILESIZE);
	player.range[PLAYER_IDLE] = (SpriteRange) { 0, 1, 36, 0 };
	player.range[PLAYER_WALK] = (SpriteRange) { 2, 6, 6, 0 };
	player.state = PLAYER_IDLE;

	// bruh.
	int pos_x = (game.window.width  / ZOOM / 2 - (TILESIZE / 2));
	int pos_y = (game.window.height / ZOOM / 2 - (TILESIZE / 2));

	player.rect = (SDL_Rect) {pos_x, pos_y, TILESIZE, TILESIZE};
	player.rect_copy = player.rect;
	player.speed = 2;
}

static void
update_player()
{
	player.rect_copy = player.rect;
	player.state = PLAYER_IDLE;

	const char *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT]) {
		player.rect.x -= player.speed;
		player.sprite.flip = SDL_FLIP_HORIZONTAL;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		player.rect.x += player.speed;
		player.sprite.flip = SDL_FLIP_NONE;
	}
	if (state[SDL_SCANCODE_UP]) {
		player.rect.y -= player.speed;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		player.rect.y += player.speed;
	}

	if (player.rect_copy.x != player.rect.x ||
			player.rect_copy.y != player.rect.y) {
		player.state = PLAYER_WALK;
	}

	spriteAnimate(&player.sprite, &player.range[player.state]);
	spriteRender(&player.sprite, game.window.render, &player.rect);
}

void
update_game()
{
	SDL_SetRenderTarget(game.window.render, game.texture);

	SDL_SetRenderDrawColor(game.window.render, 90, 60, 78, 255);
	SDL_RenderClear(game.window.render);
	update_player();

	SDL_SetRenderTarget(game.window.render, NULL);
	SDL_RenderCopy(game.window.render, game.texture, NULL, NULL);
	update_gui();
}

void
start_game()
{
	game.running = true;
	SDL_Color col = {240, 240, 240, 255};
	game.gui_font = fontNew("./data/hack.ttf", 24, col);

	game.texture = SDL_CreateTexture(game.window.render,
			SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
			game.window.width / ZOOM, game.window.height / ZOOM);

	init_player();
}


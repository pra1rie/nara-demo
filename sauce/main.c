#include "game.h"
#include "nara.h"


static void
update()
{
	SDL_Delay(12);
	update_game();
	SDL_RenderPresent(game.window.render);
}

int
main(void)
{
	initNara();

	game.window = windowNew("Odio Salim.", 900, 540, true);
	start_game();

	SDL_Event e;
	while (game.running) {
		if (SDL_PollEvent(&e)) {
			game.running = windowEvents(&game.window, e);
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				game.running = false;
			// fucking hell
			if (e.type == SDL_WINDOWEVENT
					&& e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_DestroyTexture(game.texture);
				game.texture = SDL_CreateTexture(game.window.render,
					SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,
					game.window.width / ZOOM, game.window.height / ZOOM);
			}
		}
		update();
	}

	SDL_DestroyTexture(game.texture);
	windowFree(&game.window);
	exitNara();
	return 0;
}

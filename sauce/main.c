#include "game.h"
#include "nara.h"

static void
events(SDL_Event e)
{
	switch (e.type) {
	case SDL_QUIT:
		global.isRunning = false;
		break;
	case SDL_WINDOWEVENT: {
		if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
			global.window.width = e.window.data1;
			global.window.height = e.window.data2;
		}
	} break;
	default: break;
	}
}

// TODO: render / update separately
static void
update()
{
	SDL_Delay(12);
	update_game();
	SDL_RenderPresent(global.window.render);
}

int
main(void)
{
	init();
	global.window = windowNew("Odio Salim.", 900, 540, true);
	start_game();

	while (global.isRunning) {
		SDL_Event e;
		if (SDL_PollEvent(&e))
			events(e);
		update();
	}

	windowFree(&global.window);
	quit();
	return 0;
}

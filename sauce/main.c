#include "game.h"
#include "nara.h"


static void
update()
{
	SDL_Delay(12);
	update_game();
	SDL_RenderPresent(global.window->render);
}

int
main(void)
{
	initNara();
	global.window = windowNew("Odio Salim.", 900, 540, true);
	start_game();

	SDL_Event e;
	while (global.isRunning) {
		// tired of checking the same events lul
		if (SDL_PollEvent(&e)) {
			genericEvents(e);
		}
		update();
	}

	windowFree(global.window);
	exitNara();
	return 0;
}

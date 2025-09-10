#include "core/game.h"
#include "platform/sdl/sdlcontext.h"

int main(int argc, char* argv[])
{
	SDLContext sdlContext; // don't know where to put this

	Game* game = new Game();

	game->init();

	while (!game->exitRequested())
	{
		game->tick();
	}

	delete game;

	return 0;
}
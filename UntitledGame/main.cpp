#include "core/game.h"

#include "platform/sdl/sdlplatform.h"

int main(int argc, char* argv[])
{
	Platform* platform = new SDLPlatform;
	Game* game = new Game(platform);

	game->init();

	while (!game->exitRequested())
	{
		game->tick();
	}

	delete game;
	delete platform;

	return 0;
}
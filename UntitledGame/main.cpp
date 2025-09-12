#include "core/game.h"

#include "platform/sdl/sdlplatform.h"

#include <SDL.h>

#include <print>

int main(int argc, char* argv[])
{
	Platform* platform = new SDLPlatform;
	Game* game = new Game(platform);

	game->init();

	const double fixedDeltaTime = 1.0 / 60.0;
	double accumulator = 0.0;
	double lastFrame = SDL_GetTicks() / 1000.0f;

	while (!game->exitRequested())
	{
		double currentFrame = SDL_GetTicks() / 1000.0f;
		double deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (deltaTime > 0.25)
			deltaTime = 0.25;

		accumulator += deltaTime;

		while (accumulator >= fixedDeltaTime)
		{
			game->tick(fixedDeltaTime);
			accumulator -= fixedDeltaTime;
		}

		double alpha = accumulator / fixedDeltaTime;
		game->render(alpha);
	}

	delete game;
	delete platform;

	return 0;
}
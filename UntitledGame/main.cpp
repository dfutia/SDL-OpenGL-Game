#include "core/game.h"

#include "platform/sdl/sdlcontext.h"
#include "platform/sdl/sdlwindow.h"
#include "platform/sdl/sdlinput.h"

#include "platform/gl/glrenderer.h"

int main(int argc, char* argv[])
{
	SDLContext sdl;
	Window* window = new SDLWindow;
	Input* input = new SDLInput;
	Renderer* renderer = new GLRenderer(window);
	Game* game = new Game;

	while (!input->exitRequested())
	{
		input->pollInput();
		game->tick();
		renderer->beginFrame();
		renderer->endFrame();
	}

	delete window;
	delete input;
	delete renderer;
	delete game;

	return 0;
}
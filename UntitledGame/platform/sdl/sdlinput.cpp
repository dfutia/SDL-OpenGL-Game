#include "platform/sdl/sdlinput.h"

#include <SDL.h>

bool SDLInput::exitRequested()
{
	return mExitRequested;
}

void SDLInput::pollInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mExitRequested = true;
			break;
		}
	}
}
#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

#include <SDL.h>

class SDLContext
{
public:
	SDLContext()
	{
		SDL_Init(SDL_INIT_VIDEO);
	}

	~SDLContext()
	{
		SDL_Quit();
	}
};

#endif // SDL_CONTEXT_H
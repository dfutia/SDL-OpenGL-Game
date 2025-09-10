#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "core/input.h"

class SDLInput : public Input
{
public:
	bool exitRequested() override;
	void pollInput() override;
private:
	bool mExitRequested = false;
};

#endif // SDL_INPUT_H
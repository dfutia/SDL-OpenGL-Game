#ifndef SDL_PLATFORM_H
#define SDL_PLATFORM_H

#include "core/platform.h"

class Window;
class Input;

class SDLPlatform : public Platform
{
public:
	SDLPlatform();
	~SDLPlatform();
private:
	Window* mWindow;
	Input* mInput;
};

#endif // SDL_PLATFORM_H
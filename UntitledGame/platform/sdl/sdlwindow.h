#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "core/window.h"

#include <SDL.h>

class SDLWindow : public Window
{
public:
	SDLWindow();
	~SDLWindow();

	void* getNativeWindow() override { return mWindow; }
	void swapBuffers() override { SDL_GL_SwapWindow(mWindow); }
private:
	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

#endif // SDL_WINDOW_H
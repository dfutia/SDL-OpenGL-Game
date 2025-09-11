#include "platform/sdl/sdlwindow.h"
#include "core/services.h"

SDLWindow::SDLWindow()
{
	Services::registerService<Window>("Window", this);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow
	(
		"Application",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	mContext = SDL_GL_CreateContext(mWindow);

	SDL_GL_SetSwapInterval(0); // 1 enable | 0 disable 
}

SDLWindow::~SDLWindow()
{
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}
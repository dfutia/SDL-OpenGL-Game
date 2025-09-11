#include "platform/sdl/sdlinput.h"

#include "core/services.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

SDLInput::SDLInput()
{
	Services::registerService<Input>("Input", this);
	mKeyboard = new SDLKeyboard();
	mMouse = new SDLMouse();
}

bool SDLInput::exitRequested()
{
	return mExitRequested;
}

void SDLInput::pollInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			mExitRequested = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				mExitRequested = true;
			break;
		}
	}

	mKeyboard->update();
	mMouse->update();
}
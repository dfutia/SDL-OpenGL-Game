#include "platform/sdl/sdlinput.h"

#include <SDL.h>

SDLMouse::SDLMouse()
{
	int x, y;
	mCurrButtons = SDL_GetMouseState(&x, &y);
	mPrevButtons = mCurrButtons;
	mCurrPos = glm::vec2(x, y);
	mPrevPos = mCurrPos;
	mDelta = glm::vec2(0, 0);
	mScrollDelta = 0.0f;
}

bool SDLMouse::isButtonDown(MouseButton button)
{
	return (mCurrButtons & SDL_BUTTON(static_cast<int>(button))) != 0;
}

bool SDLMouse::isButtonPressed(MouseButton button)
{
	int buttonFlag = SDL_BUTTON(static_cast<int>(button));
	return !(mPrevButtons & buttonFlag) && (mCurrButtons & buttonFlag);
}

bool SDLMouse::isButtonReleased(MouseButton button)
{
	int buttonFlag = SDL_BUTTON(static_cast<int>(button));
	return (mPrevButtons & buttonFlag) && !(mCurrButtons & buttonFlag);
}

void SDLMouse::setCursorMode(CursorMode mode)
{
	if (mode == CursorMode::Normal)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
	}
	else if (mode == CursorMode::Locked)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(SDL_DISABLE);

		// swallow the first delta
		int x, y;
		SDL_GetRelativeMouseState(&x, &y);
	}
}

glm::vec2 SDLMouse::getMousePosition()
{
	return mCurrPos;
}

glm::vec2 SDLMouse::getMouseDelta()
{
	return mDelta;
}

float SDLMouse::getScrollDelta()
{
	return mScrollDelta;
}

void SDLMouse::update()
{
    mPrevButtons = mCurrButtons;
    mDelta = glm::vec2(0, 0);
    mScrollDelta = 0.0f;

    if (SDL_GetRelativeMouseMode()) {
        int dx, dy;
        mCurrButtons = SDL_GetRelativeMouseState(&dx, &dy);
        mDelta = glm::vec2(dx, dy);
    }
    else {
        mPrevPos = mCurrPos;
        int x, y;
        mCurrButtons = SDL_GetMouseState(&x, &y);
        mCurrPos = glm::vec2(x, y);
        mDelta = mCurrPos - mPrevPos;
    }
}
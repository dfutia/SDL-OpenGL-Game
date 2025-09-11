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
	mPrevPos = mCurrPos;
	mDelta = glm::vec2(0, 0);
	mScrollDelta = 0.0f;

	int x, y;
	mCurrButtons = SDL_GetMouseState(&x, &y);
	mCurrPos = glm::vec2(x, y);
	mDelta = mCurrPos - mPrevPos;
}
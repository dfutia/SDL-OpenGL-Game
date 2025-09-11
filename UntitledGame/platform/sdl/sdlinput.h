#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "core/input.h"

#include <SDL.h>

#include <unordered_map>
#include <vector>

class SDLKeyboard : public Keyboard
{
public:
	SDLKeyboard();
	~SDLKeyboard() = default;

	bool isKeyDown(Key  key) override;
	bool isKeyPressed(Key  key) override;
	bool isKeyReleased(Key  key) override;

	void update() override;
private:
	std::vector<Uint8> mPrevKeys;
	std::vector<Uint8> mCurrKeys;
	int mNumKeys = 0;

	SDL_Scancode keyToSDLScancode(Key key) const;
	void initKeyMappings();
	std::unordered_map<Key, SDL_Scancode> mKeyMapping;
};

class SDLMouse : public Mouse
{
public:
	SDLMouse();
	~SDLMouse() = default;

	bool isButtonDown(MouseButton button) override;
	bool isButtonPressed(MouseButton button) override;
	bool isButtonReleased(MouseButton button) override;

	glm::vec2 getMousePosition() override;
	glm::vec2 getMouseDelta() override;
	float getScrollDelta() override;

	void update() override;
private:
	Uint32 mPrevButtons = 0;
	Uint32 mCurrButtons = 0;
	glm::vec2 mPrevPos{ 0, 0 };
	glm::vec2 mCurrPos{ 0, 0 };
	glm::vec2 mDelta{ 0, 0 };
	float mScrollDelta = 0.0f;
};

class SDLInput : public Input
{
public:
	SDLInput();
	~SDLInput() = default;

	bool exitRequested() override;
	void pollInput() override;

	Keyboard* getKeyboard() override { return mKeyboard; }
	Mouse* getMouse() override { return mMouse; }
private:
	bool mExitRequested = false;

	SDLKeyboard* mKeyboard;
	SDLMouse* mMouse;
};

#endif // SDL_INPUT_H
#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>

enum class Key
{
	// Alphanumeric keys
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	Key0, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9,

	// Arrow keys
	Up, Down, Left, Right,

	// Function keys
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

	// Special keys
	Space, Enter, Escape, Tab, Backspace, Delete,
	LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt,

	Unknown
};

enum class MouseButton
{
	Left = 1,
	Middle = 2,
	Right = 3,
	X1 = 4,
	X2 = 5
};

class InputDevice
{
public:
	InputDevice() = default;
	virtual ~InputDevice() = default;

	virtual void update() = 0;
};

class Keyboard : public InputDevice
{
public:
	Keyboard() = default;
	virtual ~Keyboard() = default;

	virtual bool isKeyDown(Key key) = 0;
	virtual bool isKeyPressed(Key key) = 0;
	virtual bool isKeyReleased(Key key) = 0;

	void update() override = 0;
private:
	unsigned int mCurrentFrame = 0;
};

class Mouse : public InputDevice
{
public:
	Mouse() = default;
	virtual ~Mouse() = default;

	virtual bool isButtonDown(MouseButton button) = 0;
	virtual bool isButtonPressed(MouseButton button) = 0;
	virtual bool isButtonReleased(MouseButton button) = 0;

	virtual glm::vec2 getMousePosition() = 0;
	virtual glm::vec2 getMouseDelta() = 0;
	virtual float getScrollDelta() = 0;

	void update() override = 0;
};

class Input
{
public:
	Input() = default;
	virtual ~Input() = default;

	virtual bool exitRequested() = 0;
	virtual void pollInput() = 0;

	virtual Keyboard* getKeyboard() = 0;
	virtual Mouse* getMouse() = 0;
};

#endif // INPUT_H
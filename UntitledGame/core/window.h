#ifndef PLATFORM_H
#define PLATFORM_H

class Window
{
public:
	Window() = default;
	virtual ~Window() = default;

	virtual void* getNativeWindow() = 0;
	virtual void swapBuffers() = 0;
private:
};

#endif // PLATFORM_H
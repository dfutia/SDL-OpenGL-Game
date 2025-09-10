#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include "renderer/renderer.h"

class Window;

class GLRenderer : public Renderer
{
public:
	GLRenderer(Window* window);
	~GLRenderer() = default;

	void beginFrame() override;
	void endFrame() override;
private:
	Window* mWindow;
};

#endif // GL_RENDERER_H
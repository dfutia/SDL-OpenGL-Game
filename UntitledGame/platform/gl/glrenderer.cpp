#include "platform/gl/glrenderer.h"

#include "core/window.h"

#include <SDL.h>
#include <glad/glad.h>

GLRenderer::GLRenderer(Window* window) : mWindow(window)
{
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glEnable(GL_DEPTH_TEST);
}

void GLRenderer::beginFrame()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::endFrame()
{
	mWindow->swapBuffers();
}
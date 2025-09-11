#include "platform/gl/glrenderer.h"

#include "core/window.h"
#include "core/services.h"

#include <SDL.h>
#include <glad/glad.h>

VertexBuffer* GLRenderer::createVertexBuffer(const Vertex* data, unsigned int count)
{
	return new GLVertexBuffer(data, count);
}

IndexBuffer* GLRenderer::createIndexBuffer(const unsigned int* indices, unsigned int count)
{
	return new GLIndexBuffer(indices, count);
}

GLRenderer::GLRenderer(Window* window) : mWindow(window)
{
	Services::registerService<Renderer>("Renderer", this);

	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glEnable(GL_DEPTH_TEST);
}

GPUResource* GLRenderer::createVertexShader(const char* code)
{
	return new GLShader(GL_VERTEX_SHADER, code);
}

GPUResource* GLRenderer::createFragmentShader(const char* code)
{
	return new GLShader(GL_FRAGMENT_SHADER, code);
}

ShaderProgram* GLRenderer::createShaderProgram(GPUResource* vs, GPUResource* fs)
{
	return new GLProgram(static_cast<GLShader*>(vs), static_cast<GLShader*>(fs));
}

void GLRenderer::bindResource(GPUResource* resource)
{
	if (resource->getType() == SHADER_PROGRAM)
	{
		GLProgram* program = static_cast<GLProgram*>(resource);
		glUseProgram(program->getResourceID());
	}
	else if (resource->getType() == VERTEX_BUFFER)
	{
		GLVertexBuffer* vbo = static_cast<GLVertexBuffer*>(resource);
		glBindVertexArray(vbo->getVAO());
	}
	else if (resource->getType() == INDEX_BUFFER)
	{
		GLIndexBuffer* ibo = static_cast<GLIndexBuffer*>(resource);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->getResourceID());
	}
}

void GLRenderer::unbindResource(GPUResource* resource)
{
	if (resource->getType() == SHADER_PROGRAM)
	{
		glUseProgram(0);
	}
	else if (resource->getType() == VERTEX_BUFFER)
	{
		glBindVertexArray(0);
	}
	else if (resource->getType() == INDEX_BUFFER)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
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
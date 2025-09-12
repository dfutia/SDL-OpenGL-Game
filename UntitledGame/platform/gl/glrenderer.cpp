#include "platform/gl/glrenderer.h"

#include "core/window.h"
#include "core/services.h"

#include <SDL.h>
#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

GPUTexture* GLRenderer::createTexture(int width, int height, void* data)
{
	GLTexture* texture = new GLTexture(width, height, false);
	glBindTexture(GL_TEXTURE_2D, texture->getResourceID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

VertexBuffer* GLRenderer::createVertexBuffer(const Vertex* data, unsigned int count)
{
	return new GLVertexBuffer(data, count);
}

IndexBuffer* GLRenderer::createIndexBuffer(const unsigned int* indices, unsigned int count)
{
	return new GLIndexBuffer(indices, count);
}

GLRenderer::GLRenderer()
{
	Services::registerService<Renderer>("Renderer", this);

	mWindow = Services::getService<Window>("Window");

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

void GLRenderer::bindTexture(GPUTexture* texture, int index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	if (texture->isCubeMap())
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getResourceID());
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, texture->getResourceID());
	}
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

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void GLRenderer::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	static ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	mWindow->swapBuffers();
}
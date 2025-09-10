#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include "renderer/renderer.h"

#include <glad/glad.h>

class Window;

class GLIndexBuffer : public IndexBuffer
{
public:
	GLIndexBuffer() = default;
	~GLIndexBuffer() = default;
private:
	GLuint mVAO, mVBO;
	unsigned int mVertexCount;
};

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer() = default;
	~GLVertexBuffer() = default;
private:
	GLuint mBufferId;
	unsigned int mCount;
};

//class GLVertexArray : public VertexArray
//{
//};

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
#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include "renderer/renderer.h"

#include <glad/glad.h>

class Window;

class GLIndexBuffer : public IndexBuffer
{
public:
	GLIndexBuffer(const unsigned int* indices, unsigned int count);
	~GLIndexBuffer();

	unsigned int getResourceID() const override { return mBufferId; }
	ResourceType getType() const override { return INDEX_BUFFER; }

	unsigned int getIndexCount() const override { return mVertexCount; }
private:
	GLuint mBufferId;
	unsigned int mVertexCount;
};

class GLVertexBuffer : public VertexBuffer
{
public:
	GLVertexBuffer(const Vertex* data, unsigned int count);
	~GLVertexBuffer();

	unsigned int getResourceID() const override { return mVBO; }
	ResourceType getType() const override { return VERTEX_BUFFER; }

	void setData(const Vertex* vertices, unsigned int count) override;
	unsigned int getVertexCount() const override { return mVertexCount; }

	GLuint getVAO() const { return mVAO; }
private:
	GLuint mVAO;
	GLuint mVBO;
	unsigned int mVertexCount;
};

//class GLVertexArray : public VertexArray
//{
//};

class GLTexture : public GPUTexture
{
public:
	GLTexture(unsigned int width, unsigned int height, bool isCubeMap = false);
	~GLTexture();

	unsigned int getResourceID() const override { return mTextureId; }
	ResourceType getType() const override { return TEXTURE; }
	unsigned int getWidth() const override { return mWidth; }
	unsigned int getHeight() const override { return mHeight; }
	bool isCubeMap() const override { return mIsCubeMap; }
private:
	GLuint mTextureId;
	unsigned int mWidth;
	unsigned int mHeight;
	bool mIsCubeMap;
};

class GLShader : public GPUResource
{
public:
	GLShader(GLenum type, const char* code);
	~GLShader();

	unsigned int getResourceID() const override { return mShaderId; }
	ResourceType getType() const override { return SHADER; }
private:
	GLuint mShaderId;
};

class GLProgram : public ShaderProgram
{
public:
	GLProgram(GLShader* vertexShader, GLShader* fragmentShader);
	~GLProgram();

	unsigned int getResourceID() const override { return mProgramId; }
	ResourceType getType() const override { return SHADER_PROGRAM; }
private:
	GLuint mProgramId;
};

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	~GLRenderer() = default;

	GPUTexture* createTexture(int width, int height, void* data) override;
	//GPUTexture* createCubeMap(int width, int height, std::vector<void*> dataList) override;

	VertexBuffer* createVertexBuffer(const Vertex* data, unsigned int count) override;
	IndexBuffer* createIndexBuffer(const unsigned int* indices, unsigned int count) override;

	GPUResource* createVertexShader(const char* code) override;
	GPUResource* createFragmentShader(const char* code) override;
	ShaderProgram* createShaderProgram(GPUResource* vs, GPUResource* fs) override;

	void bindTexture(GPUTexture* texture, int index) override;

	void bindResource(GPUResource* resource) override;
	void unbindResource(GPUResource* resource) override;

	void beginFrame() override;
	void endFrame() override;
private:
	Window* mWindow;
};

#endif // GL_RENDERER_H
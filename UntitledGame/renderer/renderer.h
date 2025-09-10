#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position; 
	glm::vec3 normal; 
	glm::vec3 tangent; 
	glm::vec2 texCoord;		
};

class Resource
{
public:
	Resource() = default;
	virtual ~Resource() = default;
};

class IndexBuffer : public Resource
{
public:
	IndexBuffer() = default;
	virtual ~IndexBuffer() = default;
};

class VertexBuffer : public Resource
{
public:
	VertexBuffer() = default;
	virtual ~VertexBuffer() = default;
};

//class VertexArray : public Resource
//{
//public:
//	VertexArray() = default;
//	virtual ~VertexArray() = default;
//};

class Framebuffer : public Resource
{
public:
	Framebuffer() = default;
	virtual ~Framebuffer() = default;
};

class ShaderProgram : public Resource
{
};

class Shader : public Resource
{
};

class VertexShader : public Shader
{
};

class FragmentShader : public Shader
{
};

class Texture : public Resource
{
public:
	Texture() = default;
	virtual ~Texture() = default;
};

class Material : public Resource
{
public:
	Material() = default;
	virtual ~Material() = default;
};

class ResourceManager
{
public:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
};

class Renderer
{
public:
	Renderer() = default;
	virtual ~Renderer() = default;



	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;
private:
};

#endif // RENDERER_H
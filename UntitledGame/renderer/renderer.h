#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>

#include <vector>
#include <string>

enum ResourceType
{
	INVALID,
	TEXTURE,
	SHADER,
	SHADER_PROGRAM,
	VERTEX_BUFFER,
	INDEX_BUFFER,
};

struct Vertex
{
	glm::vec3 position; 
	glm::vec3 normal; 
	glm::vec3 tangent; 
	glm::vec2 texCoord;		
};

// Base class for all CPU resources
class Resource
{
public:
	Resource(const std::string& name, const std::string& path) : mName(name), mFilePath(path) 
	{}

	Resource(const std::string& name) : mName(name), mFilePath("") 
	{}

	virtual ~Resource() = default;

	const std::string& getName() const { return mName; }
protected:
	std::string mName;
	std::string mFilePath;
};

// Base class for all GPU resources	
class GPUResource
{
public:
	GPUResource() = default;
	virtual ~GPUResource() = default;

	virtual unsigned int getResourceID() const = 0;
	virtual ResourceType getType() const = 0;
};

class IndexBuffer : public GPUResource
{
public:
	IndexBuffer() = default;
	virtual ~IndexBuffer() = default;

	ResourceType getType() const override { return INDEX_BUFFER; }

	virtual unsigned int getIndexCount() const = 0;
};

class VertexBuffer : public GPUResource
{
public:
	VertexBuffer() = default;
	virtual ~VertexBuffer() = default;

	ResourceType getType() const override { return VERTEX_BUFFER; }

	virtual void setData(const Vertex* vertices, unsigned int count) = 0;
	virtual unsigned int getVertexCount() const = 0;
};

//class VertexArray : public Resource
//{
//public:
//	VertexArray() = default;
//	virtual ~VertexArray() = default;
//};

//class Framebuffer : public Resource
//{
//public:
//	Framebuffer() = default;
//	virtual ~Framebuffer() = default;
//};

class Shader : public Resource
{
public:
	Shader(const std::string& path) : Resource(path) {}
};

class VertexShader : public Shader
{
public:
	VertexShader(const std::string& path) : Shader(path) {}
};

class FragmentShader : public Shader
{
public:
	FragmentShader(const std::string& path) : Shader(path) {}
};

class ShaderProgram : public GPUResource
{
public:
	ShaderProgram() = default;
	virtual ~ShaderProgram() = default;

	ResourceType getType() const override { return SHADER_PROGRAM; }
};

//class Texture : public Resource
//{
//public:
//	Texture() = default;
//	virtual ~Texture() = default;
//};

//class Material : public Resource
//{
//public:
//	Material() = default;
//	virtual ~Material() = default;
//};

class ResourceManager
{
public:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	//Material* createMaterial() { return nullptr; }
	//Mesh* createMesh() { return nullptr; }

	ShaderProgram* loadShaders(const char* vertexPath, const char* fragmentPath);
	//Texture* loadTexture(const char* texturePath);
	//Mesh* loadMesh(const char* meshPath);
private:
	std::vector<Resource*> mResources;
};

class Renderer
{
public:
	Renderer() = default;
	virtual ~Renderer() = default;

	virtual VertexBuffer* createVertexBuffer(const Vertex* data, unsigned int count) = 0;
	virtual IndexBuffer* createIndexBuffer(const unsigned int* indices, unsigned int count) = 0;

	virtual GPUResource* createVertexShader(const char* code) = 0;
	virtual GPUResource* createFragmentShader(const char* code) = 0;
	virtual ShaderProgram* createShaderProgram(GPUResource* vs, GPUResource* fs) = 0;

	virtual void bindResource(GPUResource* resource) = 0;
	virtual void unbindResource(GPUResource* resource) = 0;

	virtual void beginFrame() = 0;
	virtual void endFrame() = 0;
private:
};

#endif // RENDERER_H
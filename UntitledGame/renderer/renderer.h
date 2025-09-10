#ifndef RENDERER_H
#define RENDERER_H

class IndexBuffer {};
class VertexBuffer {};
class VertexArray {};

/*
- Texture
- Shader
- Material
- Vertex
- SubMesh
- Mesh
*/

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
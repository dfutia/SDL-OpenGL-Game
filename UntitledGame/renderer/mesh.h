#ifndef MESH_H
#define MESH_H

#include "renderer/renderer.h"

#include <vector>

class Submesh
{
public:
private:
	IndexBuffer* mIndexBuffer;
	VertexBuffer* mVertexBuffer;
};

class Mesh
{
public:
private:
	std::vector<Submesh> mSubmeshes;
};

#endif // MESH_H
#include "platform/gl/glrenderer.h"

GLVertexBuffer::GLVertexBuffer(const Vertex* data, unsigned int count) : mVertexCount(count)
{
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void GLVertexBuffer::setData(const Vertex* vertices, unsigned int count)
{
	mVertexCount = count;
	if (mVBO == 0)
	{
		glGenBuffers(1, &mVBO);
	}
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLIndexBuffer::GLIndexBuffer(const unsigned int* indices, unsigned int count) : mVertexCount(count)
{
	glGenBuffers(1, &mBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &mBufferId);
}
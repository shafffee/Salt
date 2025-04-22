#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &VBO);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void VertexBuffer::buffer(const void* vertices, unsigned int size)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

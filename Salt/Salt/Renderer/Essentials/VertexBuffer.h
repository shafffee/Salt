#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class VertexBuffer{
public:
	VertexBuffer(const void* vertices, unsigned int size);
	~VertexBuffer();

	void bind();
	void buffer(const void* vertices, unsigned int size);
private:
	unsigned int VBO;
};
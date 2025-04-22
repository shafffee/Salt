#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class IndexBuffer {
public:
	IndexBuffer(const void* indexes, unsigned int size);
	~IndexBuffer();

	void bind();
	void buffer(const void* indexes, unsigned int size);
private:
	unsigned int IBO;
};
#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind();

private:
	unsigned int VAO;
};
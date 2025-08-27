#pragma once

#include <glad/glad.h>

class VertexBuffer{
public:
	VertexBuffer(const void* vertices, unsigned int size) {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	};
	VertexBuffer() {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	};
	~VertexBuffer() {
		glDeleteBuffers(1, &VBO);
	};

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	};
	void buffer(const void* vertices, unsigned int size) {
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	};
private:
	unsigned int VBO;
};
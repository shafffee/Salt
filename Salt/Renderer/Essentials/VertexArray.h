#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glad/glad.h>


class VertexArray {
public:
	VertexArray() {
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
	};
	~VertexArray() {
		glDeleteVertexArrays(1, &VAO);
	};

	void bind() {
		glBindVertexArray(VAO);
	};

private:
	unsigned int VAO;
};
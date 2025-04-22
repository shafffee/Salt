#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::bind()
{
	glBindVertexArray(VAO);
}


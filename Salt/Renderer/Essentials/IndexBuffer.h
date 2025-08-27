#pragma once

#include <glad/glad.h>

namespace salt{
	class IndexBuffer {
	public:
	
		IndexBuffer(const void* indexes, unsigned int size) {
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_STATIC_DRAW);
		};

		IndexBuffer() {
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		};
	
		~IndexBuffer() {
			glDeleteBuffers(1, &IBO);
		};
	
		void bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		};
		void buffer(const void* indexes, unsigned int size) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_STATIC_DRAW);
		};
	private:
		uint32_t IBO;
	};
}
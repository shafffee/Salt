#include "Batch.h" 

namespace salt {
	Batch::Batch() : number_of_quads(0),
		shader{ "./Salt/res/shaders/batch.vs", "./Salt/res/shaders/batch.fs" }
	{

		for (int quad = 0; quad < MAX_QUADS_IN_BATCH;quad++) {
			index[quad * 6 + 0] = quad * 4 + 0;
			index[quad * 6 + 1] = quad * 4 + 1;
			index[quad * 6 + 2] = quad * 4 + 2;
			index[quad * 6 + 3] = quad * 4 + 0;
			index[quad * 6 + 4] = quad * 4 + 2;
			index[quad * 6 + 5] = quad * 4 + 3;
		}
	}

	Batch::~Batch()
	{
	}

	void Batch::addQuad(Quad quad)
	{
		if (number_of_quads >= MAX_QUADS_IN_BATCH) {
			//Salt::log::error("Can't add quad to batch because max quald limit is reached");
			return;
		}
		quads[number_of_quads] = quad;
		number_of_quads += 1;
	}

	void Batch::draw()
	{
		VertexBuffer vbo(quads, number_of_quads * sizeof(Quad));
		IndexBuffer ibo(index, sizeof(index));

		shader.bind();

		for (int i = 0;i < 16;i++) {
			shader.setInt("uTextures[" + std::to_string(i) + "]", i);
		}

		VertexArray vao;
		vbo.bind();
		vbo.buffer(quads, number_of_quads * sizeof(Quad));
		ibo.bind();
		ibo.buffer(index, sizeof(index));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(9 * sizeof(float)));
		glEnableVertexAttribArray(3);

		glDrawElements(GL_TRIANGLES, number_of_quads * 6, GL_UNSIGNED_INT, 0);
	}

	void Batch::clear() {
		number_of_quads = 0;
	}
}
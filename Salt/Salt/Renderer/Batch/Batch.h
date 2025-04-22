#pragma once

#include "../Essentials/Essentials.h"
#include "Quad.h"

#define MAX_QUADS_IN_BATCH 1024

namespace salt {
	class Batch {
	public:
		Batch();
		~Batch();
		void addQuad(Quad quad);
		void draw();
		void clear();
	private:
		unsigned number_of_quads;
		Quad quads[MAX_QUADS_IN_BATCH];
		unsigned index[MAX_QUADS_IN_BATCH * 6];
		Shader shader;
	};
}
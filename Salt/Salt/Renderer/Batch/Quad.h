#pragma once

#include "../Essentials/Essentials.h"

namespace salt {
	class Quad {
	private:
		Vertex verticies[4];
	public:
		void seDisplayRect(float x1, float y1, float x2, float y2) {
			//top right
			verticies[0].pos[0] = x2 * 2.0f - 1.0f;
			verticies[0].pos[1] = y1 * (-2.0f) + 1.0f;
			verticies[0].pos[2] = 0.0f;
			//bottom right
			verticies[1].pos[0] = x2 * 2.0f - 1.0f;
			verticies[1].pos[1] = y2 * (-2.0f) + 1.0f;
			verticies[1].pos[2] = 0.0f;
			//bottom left
			verticies[2].pos[0] = x1 * 2.0f - 1.0f;
			verticies[2].pos[1] = y2 * (-2.0f) + 1.0f;
			verticies[2].pos[2] = 0.0f;
			//top left
			verticies[3].pos[0] = x1 * 2.0f - 1.0f;
			verticies[3].pos[1] = y1 * (-2.0f) + 1.0f;
			verticies[3].pos[2] = 0.0f;
		}
		void setColor(float r, float g, float b, float a) {
			r = r / 256.0f;
			g = g / 256.0f;
			b = b / 256.0f;
			a = a / 256.0f;
			//top right
			verticies[0].color_rgba[0] = r;
			verticies[0].color_rgba[1] = g;
			verticies[0].color_rgba[2] = b;
			verticies[0].color_rgba[3] = a;
			//bottom right
			verticies[1].color_rgba[0] = r;
			verticies[1].color_rgba[1] = g;
			verticies[1].color_rgba[2] = b;
			verticies[1].color_rgba[3] = a;
			//bottom left
			verticies[2].color_rgba[0] = r;
			verticies[2].color_rgba[1] = g;
			verticies[2].color_rgba[2] = b;
			verticies[2].color_rgba[3] = a;
			//top left
			verticies[3].color_rgba[0] = r;
			verticies[3].color_rgba[1] = g;
			verticies[3].color_rgba[2] = b;
			verticies[3].color_rgba[3] = a;
		}

		void setTextureRect(float x1, float y1, float x2, float y2) {
			//top right
			verticies[0].texture_pos[0] = x2;
			verticies[0].texture_pos[1] = 1.0f-y1;
			//bottom right
			verticies[1].texture_pos[0] = x2;
			verticies[1].texture_pos[1] = 1.0f - y2;
			//bottom left
			verticies[2].texture_pos[0] = x1;
			verticies[2].texture_pos[1] = 1.0f - y2;
			//top left
			verticies[3].texture_pos[0] = x1;
			verticies[3].texture_pos[1] = 1.0f - y1;
		}

		void setTextureId(float index) {
			verticies[0].texture_id = index;
			verticies[1].texture_id = index;
			verticies[2].texture_id = index;
			verticies[3].texture_id = index;
		}
	};
}
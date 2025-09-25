#pragma once
#include <string>
#include "Shader.h"
#include <vector>
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Model.h"
#include "Sprite.h"

//#include "./TextureManager/TextureManager.h"
//#include "./Batch/Batch.h"
//#include "Color/Color.h"
//#include "FontManager/FontManager.h"

namespace salt {

	class Renderer
	{
	private:

		inline static std::vector<Model*> models;

		//currently the same shader for all objects
		inline static Shader default_shader;

		inline static Camera camera;
	public:

		//draw model
		static void draw(Model* model);
		static void draw(Sprite* sprite);

		//adds verticies that are combined into triangles using indices
		//static void drawConvex();

		static void Init();

		static void Update();
	};
};

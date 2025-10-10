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
#include "Font.h"
#include "Text.h"
#include <map>

//#include "./TextureManager/TextureManager.h"
//#include "./Batch/Batch.h"
//#include "Color/Color.h"
//#include "FontManager/FontManager.h"

namespace salt {

	class Renderer
	{
	private:

		// layer 1 - {model1, model2, ...}
		/*
		
		layer1:
			default_shader: model1, model2
			text_shader: model1
			...
		layer2:
			...

		*/
		inline static std::map<int, std::map<std::string,std::vector<Model*>> > layers;

		//currently the same shader for all objects
		inline static Shader default_shader;
		inline static Shader text_shader;

		inline static Camera* main_camera = nullptr;
	public:

		//draw model
		static void draw(Model* model, int layer=0);
		static void draw(Sprite* sprite, int layer=0);
		static void drawT(Text* text, int layer=0);

		static void setCamera(Camera* camera);

		//adds verticies that are combined into triangles using indices
		//static void drawConvex();

		static void Init();

		static void Update();
	};
};

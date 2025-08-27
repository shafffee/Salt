#pragma once
#include <string>
#include "Shader.h"
#include <vector>
#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"

//#include "./TextureManager/TextureManager.h"
//#include "./Batch/Batch.h"
//#include "Color/Color.h"
//#include "FontManager/FontManager.h"

namespace salt {

	class Renderer
	{
	private:
		
		//currently material for all objects
		inline static Material mat = Material(glm::vec3(0.5375,0.05,0.06625), 
																					glm::vec3(0.18275 ,0.17 ,0.22525), 
																					glm::vec3(0.332741 ,0.328634 ,0.346435), 
																					0.3
																					);

		inline static std::vector<Vertex> _verticies;
		inline static std::vector<uint32_t> _indices;
		//videomode
		inline static int64_t _videomode_x;
		inline static int64_t _videomode_y;
		inline static bool _videomode_stretch;

		//currently the same shader for all objects
		inline static Shader default_shader;

		inline static Camera camera;
	public:

		static void setVideomode(int64_t videomode_x, int64_t videomode_y, bool videomode_stretch);

		//adds polygon
		static void drawPolygon( Vertex a, Vertex b, Vertex c );

		//adds verticies that are combined into triangles using indices
		//static void drawConvex();

		static void Init();

		static void Update();
	};
};

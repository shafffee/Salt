#pragma once
#include <string>
#include "./TextureManager/TextureManager.h"
#include "./Batch/Batch.h"
#include "Color/Color.h"
#include "FontManager/FontManager.h"

namespace salt {

	//EXAMPLE:
	// drawRect(px(256), sc(0.5), sc(0.3), px(100))
	// 
	//used to transform pixels into screencords
	float pix_x(float px);
	float pix_y(float px);
	//used to use screencords in the same format as pixels
	float sc(float c);

	class Renderer
	{
	private:
	public:
		inline static TextureManager* texture_manager;
		inline static Batch* batch;
		inline static FontManager* font_manager;
	public:
		/*
		static void drawTriangle(
			float x1, float y1, 
			float x2, float y2,
			float x3, float y3);
		static void drawRect(
			float x, float y,
			float width, float height);
		*/
		static void drawSprite(
			float x, float y,
			float width, float height,
			std::string texture_name, Color color);
		static void drawSprite(
			float x, float y,
			float width, float height,
			Color color);
		static void drawSprite(
			float x, float y,
			float width, float height,
			std::string texture_name);
		static void drawSprite(
			float x, float y,
			float width, float height);

		static void drawText(float x, float y,
			float width, float height,
			float size,
			std::string text, std::string font_name,
			Color c = Color(255,255,255,255)
		);

		static void Init();

		static void Update();
	};
};
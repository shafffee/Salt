#include "Renderer.h"
#include "Core/Window.h"
namespace salt {



	void Renderer::drawSprite(float x, float y, float width, float height, std::string texture_name, Color color)
	{
		Quad q;
		q.seDisplayRect(x, y, x + width, y + height);
		q.setColor(color.r, color.g, color.b, color.a);
		q.setTextureId(texture_manager->getTexBindIndex(texture_name));
		q.setTextureRect(0, 0, 1, 1);
		batch->addQuad(q);
	}
	void Renderer::drawSprite(float x, float y, float width, float height, Color color)
	{
		Renderer::drawSprite(x, y, width, height, "_blank", color);
	}

	void Renderer::drawSprite(float x, float y, float width, float height, std::string texture_name)
	{
		Renderer::drawSprite(x, y, width, height, texture_name, Color(255,255,255,255));
	}

	void Renderer::drawSprite(float x, float y, float width, float height)
	{
		Renderer::drawSprite(x, y, width, height, "_blank", Color(255, 255, 255, 255));
	}

	void Renderer::drawText(float x, float y, 
		float width, float height, 
		float size_y, 
		std::string text, std::string font_name,
		Color c
		)
	{
		Font* font = font_manager->getFont(font_name);

		float pos_x = x;
		float pos_y = y;
		float size_x = size_y * font->char_pix_x / font->char_pix_y;

		for (int i = 0;i < text.size();i++) {
			if (text[i] == '\n') {
				pos_y += size_y;
				pos_x = 0.0f;
			}
			else {
				font->drawChar(text[i], pos_x, pos_y, size_y, c);
				if (pos_x + size_x > x + width) {
					pos_y += size_y;
					pos_x = 0.0f;
				}
				else {
					pos_x += size_x;
				}
			}
			//if too long vertically then cut
			if (pos_y+size_y > y + height) break;
		}

	}

	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//DEFINES NUMBER OF TEXTURE SLOTS
		GLint max_units;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
		//Salt::log::debug("Max texture units: " + std::to_string(max_units));

		texture_manager = new TextureManager();
		batch = new Batch();
		font_manager = new FontManager();
	}
	void Renderer::Update() {
		texture_manager->bindTextures();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		batch->draw();
		batch->clear();
		glfwSwapBuffers(salt::Window::getGLFWwindow());
	}
	float pix_x(float px)
	{
		return px / salt::Window::getWidth();
	}
	float pix_y(float px)
	{
		return px / salt::Window::getHeight();
	}
	float sc(float c)
	{
		return c;
	}
}
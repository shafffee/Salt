#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "DataTypes/NameID_Container.h"
#include <Renderer/Color/Color.h>


#include <filesystem>
namespace fs = std::filesystem;

#define FONTS_MAX 16

namespace salt {
	struct Font {
		uint16_t chars_in_tex_row;
		uint16_t chars_in_tex_col;
		float char_size_x;
		float char_size_y;
		float char_pix_x;
		float char_pix_y;
		std::string texture_name;
		std::string char_map;

		void loadData(std::string foldername);

		void drawChar(char c,
			float x, float y,
			float size_y,
			Color color);

	};


	class FontManager {
	public:
		NameID_Container<Font, FONTS_MAX> fonts;
		void addFont(std::string folderpath);
		inline Font* getFont(std::string name) { return fonts.getItem(name); };
	};

};
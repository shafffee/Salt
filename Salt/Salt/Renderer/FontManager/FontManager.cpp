#include "FontManager.h"

#include <Renderer/Renderer.h>

namespace salt {
	void Font::loadData(std::string foldername) {
		char_map = "";
		//folder/folder.txt
		std::ifstream data_file(foldername +"/"+ fs::path(foldername).filename().string() + ".txt");
		std::string line;
		//load size
		getline(data_file, line);
		chars_in_tex_row = 0;
		chars_in_tex_col = 0;
		int i = 0;
		while (line[i] != 'x') {
			i++;
		}

		chars_in_tex_row = stoi(line.substr(0, i));
		chars_in_tex_col = stoi(line.substr(i + 1));

		char_size_x = 1.0f / chars_in_tex_row;
		char_size_y = 1.0f / chars_in_tex_col;
		//load strings
		while (getline(data_file, line)) {
			char_map += line + '\n';
		}

		int width, height;
		//folder/folder.png
		//texture is called 
		// _font_folder
		texture_name = "_font_" + fs::path(foldername).filename().string();
		salt::Renderer::texture_manager->LoadTexture(texture_name, foldername + "/" + fs::path(foldername).filename().string() + ".png", &width, &height);
		char_pix_x = width / chars_in_tex_row;
		char_pix_y = height / chars_in_tex_col;
	}
	void Font::drawChar(char c, float x, float y, float size_y, Color color) {

		int cx = 0;
		int cy = 0;
		for (int i = 0;i < char_map.size();i++) {
			if (char_map[i] == '\n') {
				cy += 1;
				cx = 0;
			}
			else {
				if (char_map[i] == c) {
					break;
				}
				cx++;
			}
		}

		Quad q;
		q.seDisplayRect(x, y, x+size_y * char_pix_x / char_pix_y, y+size_y);
		q.setColor(color.r, color.g, color.b, color.a);
		q.setTextureId(salt::Renderer::texture_manager->getTexBindIndex(texture_name));
		q.setTextureRect(cx * char_size_x, cy * char_size_y, (cx+1) * char_size_x, (cy+1) * char_size_y);
		//not really great that uses batch var of renderer, mb fix laterr
		salt::Renderer::batch->addQuad(q);
	}
	void FontManager::addFont(std::string folderpath)
	{
		Font f;
		f.loadData(folderpath);
		fonts.addItem(f, fs::path(folderpath).filename().string());
	}
}

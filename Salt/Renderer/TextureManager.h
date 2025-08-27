#pragma once
#include <stb_image.h>
#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//will need a lot of changes

//Max textures are also tied with a fragment shader uniform(assigned in Batch.draw()) and a  fragment shader itself
//CONSIDER THIS BEFORE MAKING AN UPGRADE 
#define MAX_TEXTURE_NUMBER 16

class TextureManager {
public:

	TextureManager() {
		glGenTextures(MAX_TEXTURE_NUMBER, bind_index);
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) name[i] = "";
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) filename[i] = "";
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) is_loaded[i] = false;

		//add _blank texture
		name[0] = "_blank";
		is_loaded[0] = true;
		GLubyte blankTexData[] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, blankTexData);
	}

	//used to get size of loaded texture
	void LoadTexture(const std::string& tex_name, const std::string& tex_filename, int* width, int* height) {
		unsigned tex_index = MAX_TEXTURE_NUMBER + 1;
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) {
			if (name[i] == "") {
				tex_index = i;
				name[tex_index] = tex_name;
				filename[tex_index] = tex_filename;
				is_loaded[tex_index] = true;
				break;
			}
			if (name[i] == tex_name) {
				//Salt::log::error("texture with name " + tex_name + " is already created");
				return;
			};
		}
		if (tex_index == MAX_TEXTURE_NUMBER + 1) {
			//Salt::log::error("unable to add texture " + tex_name + " because max texture number is  reached");
			return;
		}

		glBindTexture(GL_TEXTURE_2D, tex_index);
		// set the texture wrapping/filtering options (on currently bound texture)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(true);
		int nrChannels;
		/*unsigned char* data = stbi_load("./Salt/res/textures/texture1.png", &width, &height,
			&nrChannels, 0);*/
		unsigned char* data = stbi_load(filename[tex_index].c_str(), width, height,
			&nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			//std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	//just load
	void LoadTexture(const std::string& tex_name, const std::string& tex_filename) {
		int w, h;
		LoadTexture(tex_name, tex_filename, &w, &h);
	}

	unsigned getTexBindIndex(std::string tex_name) {
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) {
			if (tex_name == name[i]) {
				//Salt::log::error(name[i] + "\t" + std::to_string(i));
				return i;
			}
		}
		//Salt::log::error("unable to find texture" + tex_name);
		return 0;
	}

	void bindTextures() {
		for (unsigned i = 0;i < MAX_TEXTURE_NUMBER;i++) {
			if (is_loaded[i]) {
				//Salt::log::error(name[i] + "\t" + std::to_string(bind_index[i]));
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, i);
			}
		}
	}
private:
	unsigned bind_index[MAX_TEXTURE_NUMBER];
	std::string name[MAX_TEXTURE_NUMBER];
	std::string filename[MAX_TEXTURE_NUMBER];
	bool is_loaded[MAX_TEXTURE_NUMBER];
};
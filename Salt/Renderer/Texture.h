#pragma once
#include <string>
#include "Shader.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//will need a lot of changes

//Max textures are also tied with a fragment shader uniform(assigned in Batch.draw()) and a  fragment shader itself
//CONSIDER THIS BEFORE MAKING AN UPGRADE 
#define MAX_TEXTURE_NUMBER 8

//texture type for shader
enum TextureType{
	DIFFUSE,
	SPECULAR
};


/*
//texture struct
class Texture{
private:
	//those two vars are used in Textures and should not be used anywhere else
    std::string filepath = "";
public:
	Texture(const std::string& filepath);

	int getWidth() {};
	int getHeight() {};

	std::string getFilepath() {return filepath;};

	TextureType getType() {};
	void setType(const TextureType& t) {};
};
*/

struct Texture{
	std::string filepath = "";
	TextureType type = DIFFUSE;
};

/*
Textures::UnbindAll();
Textures::bind("background.png");
Textures::passBoundTexturesToShader
*/


class Textures{

public:
	static void passTexturesToShader(const std::vector<Texture>& textures, salt::Shader &shader);
	static void Init();

private:

	static void bind(const Texture& texture);
	static void bind(const std::string& filepath, TextureType type=DIFFUSE);

	static void UnbindAll();

	static void passBoundTexturesToShader(salt::Shader &shader);

	struct TextureInstance{

		//set in Textures::bind
		TextureType type = DIFFUSE;
    	std::string filepath = "";

    	//set in TextureInstance::loadFromFile
    	int width = 0;
    	int height = 0;
    	int channels = 0;
    	unsigned char* data = nullptr;

    	void loadFromFile(const std::string& filepath);

    	void bindToSlot(unsigned bind_index);

	};

	inline static std::vector<TextureInstance> texture_data;
	inline static int bound_texture_indicies[MAX_TEXTURE_NUMBER]; //has -1 if no texture is bound to corresponding bind indes
	inline static unsigned bind_indices[MAX_TEXTURE_NUMBER];



	//returns index in texture_data vector or -1 if not found
	static int find_texture_by_name(const std::string& filepath);

	//returns index in bound_texture_indicies[i]that has -1 (no texture in it)  (or -1 if not found)
	static int find_slot_to_bind();

	static int find_texture_in_bound(int index);
};
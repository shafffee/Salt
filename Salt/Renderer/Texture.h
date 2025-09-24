#pragma once
#include <string>
#include "Shader.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//will need a lot of changes

//textures num is also defined in shader, you should set it there too
//CONSIDER THIS BEFORE MAKING AN UPGRADE 
#define TEXTURES_IN_SHADER 8

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

	struct TextureInstance{

		TextureType type = DIFFUSE;
    	std::string filepath = "";

    	//set in TextureInstance::loadFromFile
    	int width = 0;
    	int height = 0;
    	int channels = 0;
    	unsigned char* data = nullptr;

    	//handle for bindless texture
    	GLuint64 handle = 0;
    	GLuint textureId = 0;


    	void loadFromFile(const std::string& filepath);

    	void loadToGPU();
    	void Textures::TextureInstance::loadToGPU_Fallback();

    	void unloadFromGPU();

	};

	inline static std::vector<TextureInstance> texture_data;

	//returns index in texture_data vector or -1 if not found
	static int find_texture_by_name(const std::string& filepath);
};
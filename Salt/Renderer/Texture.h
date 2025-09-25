#pragma once
#include <string>
#include "Shader.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//will need a lot of changes


//texture type for shader
/*
enum TextureType{
	DIFFUSE,
	SPECULAR
};
*/

struct Texture{
	std::string filepath = "";
	//TextureType type = DIFFUSE;

	Texture(std::string filepath=""): filepath(filepath){};

	bool isNull(){
		return filepath == "";
	} 
};

class Textures{

public:
	static void passTextureToShader(const Texture& texture, salt::Shader &shader, const std::string& field_name);
	static void Init();

private:

	struct TextureInstance{

		//TextureType type = DIFFUSE;
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
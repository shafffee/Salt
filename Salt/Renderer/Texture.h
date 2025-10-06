#pragma once
#include <string>
#include <map>
#include "Shader.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//runs stbi_image_free(ti.data); if 1
#define CLEAR_DATA_AFTER_LOADING_TO_GPU 1

//default tag for texture from file
#define TEXTURE_FROM_FILE_TAG "#texture_from_file | "
//default tag for texture from data
#define TEXTURE_FROM_DATA_TAG "#texture_from_data | "


//texture type for shader
/*
enum TextureType{
	DIFFUSE,
	SPECULAR
};
*/

class Texture;

class Textures{

public:
	static void passTextureToShader(const Texture& texture, salt::Shader &shader, const std::string& field_name);
	static void Init();

private:

	inline static uint64_t textures_loaded = 0;

	struct TextureInstance{

		//TextureType type = DIFFUSE;
    	std::string tag = "";	//a unique tag for each texture. It is used to determine if it is already loaded
    	std::string filepath = "";
    	std::string label = "";	//if texture is loaded from data it can use label (works the same as filepath)

    	//set in TextureInstance::loadFromFile
    	int width = 0;
    	int height = 0;
    	int channels = 0;
    	unsigned char* data = nullptr;

    	//handle for bindless texture
    	GLuint64 handle = 0;
    	GLuint textureId = 0;


    	void loadFromFile(const std::string& filepath);
    	void loadFromData(const unsigned char*& data, int width, int height, int channels);

    	void loadToGPU();
    	void Textures::TextureInstance::loadToGPU_Fallback();

    	void unloadFromGPU();

	};

	//loads texture from file, loads it to gpu and returns id
	static uint64_t TextureFromFile(const std::string& filepath);
	//loads texture from file, loads it to gpu and returns id
	//does not copy data into TextureInstance, does not clean it
	static uint64_t TextureFromData(const unsigned char*& data, int width, int height, int channels,  const std::string& label = "");

	friend class Texture;

	// map name - id
	// name = tag+filepath
    inline static std::map<std::string, uint64_t> name_id_map;
    inline static std::map<uint64_t, TextureInstance> id_instance_map;
};



class Texture{
public:


	Texture(){
		id = 0;
	};

	Texture(std::string filepath){
		id = Textures::TextureFromFile(filepath);
	};

	Texture(const unsigned char*& data, int width, int height, int channels, const std::string& label){
		id = Textures::TextureFromData(data, width, height, channels, label);
	};

	bool isNull() const{
		return id == 0;
	} 
	
private:
	uint64_t id = 0;	//if id is 0 -> texture is null
	//TextureType type = DIFFUSE;

	friend class Textures;
};
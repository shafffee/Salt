#pragma once
#include <string>
#include "Shader.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//will need a lot of changes

//Max textures are also tied with a fragment shader uniform(assigned in Batch.draw()) and a  fragment shader itself
//CONSIDER THIS BEFORE MAKING AN UPGRADE 
#define MAX_TEXTURE_NUMBER 16

//texture type for shader
enum TextureType{
	DIFFUSE,
	SPECULAR
};


//texture struct
class Texture{
private:
	//those two vars are used in Textures and should not be used anywhere else
	bool is_bound = false;
	unsigned bind_index = 0;

	TextureType type = DIFFUSE;
    std::string filepath = "";

    int width = 0;
    int height = 0;
	friend class Textures;

	Texture(){};
public:
	Texture(const std::string& filepath, TextureType type = DIFFUSE);
	void bind();
	void unbind();

	int getWidth() {return width;};
	int getHeight() {return height;};

	//bool isBound() {return is_bound};
	//unsigned getBindIndex(){}; //error if not bound

	std::string getFilepath() {return filepath;};

	TextureType getType() {return type;};
	void setType(const TextureType& t) {type=t;};
};

/*
class TextureInstance{
private:
	//those two vars are used in Textures and should not be used anywhere else
	bool is_bound = false;
	unsigned bind_index = 0;

	TextureType type = DIFFUSE;
    std::string filepath = "";

    int width = 0;
    int height = 0;
	friend class Textures;

	TextureInstance(){};
public:
	TextureInstance(const std::string& filepath, TextureType type = DIFFUSE);
	void bind();
	void unbind();

	int getWidth() {return width;};
	int getHeight() {return height;};

	//bool isBound() {return is_bound};
	//unsigned getBindIndex(){}; //error if not bound

	std::string getFilepath() {return filepath;};

	TextureType getType() {return type;};
	void setType(const TextureType& t) {type=t;};
};
*/

class Textures{
public:

	static void UnbindAll();
	static void passTexturesToShader(salt::Shader &shader);


	static void Init(){
		//TODO: get MAX_TEXTURE_NUMBER from opengl api
		unsigned bind_indices[MAX_TEXTURE_NUMBER];
		glGenTextures(MAX_TEXTURE_NUMBER, bind_indices);
		for(int i=0; i<MAX_TEXTURE_NUMBER; i++){
			textures[i].bind_index=bind_indices[i];
		}
	}

private:
	inline static Texture textures[MAX_TEXTURE_NUMBER];

	//loads texture and binds it
	static void LoadAndBindTexture(Texture* texture);
	
	static void Unbind(Texture* texture);

	friend class Renderer;
	friend class Texture;
};
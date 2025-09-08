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


//texture type for shader
enum TextureType{
	DIFFUSE,
	SPECULAR
}

//texture struct
struct Texture{
	unsigned bind_index = 0;
	TextureType type = DIFFUSE;
    std::string filepath = "";

    int width = 0;
    int height = 0;
}


/*
Texture manager has 3 main functions:
CleanTextures - unloads all textures (does not unload textures from gpu, but makes them available for rewrite)
LoadTexture - loads one texture using its filepath
*/

class TextureManager {
public:
	Texture textures[MAX_TEXTURE_NUMBER];

	TextureManager() {
		//TODO: get MAX_TEXTURE_NUMBER from opengl api
		glGenTextures(MAX_TEXTURE_NUMBER, bind_index);
	}

	void CleanTextures(){
		for(int i = 0; i<MAX_TEXTURE_NUMBER;i++){
			textures[i] = Texture();
		}
	}

	//loads texture and binds it
	Texture LoadTexture(const std::string& filepath, TextureType type) {
		//if texture is already binded -> return  
		unsigned bind_index = MAX_TEXTURE_NUMBER+1;
		for(int i=0; i<MAX_TEXTURE_NUMBER; i++){
			if(textures[i].filepath == filepath){
				//Salt::log::debug("texture "+filepath+" has already been binded")
				return;
			}
			if(textures[i].filepath == ""){
				//found free spot
				bind_index=i;
				break;
			}
		}

		if(bind_index>MAX_TEXTURE_NUMBER){
			Salt::log::error("texture "+filepath+" can not be binded: no free spot")
			return;
		}


		//LOADING TEXTURE
		glBindTexture(GL_TEXTURE_2D, );
		// set the texture wrapping/filtering options (on currently bound texture)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(true);
		int nrChannels;
		int width, height;
		unsigned char* data = stbi_load(filepath, &width, &height,
			&nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Salt::log::error("Failed to load texture: "+filepath)
		}
		stbi_image_free(data);

		//WRITING DATA TO TEXTURE
		Texture[bind_index].bind_index=free_spot;
		Texture[bind_index].type=type;
		Texture[bind_index].filepath=filepath;
		Texture[bind_index].width=width;
		Texture[bind_index].height=height;

		return Texture[bind_index];
	}

	void passTexturesToShader(){
		unsigned int diffuseCount = 0;
    	unsigned int specularCount = 0;
    	unsigned int totalCount = 0;

    	for(unsigned int i = 0; i < MAX_TEXTURE_NUMBER; i++)
    	{
        	glActiveTexture(GL_TEXTURE0 + totalCount); // activate proper texture unit before binding
        		
       		if(textures[i].filepath!=""){
	        	std::string name = "";
   		    	if(textures[i].type==DIFFUSE){
   		    		diffuseCount++;
   		    		totalCount++;
 	        		name = "texture_diffuse"+std::to_string(diffuseCount);
   		    	}
        		else if(textures[i].type==SPECULAR){
   		    		specularCount++;
   		    		totalCount++;
 	        		name = "texture_specular"+std::to_string(specularCount);
   		    	}
	
        		shader.setInt(("material." + name).c_str(), i);
       			glBindTexture(GL_TEXTURE_2D, textures[i].bind_index);
       		}
    	}
    	glActiveTexture(GL_TEXTURE0);
	}

};
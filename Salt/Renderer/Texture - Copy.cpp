#include "Texture.h"
#include <stb_image.h>
#include <Logging.h>


std::string GetOpenGLError() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) return "GL_NO_ERROR";

	std::vector<std::string> errors;
	while (error != GL_NO_ERROR) {
		switch (error) {
		case GL_INVALID_ENUM:
			errors.push_back("GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			errors.push_back("GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			errors.push_back("GL_INVALID_OPERATION");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errors.push_back("GL_INVALID_FRAMEBUFFER_OPERATION");
			break;
		case GL_OUT_OF_MEMORY:
			errors.push_back("GL_OUT_OF_MEMORY");
			break;
		case GL_STACK_UNDERFLOW:
			errors.push_back("GL_STACK_UNDERFLOW");
			break;
		case GL_STACK_OVERFLOW:
			errors.push_back("GL_STACK_OVERFLOW");
			break;
		default:
			errors.push_back("UNKNOWN_ERROR (0x" +
				std::to_string(static_cast<unsigned int>(error)) + ")");
		}
		error = glGetError();
	}

	std::string result;
	for (const auto& err : errors) {
		if (!result.empty()) result += " | ";
		result += err;
	}
	return result;
}


Texture::Texture(const std::string& filepath, TextureType type){
	salt::Logging::Debug( "Texture::Texture "+filepath);

	this->filepath = filepath;
	this->type = DIFFUSE;
	

    //loading image to get size
    stbi_set_flip_vertically_on_load(true);
	int nrChannels;
	int width, height;
	unsigned char* data = stbi_load(this->filepath.c_str(), &width, &height,
		&nrChannels, 0);
	if (data)
	{
        //recording size if loaded correctly
        this->width = width;
        this->height = height; 
	}
	else
	{
		salt::Logging::Error("Failed to load texture: "+this->filepath);
	}
	stbi_image_free(data);
};

void Texture::bind(){
    Textures::LoadAndBindTexture(this);
}

void Texture::unbind(){
    Textures::Unbind(this);
}



void Textures::UnbindAll(){
	for(int i = 0; i<MAX_TEXTURE_NUMBER;i++){
		textures[i].is_bound = false;
	}
}

void Textures::LoadAndBindTexture(Texture* texture) {
	salt::Logging::Debug("texture "+texture->filepath+" is being loaded and binded");

	//if texture is already binded -> return  
	unsigned bind_index;
    int i=0;
	for(; i<MAX_TEXTURE_NUMBER; i++){
		if(textures[i].filepath == texture->filepath){
			//salt::log::debug("texture "+filepath+" has already been binded")
			if(textures[i].is_bound) return;
			bind_index=textures[i].bind_index;
			break;
		}
		if(textures[i].is_bound = false){
			//found free spot
			bind_index=textures[i].bind_index;
			break;
		}
	}
	if(i>=MAX_TEXTURE_NUMBER){
		salt::Logging::Error("texture "+texture->filepath+" can not be binded: no free spot");
		return;
	}
	//LOADING TEXTURE
	glBindTexture(GL_TEXTURE_2D, bind_index);
	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	salt::Logging::Error(GetOpenGLError());

	stbi_set_flip_vertically_on_load(true);
	int nrChannels;
	int width, height;
	unsigned char* data = stbi_load(texture->filepath.c_str(), &width, &height,
		&nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		salt::Logging::Error(GetOpenGLError());
	}
	else
	{
		salt::Logging::Error("Failed to load texture: "+texture->filepath);
	}
	stbi_image_free(data);
	//WRITING DATA TO TEXTURE
	textures[bind_index].bind_index=bind_index;
	textures[bind_index].type=texture->type;
	textures[bind_index].filepath=texture->filepath;
	textures[bind_index].width=width;
	textures[bind_index].height=height;
	*texture = textures[bind_index];
}

void Textures::Unbind(Texture* texture){
    for(int i = 0; i<MAX_TEXTURE_NUMBER;i++){
        if(textures[i].filepath==texture->filepath && textures[i].type==texture->type){
		    textures[i].is_bound = false;
        }
	}
}

void Textures::passTexturesToShader(salt::Shader &shader){
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
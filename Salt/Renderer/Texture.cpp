#include "Texture.h"
#include <stb_image.h>
#include <Logging.h>


void Textures::Init(){
    //TODO: get MAX_TEXTURE_NUMBER from opengl api
    /*
    glGenTextures(MAX_TEXTURE_NUMBER, bind_indices);
    UnbindAll();
    for(int i=0; i<MAX_TEXTURE_NUMBER;i++){
        glBindTexture(GL_TEXTURE_2D, bind_indices[i]);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    */

    //if GL_ARB_bindless_texture is undefined -> regenerate glad
    if ( !GL_ARB_bindless_texture ){
       salt::Logging::Error("GL_ARB_bindless_texture is not supported");
        return;
    }
    if (!GL_ARB_direct_state_access){
        salt::Logging::Error("GL_ARB_direct_state_access is not supported");
        return;
    }
}



void Textures::passTexturesToShader(const std::vector<Texture>& textures, salt::Shader &shader){

    if(textures.size()>TEXTURES_IN_SHADER){
        salt::Logging::Error("Textures::passTexturesToShader : too many textures. shader supports less handles");
        return;
    }

    GLuint64 handles[TEXTURES_IN_SHADER] = {0};


    for(unsigned int i = 0; i < textures.size(); i++)
    {

        int index = find_texture_by_name(textures[i].filepath);

        //if texture is loaded for the first time
        if(index==-1){
            TextureInstance ti;
            ti.filepath = textures[i].filepath;
            ti.type = textures[i].type;
            texture_data.push_back(ti);
            index = texture_data.size()-1;
        }

        //reading image and sending it to gpu
        if(texture_data[index].data==nullptr) texture_data[index].loadFromFile(texture_data[index].filepath);
        if(texture_data[index].handle==0) texture_data[index].loadToGPU();

        //sending image to shader
        //glUniformHandleui64ARB(shader, texture_data[index].handle);
        handles[i] = texture_data[index].handle;


    }

    //sending handles to shader
    shader.setUint64Array("textures", TEXTURES_IN_SHADER, handles);

};


//----------------------------------------------------------


//returns index in texture_data vector or -1 if not found
int Textures::find_texture_by_name(const std::string& filepath){
    int result = -1;

    for(int i=0; i<texture_data.size();i++){
        if(texture_data[i].filepath==filepath){
            result = i;
            break;
        }
    }

    return result;
}

//------------------------------------------------------------

void Textures::TextureInstance::loadFromFile(const std::string& filepath){

    if(data) stbi_image_free(data);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filepath.c_str(), &width, &height,
        &channels, 0);
    
    if (!data){
        salt::Logging::Error("Failed to load texture: "+filepath);
        return;
    }
};


void Textures::TextureInstance::loadToGPU(){

    if (!data){
        salt::Logging::Error("No data to load texture to GPU");
        return;
    }

    //if handle is not create4d and texture is not loaded to gpu
    if(handle==0){

        GLuint textureId;
        glCreateTextures(GL_TEXTURE_2D, 1, &textureId); // requires GL_ARB_direct_state_access

        // Determine format based on channel count
        //there may be errors with sized format (it may not be 8)
        GLenum sizedInternalFormat = GL_RGB8;
        GLenum baseInternalFormat = GL_RGB;
        switch(channels) {
            case 1: baseInternalFormat = GL_RED; sizedInternalFormat = GL_R8; break;
            case 3: baseInternalFormat = GL_RGB; sizedInternalFormat = GL_RGB8; break;
            case 4: baseInternalFormat = GL_RGBA; sizedInternalFormat = GL_RGBA8; break;
            default:
                salt::Logging::Error("Textures::TextureInstance::bindToSlot Unsupported texture format with " + 
                    std::to_string(channels) + " channels in " + filepath);
                return;
        }

        glTextureStorage2D(textureId, 1, sizedInternalFormat,  width, height);
        glTextureSubImage2D(textureId, 0, 0, 0, width, height, baseInternalFormat, GL_UNSIGNED_BYTE, data);
 
        // Устанавливаем параметры текстуры
        glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glGenerateTextureMipmap(textureId);

        handle = glGetTextureHandleARB(textureId);
        glMakeTextureHandleResidentARB(handle);
    }
};

void Textures::TextureInstance::unloadFromGPU(){
    //NOT IMPLEMENTED YET
    //glMakeTextureHandleNonResidentARB(handle);
};




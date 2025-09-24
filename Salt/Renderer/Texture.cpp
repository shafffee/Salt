#include "Texture.h"
#include <stb_image.h>
#include <Logging.h>


void Textures::Init(){

    //if GL_ARB_bindless_texture is undefined -> regenerate glad
    if ( !GLAD_GL_ARB_bindless_texture ){
       salt::Logging::Error("GL_ARB_bindless_texture is not supported: CRITICAL");
        return;
    }

    //needed for glTexStorage2D(); It is used in loadToGpu in no-fallback case.
    if ( !GLAD_GL_ARB_texture_storage ){
       salt::Logging::Warning("GL_ARB_texture_storage is not supported, using fallback");
        return;
    }

    if (!GLAD_GL_ARB_direct_state_access){
        salt::Logging::Warning("GL_ARB_direct_state_access is not supported, using fallback");
        return;
    }

}



void Textures::passTextureToShader(const Texture& texture, salt::Shader &shader, const std::string& field_name){

    int index = find_texture_by_name(texture.filepath);
    //if texture is loaded for the first time
    if(index==-1){
        TextureInstance ti;
        ti.filepath = texture.filepath;
        //ti.type = texture.type;
        texture_data.push_back(ti);
        index = texture_data.size()-1;
    }

    //reading image and sending it to gpu
    if(texture_data[index].data==nullptr) texture_data[index].loadFromFile(texture_data[index].filepath);
    if(texture_data[index].handle==0) texture_data[index].loadToGPU();
    //salt::Logging::Debug("Loaded "+texture_data[index].filepath+" "+std::to_string(texture_data[index].handle));

    //sending handle to shader
    shader.setUVec2(field_name, texture_data[index].handle);
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



//this function uses GLAD_ARB_direct_state_access, but has fallbacks if needed
//TODO: separate on two functions:fallback and standart
void Textures::TextureInstance::loadToGPU(){

    if (!data){
        salt::Logging::Error("No data to load texture to GPU");
        return;
    }

    if(!GLAD_GL_ARB_direct_state_access || !GLAD_GL_ARB_texture_storage){
        loadToGPU_Fallback();
        return;
    }

    //if handle is not created and texture is not loaded to gpu
    if(handle==0){

        glCreateTextures(GL_TEXTURE_2D, 1, &textureId);

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

        //texture_parameters
        glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glGenerateTextureMipmap(textureId);

        handle = glGetTextureHandleARB(textureId);
        glMakeTextureHandleResidentARB(handle);
    
    }
};


void Textures::TextureInstance::loadToGPU_Fallback(){
    
    //if handle is not created and texture is not loaded to gpu
    if(handle==0){

        if (textureId == 0) {
            glGenTextures(1, &textureId);
        }

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



        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, sizedInternalFormat, width, height, 0, baseInternalFormat, GL_UNSIGNED_BYTE, data);

        //texture_parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            
        glGenerateMipmap(GL_TEXTURE_2D);

        handle = glGetTextureHandleARB(textureId);
        glMakeTextureHandleResidentARB(handle);

        // Unbind texture after configuration
        glBindTexture(GL_TEXTURE_2D, 0);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            salt::Logging::Error("OpenGL error in texture loading: " + std::to_string(err));
        }
    
    }
}

void Textures::TextureInstance::unloadFromGPU(){
    //NOT IMPLEMENTED YET
    //glMakeTextureHandleNonResidentARB(handle);
};




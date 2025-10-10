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

    if(texture.isNull()){
        salt::Logging::Error("Trying to pass null texture to shader");
        return;
    }

    if(!id_instance_map.count(texture.id)){
        salt::Logging::Error("Trying to pass texture with invalid id to shader");
        return;
    }

    //sending handle to shader
    shader.setUVec2(field_name, id_instance_map[texture.id].handle);
};


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

void Textures::TextureInstance::loadFromData(unsigned char* data, int width, int height, int channels){

    if (!data || width <= 0 || height <= 0 || channels <= 0) {
        salt::Logging::Error("Smth is wrong in the Textures::TextureInstance::loadFromData. Null argument.");
        return;
    }

    // Delete existing data first to prevent leaks
    delete[] this->data;

    this->width = width;
    this->height=height;
    this->channels=channels;

    size_t size = width * height * channels;
    this->data = new unsigned char[size];
    std::copy(data, data + size, this->data);
};



//loads texture from file, loads it to gpu and returns id
uint64_t Textures::TextureFromFile(const std::string& filepath){
        //calculating name for texture
        std::string name = TEXTURE_FROM_FILE_TAG+filepath;

        //if file is already loaded
        if(name_id_map.count(name)){
            return name_id_map[name];
        }
        //else

        textures_loaded+=1;
        uint64_t id = textures_loaded;

        TextureInstance ti;
        ti.tag = TEXTURE_FROM_FILE_TAG;
        ti.filepath = filepath;
        ti.loadFromFile(filepath);
        ti.loadToGPU();
        if(ti.data && CLEAR_DATA_AFTER_LOADING_TO_GPU) stbi_image_free(ti.data);
        //ti.type = texture.type;

        name_id_map.insert({name, id});
        id_instance_map.insert({id, ti});

        return id;
};

uint64_t Textures::TextureFromData(unsigned char* data, int width, int height, int channels, const std::string& label){
        //calculating name for texture
        std::string name = TEXTURE_FROM_DATA_TAG+label;

        //if texture with the same label is already loaded
        if(name_id_map.count(name)){
            return name_id_map[name];
        }
        //else

        textures_loaded+=1;
        uint64_t id = textures_loaded;

        TextureInstance ti;
        ti.tag = TEXTURE_FROM_DATA_TAG;
        ti.label = label;
        ti.loadFromData(data, width, height, channels);
        ti.loadToGPU();

        
        if(ti.data && CLEAR_DATA_AFTER_LOADING_TO_GPU){
            delete[] ti.data;
            ti.data = nullptr;
        };
        


        name_id_map.insert({name, id});
        id_instance_map.insert({id, ti});

        return id;
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
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
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
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
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




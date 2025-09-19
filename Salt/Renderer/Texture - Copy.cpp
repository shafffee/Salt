#include "Texture.h"
#include <stb_image.h>
#include <Logging.h>




void Textures::Init(){
    //TODO: get MAX_TEXTURE_NUMBER from opengl api
    glGenTextures(MAX_TEXTURE_NUMBER, bind_indices);
    UnbindAll();
    for(int i=0; i<MAX_TEXTURE_NUMBER;i++){
        glBindTexture(GL_TEXTURE_2D, bind_indices[i]);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}



void Textures::passTexturesToShader(const std::vector<Texture>& textures, salt::Shader &shader){
    //Textures::UnbindAll();
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        Textures::bind(textures[i]);
    }

    Textures::passBoundTexturesToShader(shader);
};


//----------------------------------------------------------



void Textures::bind(const Texture& texture){
    bind(texture.filepath, texture.type);
}


void Textures::bind(const std::string& filepath, TextureType type){
    //loading texture to ram if it is not loaded
    int index = find_texture_by_name(filepath); //index in texture_data;
    if(index==-1){
        TextureInstance newTex;
        newTex.filepath = filepath;
        newTex.type = type;
        newTex.loadFromFile(filepath);
        texture_data.push_back(newTex);
        index = texture_data.size()-1;
    }

    //does not trigger after unbind all. needs to be fixed
    if(find_texture_in_bound(index)!=-1) return; //if texture is already bound

    else{
        //checking if there is free space to bind
        int slot = find_slot_to_bind();
        if(slot==-1){
            salt::Logging::Error("Failed to bind texture: "+filepath+"\t no free spots to bind");
            return;
        }
        salt::Logging::Debug("Binding "+filepath);

        bound_texture_indicies[slot]=index;
        texture_data[index].bindToSlot(bind_indices[slot]);
    }

};


void Textures::UnbindAll(){
    for(int i =0;i<MAX_TEXTURE_NUMBER;i++){
        bound_texture_indicies[i]=-1;
    }
};


void Textures::passBoundTexturesToShader(salt::Shader &shader){
    unsigned int diffuseCount = 0;
    unsigned int specularCount = 0;
    unsigned int totalCount = 0;
    for(unsigned int i = 0; i < MAX_TEXTURE_NUMBER; i++)
    {
        //skip if no texture bound to slot
        if(bound_texture_indicies[i]==-1) continue;

        glActiveTexture(GL_TEXTURE0 + totalCount); // activate proper texture unit before binding
        glBindTexture(GL_TEXTURE_2D, bind_indices[i]);
            
        std::string name = "";
        if(texture_data[bound_texture_indicies[i]].type==DIFFUSE){
            diffuseCount++;
            totalCount++;
            name = "texture_diffuse"+std::to_string(diffuseCount);
        }
        else if(texture_data[bound_texture_indicies[i]].type==SPECULAR){
            specularCount++;
            totalCount++;
            name = "texture_specular"+std::to_string(specularCount);
        }
        shader.setInt(("material." + name).c_str(), i);
    }
    glActiveTexture(GL_TEXTURE0);
};

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


//returns index in bound_texture_indicies[i]that has -1 (no texture in it)  (or -1 if not found)
int Textures::find_slot_to_bind(){
    int result = -1;

    for(int i=0; i<MAX_TEXTURE_NUMBER;i++){
        if(bound_texture_indicies[i]==-1){
            result = i;
            break;
        }
    }

    return result;
}

int Textures::find_texture_in_bound(int index){
    int slot = -1;

    for(int i=0; i<MAX_TEXTURE_NUMBER;i++){
        if(bound_texture_indicies[i]==index){
            slot = i;
            break;
        }
    }

    return slot;
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


void Textures::TextureInstance::bindToSlot(unsigned bind_index){
    if(!data){
        salt::Logging::Error("Failed to bind texture: "+filepath+"\tno data");
        return;
    }


    glBindTexture(GL_TEXTURE_2D, bind_index);  

    // Determine format based on channel count
    GLenum format = GL_RGB;
    switch(channels) {
        case 1: format = GL_RED; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default:
            salt::Logging::Error("Textures::TextureInstance::bindToSlot Unsupported texture format with " + 
                std::to_string(channels) + " channels in " + filepath);
            return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
    GL_UNSIGNED_BYTE, data);


    glGenerateMipmap(GL_TEXTURE_2D); 
}

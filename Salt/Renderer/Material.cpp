#include "Material.h"

void Material::passToShader(salt::Shader &shader){
    shader.setVec4("material.color", color);

    if(!texture.isNull()){
      Textures::passTextureToShader(texture, shader, "material.texture_handle");
    }
}
#version 330 core

#extension GL_ARB_bindless_texture : require


in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vFragPos;
in vec3 vViewPos;

out vec4 FragColor;

struct Material {
    vec4 color;             //tint
    uvec2 texture_handle;
}; 

uniform Material material;

void main()
{

    // Прoверяем, что handle не нулевой
    if (material.texture_handle != 0u) 
        FragColor = material.color*texture(sampler2D(material.texture_handle), vTexCoords);
    else
        FragColor = material.color;

}
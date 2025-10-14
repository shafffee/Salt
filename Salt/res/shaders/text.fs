#version 330 core

#extension GL_ARB_bindless_texture : require

in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vFragPos;
in vec3 vViewPos;

out vec4 FragColor;

struct Material {
    vec4 color;             //text color
    uvec2 texture_handle;
}; 

uniform Material material;

void main()
{

    // Прoверяем, что handle не нулевой
    if (!(material.texture_handle.x == 0u && material.texture_handle.y == 0u)){
        FragColor = material.color;
        FragColor.a = material.color.a*texture(sampler2D(material.texture_handle), vTexCoords).r;
    }
    else
        FragColor = vec4(1,0,1,1);

}
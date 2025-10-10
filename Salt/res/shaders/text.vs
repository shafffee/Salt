#version 420 core

#extension GL_ARB_bindless_texture : require

// Matches Vertex struct layout
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 vNormal;
out vec2 vTexCoords;
out vec3 vFragPos; 
out vec3 vViewPos; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

void main()
{
    // Pass-through all attributes (for debugging)
    vNormal = mat3(transpose(inverse(model))) * aNormal; //better calculate this  "mat3(transpose(inverse(model)))" part on a cpu and then pass a a uniform
    vTexCoords = aTexCoords;
    
    gl_Position = projection * view * model * vec4(aPosition, 1.0);

    vFragPos = vec3(model * vec4(aPosition, 1.0));
    vViewPos = viewPos;
}
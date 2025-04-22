#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
in float TexIndex;

uniform sampler2D uTextures[16];

void main()
{
	// Sample the texture
    vec4 texColor = texture(uTextures[int(TexIndex)], TexCoord);
    
    FragColor = ourColor * texColor;
}
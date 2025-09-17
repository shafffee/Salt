#version 330 core

in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vFragPos;
in vec3 vViewPos;

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
}; 

uniform Material material;

void main()
{

    vec4 lightColor = vec4(1, 1, 1, 1);
    
    vec3 lightPos = vec3(0.0, 0.0, 0.0);
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vFragPos); 

    //diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    //ambient
    vec4 amb = lightColor;
    //specular
    vec3 viewDir = normalize(vViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess*128);

    
    //vec3 ambient  = light.ambient * material.ambient;
    //vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    //vec3 specular = light.specular * (spec * material.specular);  

    vec4 ambient  = 0.2 * texture(material.texture_diffuse1, vTexCoords) * amb;
    vec4 diffuse  = 0.8 * texture(material.texture_diffuse1, vTexCoords) * diff;
    vec4 specular = 1.0 * texture(material.texture_specular1, vTexCoords)*spec;
    
    FragColor = ambient + diffuse + specular;
    FragColor.a = 1.0;
    FragColor.b = 1.0;

    FragColor = texture(material.texture_diffuse1, vTexCoords);
}
#include "Model.h"

void Model::Draw(salt::Shader &shader)
{   
    for(unsigned int i = 0; i < meshes.size(); i++){
        //salt::Logging::Error(std::to_string(i));
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        salt::Logging::Error("Assimp::");
        salt::Logging::Error(import.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}  

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates

        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);  

        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *aimaterial = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(aimaterial, 
                                        aiTextureType_DIFFUSE);

        //the texture in material is diffuse texture now
        if(diffuseMaps.size()>0) material.texture = diffuseMaps[0];

    }

    return Mesh(vertices, indices, material);
}  


std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString aipath;
        mat->GetTexture(type, i, &aipath);
        /*
        some models were broken and were giwing path like this:
        [ERROR]         Failed to load texture: ./Salt/res/models/container/C:\Users\Jaroslav\Documents\TS_Models\Container\textures_container\Container_DiffuseMap.jpg
        so i cut it
        */
        
        std::string path = aipath.C_Str();
        if(path.find_last_of("/\\")!=std::string::npos){
            path = path.substr(path.find_last_of('/\\')+1);
        }

        
        textures.push_back(Texture(directory+"/"+path));
    }
    return textures;
}  
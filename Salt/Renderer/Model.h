#pragma once

#include "Shader.h"
#include <string>
#include <vector>
#include "Mesh.h"
#include "Texture.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace salt{
class Renderer;
}

class Model 
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }	
    private:
        Model(){};

        void Draw(salt::Shader &shader);
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        //functions to load model from file
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);

        friend class salt::Renderer;
        friend class Sprite;
};
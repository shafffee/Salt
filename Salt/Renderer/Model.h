#pragma once

#include "Shader.h"
#include <string>
#include <vector>
#include "Mesh.h"
#include "Texture.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//to use Euler angles. mb need to move to quads after
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

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

        void setPosition(const glm::vec3& position){
            this->position = position;
            updateTransformationMatrix();
        }
        void setScale(const glm::vec3& scale){
            this->scale = scale;
            updateTransformationMatrix();
        }
        void setRotation(const glm::vec3& euler_angles){
            this->euler_angles=euler_angles;
            updateTransformationMatrix();
        }

        glm::mat4 getTransformationMatrix(){
            return transformation;
        }
        //no setTransformationMatrix because it will require recallc of pos, scale and rot and it may not be just these transforms

    private:

        glm::mat4 transformation = glm::mat4(1.0f); // this is updated on setPosition, setRotation, etc

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
        glm::vec3 euler_angles = glm::vec3(0.0f); // in degrees

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


        void updateTransformationMatrix(){
            // Position matrix (translation)
            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
            
            // Rotation Matrix from euler
            glm::mat4 rotationMatrix = glm::eulerAngleXYZ(
                glm::radians(euler_angles.x),
                glm::radians(euler_angles.y),
                glm::radians(euler_angles.z)
            );
            
            // Scale matrix
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
            
            //Matrix multiplication
            transformation =  translationMatrix * rotationMatrix * scaleMatrix;
        }

        friend class salt::Renderer;
        friend class Sprite;
        friend class Text;
};
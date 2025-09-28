#pragma once

#include <string>
#include <vector>
#include "Model.h"

namespace salt{
class Renderer;
}

class Sprite: public Model
{
    public:
        Sprite(char *texture_path)
        {
            //creating rect
            std::vector<Vertex> vertices;
            vertices.push_back({
                {0.0f, 0.0f, 0.0f},  //pos
                {0.0f, 0.0f, 1.0f},  //normal
                {0.0f, 0.0f}         //tex cords
            });
            vertices.push_back({
                {0.0f, 1.0f, 0.0f},  //pos
                {0.0f, 0.0f, 1.0f},  //normal
                {0.0f, 1.0f}         //tex cords
            });
            vertices.push_back({
                {1.0f, 1.0f, 0.0f},  //pos
                {0.0f, 0.0f, 1.0f},  //normal
                {1.0f, 1.0f}         //tex cords
            });
            vertices.push_back({
                {1.0f, 0.0f, 0.0f},  //pos
                {0.0f, 0.0f, 1.0f},  //normal
                {1.0f, 0.0f}         //tex cords
            });

            std::vector<unsigned int> indices = {0,1,2,0,2,3};

            //setting material
            Material mat(
                {1.0f,1.0f,1.0f,1.0f},  //white color
                Texture(texture_path)   //texture
            );

            //adding mesh (rect with texture)
            Model::meshes.push_back(Mesh(vertices, indices, mat));
        }	
    private:
        void Draw(salt::Shader &shader);

        friend class salt::Renderer;
};
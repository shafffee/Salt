#pragma once

#include <string>
#include <vector>
#include "Model.h"
#include "Font.h"


namespace salt{
class Renderer;
}

class Text: public Model
{
    public:
        Text()
        {
        }

        Text(const std::string& str, Font font, const glm::vec4& color = {1,1,1,1})
        {
            this->str = str;
            this->font = font;
            this->color = color;
            regenerateModel();
        }

        void setFont(Font font){
            if(this->font != font){
                changeFont(font);
            }
        }
        void setString(const std::string& str){
            if(this->str != str){
                changeStr(str);
            }
        }

        void setColor(const glm::vec4& color){
            if(this->color != color){
                changeColor(color);
            }
        }

    private:
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f,1.0f);

        Font font;
        std::string str;

        void regenerateModel(){
            //clean all
            Model::meshes.clear();


            //used to make each letter 1x1 size (not exactly, but sizes are close)
            float scale = 1.0f/font.height;

            float x=0;
            float y=0;

            // iterate through all characters
            for (char c: str)
            {
                Character ch = font.getChar(c);

                float xpos = (x + ch.Bearing.x)*scale;
                float ypos = (y - (ch.Size.y - ch.Bearing.y))*scale;
        
                float w = ch.Size.x*scale;
                float h = ch.Size.y*scale;


                /*
                salt::Logging::Debug(std::to_string(xpos));
                salt::Logging::Debug(std::to_string(ypos));
                salt::Logging::Debug(std::to_string(w));
                salt::Logging::Debug(std::to_string(h));
                salt::Logging::Debug("-------------------------");
                */

                //creating rect
                std::vector<Vertex> vertices;
                vertices.push_back({
                    {xpos, ypos + h, 0.0f},  //pos
                    {0.0f, 0.0f, 1.0f},  //normal
                    {0.0f, 0.0f}         //tex cords
                });
                vertices.push_back({
                    {xpos, ypos, 0.0f},  //pos
                    {0.0f, 0.0f, 1.0f},  //normal
                    {0.0f, 1.0f}         //tex cords
                });
                vertices.push_back({
                    {xpos + w, ypos, 0.0f},  //pos
                    {0.0f, 0.0f, 1.0f},  //normal
                    {1.0f, 1.0f}         //tex cords
                });
                vertices.push_back({
                    {xpos + w, ypos + h, 0.0f},  //pos
                    {0.0f, 0.0f, 1.0f},  //normal
                    {1.0f, 0.0f}         //tex cords
                });

                std::vector<unsigned int> indices = {0,1,2,0,2,3};

                //setting material
                Material mat(
                    color,  //white color
                    ch.texture   //texture
                );

                //adding mesh (rect with texture)
                Model::meshes.push_back(Mesh(vertices, indices, mat));
                x += ch.Advance >> 6;
            }
        };

        void changeFont(Font new_font){
            font = new_font;
            //regenerate model because scale is dependent on font size
            regenerateModel();
        };

        void changeStr(const std::string& new_str){
            str = new_str;
            regenerateModel();
        };

        //optimization
        void changeColor(const glm::vec4& new_color){
            this->color = new_color;
            //regenerateModel();
            for(int i=0; i< Model::meshes.size();i++){
                Model::meshes[i].material.color=color;
            }
        };

        void Draw(salt::Shader &shader);

        friend class salt::Renderer;
};
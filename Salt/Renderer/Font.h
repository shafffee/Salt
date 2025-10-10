#pragma once
#include <string>

#include "ft2build.h"
#include FT_FREETYPE_H 


    struct Character {
        Texture texture;  //glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

class Font;

class Fonts{

public:
    //static void passTextureToShader(const Texture& texture, salt::Shader &shader, const std::string& field_name);
    inline static void Init(){
        /*
        if (FT_Init_FreeType(&ft))
        {
            salt::Logging::ERROR("ERROR::FREETYPE: Could not init FreeType Library");
            return;
        }
        */
    };

private:

    inline static uint64_t fonts_loaded = 0;

    struct FontInstance{
        std::string filepath = "";
        int width = 0;      //0-auto based on height
        int height = 0;     //0-auto based on width

        std::map<char, Character> Characters;

        void loadFromFile(const std::string& filepath, int height=48){
            loadFromFile(filepath, 0, height);
        }
        void loadFromFile(const std::string& filepath, int width, int height){

            this->filepath = filepath;
            
            FT_Library ft;
            if (FT_Init_FreeType(&ft))
            {
                salt::Logging::Error("ERROR::FREETYPE: Could not init FreeType Library");
                return;
            }

            FT_Face face;
            int err = FT_New_Face(ft, filepath.c_str(), 0, &face);
            if (err)
            {
                salt::Logging::Error("ERROR::FREETYPE: Failed to load font. Error: "+std::to_string(err));  
                return;
            }

            FT_Set_Pixel_Sizes(face, width, height); 

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
            for (unsigned char c = 0; c < 128; c++)
            {
                // load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    salt::Logging::Error("ERROR::FREETYTPE: Failed to load Glyph");
                    continue;
                }

                std::string tex_name = "font:"+filepath+"_"+std::to_string(width)+"x"+std::to_string(height)+"|char:"+std::to_string(c);
                // generate texture
                Texture tex;
                if(face->glyph->bitmap.buffer){ //for space ' ' it is null and was causing some errors in textures
                    tex = Texture(face->glyph->bitmap.buffer,
                            face->glyph->bitmap.width,
                            face->glyph->bitmap.rows,
                            1,
                            tex_name);
                }else{ //for space just send an empty texture (or for any broken symbol)
                }

                // now store character for later use
                Character character = {
                    tex, 
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    (unsigned)face->glyph->advance.x
                };
                Characters.insert(std::pair<char, Character>(c, character));
            }

            FT_Done_Face(face);
            FT_Done_FreeType(ft);
        
        };

        Character getChar(char c){
            if(Characters.count(c))
                return Characters[c];
            //salt::Logging::Error("Characters array does not contain \'"+c+"\'. Font: "+filepath);
            salt::Logging::Error("Characters array does not contain letter. Font: "+filepath);
            return Character();
        };


    };


        inline static uint64_t FontFromFile(std::string filepath, int width, int height){
            //if texture with the same label is already loaded
            //if(name_id_map.count()){
            //    return name_id_map[name];
            //}
            //else

            std::string name = filepath;

            fonts_loaded+=1;
            uint32_t id = fonts_loaded;

            FontInstance fi;
            fi.filepath = filepath;
            fi.width = width;
            fi.height = height;
            fi.loadFromFile(filepath, width, height);

            name_id_map.insert({name, id});
            id_instance_map.insert({id, fi});

            return id;
        }


    // map name - id
    inline static std::map<std::string, uint32_t> name_id_map;
    inline static std::map<uint32_t, FontInstance> id_instance_map;

    friend class Font;
};




struct Font{
    uint64_t id = 0;
    int width = 0;      //0-auto based on height
    int height = 0;     //0-auto based on width

    Font(){};

    Font(std::string filepath, int width =0, int height = 48): width(width), height(height){
        id = Fonts::FontFromFile(filepath, width, height);
    };

    bool isNull(){
        return id == 0;
    } 

    Character getChar(char c){
        return Fonts::id_instance_map[id].getChar(c);
    }
};
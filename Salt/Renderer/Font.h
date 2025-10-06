#pragma once
#include <string>

struct Font{
    std::string filepath = "";
    std::int width = 0;      //0-auto based on height
    std::int height = 0;     //0-auto based on width

    Font(std::string filepath="", int width =0, int height = 48): filepath(filepath), width(width), height(height){};

    bool isNull(){
        return filepath == "";
    } 
};

class Fonts{

public:
    //static void passTextureToShader(const Texture& texture, salt::Shader &shader, const std::string& field_name);
    inline static void Init(){
        if (FT_Init_FreeType(&ft))
        {
            salt::Logging::ERROR("ERROR::FREETYPE: Could not init FreeType Library");
            return;
        }
    };

private:

    FT_Library ft;

    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    struct FontInstance{
        std::string filepath = "";
        std::int width = 0;      //0-auto based on height
        std::int height = 0;     //0-auto based on width

        FT_Face face;

        std::map<char, Character> Characters;

        void loadFromFile(const std::string& filepath, const FT_Library& ft){
            if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
            {
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
                return -1;
            }
            FT_Set_Pixel_Sizes(face, width, height);
        };

        void getChar();

    };

    // map filename - id
    inline static std::map<std::string, uint32_t> name_id_map;
    inline static std::map<uint32_t, FontInstance> id_instance_map;
};
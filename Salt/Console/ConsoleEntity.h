#include "ECS.h"
#include "UCSL.h"

#define CONSOLE_FONT "./Salt/res/fonts/JetBrains_Mono/static/JetBrainsMono-Medium.ttf"
#define CONSOLE_FONT_RES 128
#define CONSOLE_FONT_SIZE 0.1



void s_message(salt::ECS::Entity e)
{
     //e.component<c_transformation>(C_TRANSFORMATION)->y += BULLET_SPEED;
     //if( e.component<c_transformation>(C_TRANSFORMATION)->y>1.0f ) e.destroy();
}

inline static salt::ECS::System S_MESSAGE(&s_message, C_TRANSFORMATION);



salt::ECS::Entity createConsoleMessage(const std::string& msg){
    salt::ECS::Entity message( 
                            C_MODEL  | C_TRANSFORMATION, 
                            S_DRAW   | S_MESSAGE
    );

    //pos
    message.component<c_transformation>(C_TRANSFORMATION)->x = -1.0;
    message.component<c_transformation>(C_TRANSFORMATION)->y = -1.0+CONSOLE_FONT_SIZE;
    message.component<c_transformation>(C_TRANSFORMATION)->z = -1;

    //size
    message.component<c_transformation>(C_TRANSFORMATION)->width = CONSOLE_FONT_SIZE;
    message.component<c_transformation>(C_TRANSFORMATION)->height = CONSOLE_FONT_SIZE;

    //sprite
    message.component<c_model>(C_MODEL)->text = new Text(msg, Font(CONSOLE_FONT,CONSOLE_FONT_RES));
    message.component<c_model>(C_MODEL)->layer = 100;

    return message;
}
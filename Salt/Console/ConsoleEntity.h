#pragma once
#include "ECS.h"
#include "UCSL.h"

#define CONSOLE_FONT "./Salt/res/fonts/JetBrains_Mono/static/JetBrainsMono-Medium.ttf"
#define CONSOLE_FONT_RES 128
#define CONSOLE_FONT_SIZE 0.05

#define MESSAGE_LIFE_TIME       200
#define MESSAGE_DISSAPEAR_TIME  100

struct c_message {
public:
    glm::vec3 color;
    int ticks = 0;
};
inline static salt::ECS::Component<c_message> C_MESSAGE;

inline static void s_message(salt::ECS::Entity e)
{
     e.component<c_message>(C_MESSAGE)->ticks += 1;
     int ticks = e.component<c_message>(C_MESSAGE)->ticks;
     glm::vec3 color = e.component<c_message>(C_MESSAGE)->color;

     if( ticks>MESSAGE_LIFE_TIME){
        float a = 1.0f*(MESSAGE_DISSAPEAR_TIME-(ticks-MESSAGE_LIFE_TIME))/MESSAGE_DISSAPEAR_TIME;
        if(e.component<c_model>(C_MODEL)->text) e.component<c_model>(C_MODEL)->text->setColor({color.r,color.g,color.b,a});
     }
     if( ticks>MESSAGE_LIFE_TIME+MESSAGE_DISSAPEAR_TIME) e.destroy();
}

inline static salt::ECS::System S_MESSAGE(&s_message, C_MESSAGE | C_MODEL);



inline static salt::ECS::Entity createConsoleMessage(const std::string& msg, const glm::vec3& color = {1,1,1}){
    salt::ECS::Entity message( 
                            C_MODEL  | C_TRANSFORMATION | C_MESSAGE, 
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
    message.component<c_model>(C_MODEL)->text = new Text(msg, Font(CONSOLE_FONT,CONSOLE_FONT_RES), {color.r,color.g,color.b,1});
    message.component<c_model>(C_MODEL)->layer = 100;

    //color
    message.component<c_message>(C_MESSAGE)->color = color;

    return message;
}
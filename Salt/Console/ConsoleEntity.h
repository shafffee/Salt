#pragma once
#include "ECS.h"
#include "UCSL.h"
#include "Console.h"
#include <iostream>

#define CONSOLE_FONT "./Salt/res/fonts/JetBrains_Mono/static/JetBrainsMono-Medium.ttf"
#define CONSOLE_FONT_RES 128
#define CONSOLE_FONT_SIZE 0.05

#define MESSAGE_LIFE_TIME       200
#define MESSAGE_DISSAPEAR_TIME  100

struct c_message {
public:
    glm::vec3 color;
    int string_from_bottom = 0;
    int ticks = 0;
};
inline static salt::ECS::Component<c_message> C_MESSAGE;

static void s_message(salt::ECS::Entity e){

    e.component<c_transformation>(C_TRANSFORMATION)->y = -1.0+CONSOLE_FONT_SIZE*(e.component<c_message>(C_MESSAGE)->string_from_bottom+1);

    e.component<c_message>(C_MESSAGE)->ticks += 1;
    int ticks = e.component<c_message>(C_MESSAGE)->ticks;
    glm::vec3 color = e.component<c_message>(C_MESSAGE)->color;

    if( ticks>MESSAGE_LIFE_TIME){
       float a = 1.0f*(MESSAGE_DISSAPEAR_TIME-(ticks-MESSAGE_LIFE_TIME))/MESSAGE_DISSAPEAR_TIME;
       if(e.component<c_model>(C_MODEL)->text) e.component<c_model>(C_MODEL)->text->setColor({color.r,color.g,color.b,a});
    }
    if( ticks>MESSAGE_LIFE_TIME+MESSAGE_DISSAPEAR_TIME) e.destroy();
};
inline static salt::ECS::System S_MESSAGE(&s_message, C_MESSAGE | C_MODEL);


inline static salt::ECS::Entity createConsoleMessage(const std::string& msg, const glm::vec3& color = {1,1,1}){
    salt::ECS::Entity message( 
                            C_MODEL  | C_TRANSFORMATION | C_MESSAGE, 
                            S_DRAW   | S_MESSAGE
    );

    //pos
    message.component<c_transformation>(C_TRANSFORMATION)->x = -1.0;
    message.component<c_transformation>(C_TRANSFORMATION)->y = -1.0+CONSOLE_FONT_SIZE*(message.component<c_message>(C_MESSAGE)->string_from_bottom+1);
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

struct c_console {
public:
    std::vector<salt::ECS::Entity> messages;
};
inline static salt::ECS::Component<c_console> C_CONSOLE;

static void s_console(salt::ECS::Entity e){

    for(int i = salt::Console::history.size()-1; i>=0;i--){
        if(salt::Console::history[i].time_created != salt::Ticks::current()-1) break;
        std::cout<<salt::Console::history[i].message<<std::endl;
        e.component<c_console>(C_CONSOLE)->messages.push_back(createConsoleMessage(salt::Console::history[i].message, salt::Console::history[i].color));
    }

    
    //delete expired messages
    std::cout<<e.component<c_console>(C_CONSOLE)->messages.size()<<"\t";
    for(int i=0;i<e.component<c_console>(C_CONSOLE)->messages.size(); i++){
        if(e.component<c_console>(C_CONSOLE)->messages[i].isNull()){
            std::cout<<"deleting "<<i<<"\t";
            e.component<c_console>(C_CONSOLE)->messages.erase(e.component<c_console>(C_CONSOLE)->messages.begin()+i);
            i-=1;
        }
    }
    std::cout<<e.component<c_console>(C_CONSOLE)->messages.size()<<std::endl;

    

    //adjust strings
    for(int i=0;i<e.component<c_console>(C_CONSOLE)->messages.size(); i++){
        int string_from_bottom = e.component<c_console>(C_CONSOLE)->messages.size()-i-1;
        e.component<c_console>(C_CONSOLE)->messages[i].component<c_message>(C_MESSAGE)->string_from_bottom = string_from_bottom;
    }
    
};
inline static salt::ECS::System S_CONSOLE(&s_console, C_CONSOLE);


inline static salt::ECS::Entity createConsoleEntity(){
    salt::ECS::Entity console( 
                            C_CONSOLE, 
                            S_CONSOLE
    );
    return console;
}



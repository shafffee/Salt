#include "ECS.h"

#define CONSOLE_FONT "./Salt/res/fonts/JetBrains_Mono/static/JetBrainsMono-Medium.ttf"
#define CONSOLE_FONT_RES 128
#define CONSOLE_FONT_SIZE 0.1



void s_message(salt::ECS::Entity e)
{
     e.component<c_transformation>(C_TRANSFORMATION)->y += BULLET_SPEED;
     if( e.component<c_transformation>(C_TRANSFORMATION)->y>1.0f ) e.destroy();
}

inline static salt::ECS::System S_MESSAGE(&s_message, C_TRANSFORMATION);



salt::ECS::Entity createConsoleMessage(float x, float y){
    salt::ECS::Entity message( 
                            C_MODEL  | C_TRANSFORMATION, 
                            S_DRAW   | S_BULLET
    );

    //pos
    bullet.component<c_transformation>(C_TRANSFORMATION)->x = x-0.5*BULLET_SIZE_X;
    bullet.component<c_transformation>(C_TRANSFORMATION)->y = y-0.5*BULLET_SIZE_Y;
    bullet.component<c_transformation>(C_TRANSFORMATION)->z = -1;


    //size
    bullet.component<c_transformation>(C_TRANSFORMATION)->width = BULLET_SIZE_X;
    bullet.component<c_transformation>(C_TRANSFORMATION)->height = BULLET_SIZE_Y;

    //sprite
    bullet.component<c_model>(C_MODEL)->sprite = new Sprite("./res/kenney_pixelshmup/Ships/ship_0022.png");
    bullet.component<c_model>(C_MODEL)->layer = 1;

    return bullet;
}
#include "Salt.h"
#include "Bullet.h"


#define PLAYER_SPEED 0.02
#define PLAYER_SIZE  0.5f


void s_controls(salt::ECS::Entity e)
{
    if (salt::Input::IsKeyPressed(SALT_KEY_A)) e.component<c_transformation>(C_TRANSFORMATION)->x -= PLAYER_SPEED;
    if (salt::Input::IsKeyPressed(SALT_KEY_D)) e.component<c_transformation>(C_TRANSFORMATION)->x += PLAYER_SPEED;
    if (salt::Input::IsKeyPressed(SALT_KEY_W)) e.component<c_transformation>(C_TRANSFORMATION)->y += PLAYER_SPEED;
    if (salt::Input::IsKeyPressed(SALT_KEY_S)) e.component<c_transformation>(C_TRANSFORMATION)->y -= PLAYER_SPEED;
}
inline static salt::ECS::System S_CONTROLS(&s_controls, C_TRANSFORMATION);


//for easy creation of the player
salt::ECS::Entity createPlayerEntity(){
    salt::ECS::Entity player( 
                              C_MODEL  | C_TRANSFORMATION, 
                              S_DRAW   | S_CONTROLS | S_BULLET_SHOOTER
    );

    //pos
    player.component<c_transformation>(C_TRANSFORMATION)->x = 0;
    player.component<c_transformation>(C_TRANSFORMATION)->y = 0;
    player.component<c_transformation>(C_TRANSFORMATION)->z = -1;


    //size
    player.component<c_transformation>(C_TRANSFORMATION)->width = PLAYER_SIZE;
    player.component<c_transformation>(C_TRANSFORMATION)->height = PLAYER_SIZE;

    //sprite
    player.component<c_model>(C_MODEL)->sprite = new Sprite("./res/kenney_pixelshmup/Ships/ship_0001.png");
    player.component<c_model>(C_MODEL)->layer = 0;

    return player;
}
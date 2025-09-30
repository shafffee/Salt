#include "Salt.h"
#include "Components.h"
#include "Systems.h"
#include "Bullet.h"


#define PLAYER_SPEED 0.02
#define PLAYER_SIZE  0.5f

//on update player
void player_sys(salt::ECS::Entity e)
{
    //move cprite to character pos
    e.component<sprite_comp>(SPRITE_COMP)->x = e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->x;
    e.component<sprite_comp>(SPRITE_COMP)->y = e.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->y;
}

inline static salt::ECS::System PLAYER_SYS(&player_sys, SPRITE_COMP | CHAR2DCONTROLS_COMP);

//for easy creation of the player
salt::ECS::Entity createPlayerEntity(){
    salt::ECS::Entity player( 
                              SPRITE_COMP  | CHAR2DCONTROLS_COMP, 
                              SPRITE_SYS   | CHAR2DCONTROLS_SYS | PLAYER_SYS | BULLET_SHOOTER_SYS
    );

    //position
    player.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->x = 0;
    player.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->y = 0;
    //speed
    player.component<char2Dcontrols_comp>(CHAR2DCONTROLS_COMP)->speed = PLAYER_SPEED;

    //size
    player.component<sprite_comp>(SPRITE_COMP)->width = PLAYER_SIZE;
    player.component<sprite_comp>(SPRITE_COMP)->height = PLAYER_SIZE;

    //sprite
    player.component<sprite_comp>(SPRITE_COMP)->sprite = new Sprite("./res/kenney_pixelshmup/Ships/ship_0001.png");

    return player;
}
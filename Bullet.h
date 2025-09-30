#include "Salt.h"
#include "Components.h"
#include "Systems.h"

#define BULLET_SPEED 0.1
#define BULLET_SIZE_X  0.1f
#define BULLET_SIZE_Y  0.1f


//fly upward
void bullet_fly_sys(salt::ECS::Entity e)
{
    float speed = e.component<bullet_comp>(BULLET_COMP)->speed;
    e.component<bullet_comp>(BULLET_COMP)->y += speed;
}
inline static salt::ECS::System BULLET_FLY_SYS(&bullet_fly_sys, BULLET_COMP);


//on update bullet
void bullet_sys(salt::ECS::Entity e)
{
    //move sprite to bullet pos
    e.component<sprite_comp>(SPRITE_COMP)->sprite->setPosition({
        e.component<bullet_comp>(BULLET_COMP)->x,
        e.component<bullet_comp>(BULLET_COMP)->y,
        -1
    });
}

inline static salt::ECS::System BULLET_SYS(&bullet_sys, SPRITE_COMP | BULLET_COMP);

//shoots bullet with the center on x, y
salt::ECS::Entity createBulletEntity(float x, float y){
    salt::ECS::Entity bullet( 
                              SPRITE_COMP  | BULLET_COMP, 
                              SPRITE_SYS   | BULLET_FLY_SYS | BULLET_SYS
    );

    //position
    bullet.component<bullet_comp>(BULLET_COMP)->x = x - 0.5*BULLET_SIZE_X;
    bullet.component<bullet_comp>(BULLET_COMP)->y = y - 0.5*BULLET_SIZE_Y;

    //speed
    bullet.component<bullet_comp>(BULLET_COMP)->speed = BULLET_SPEED;

    //size
    bullet.component<sprite_comp>(SPRITE_COMP)->width = BULLET_SIZE_X;
    bullet.component<sprite_comp>(SPRITE_COMP)->height = BULLET_SIZE_Y;

    //sprite
    bullet.component<sprite_comp>(SPRITE_COMP)->sprite = new Sprite("./res/kenney_pixelshmup/Ships/ship_0022.png");

    return bullet;
}


//shoot bullets on space from the top middle of the SPRITE
void bullet_shooter_sys(salt::ECS::Entity e)
{
    if (salt::Input::IsKeyPressed(SALT_KEY_SPACE)){
        float x = e.component<sprite_comp>(SPRITE_COMP)->x + 0.5*e.component<sprite_comp>(SPRITE_COMP)->width;
        float y = e.component<sprite_comp>(SPRITE_COMP)->y;
        createBulletEntity(x, y);
    }

}
inline static salt::ECS::System BULLET_SHOOTER_SYS(&bullet_shooter_sys, SPRITE_COMP);
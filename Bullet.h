#include "Salt.h"

#define BULLET_SPEED 0.1
#define BULLET_SIZE_X  0.1f
#define BULLET_SIZE_Y  0.1f



//fly upward and delete if out of the screen
void s_bullet(salt::ECS::Entity e)
{
     e.component<c_transformation>(C_TRANSFORMATION)->y += BULLET_SPEED;
     if( e.component<c_transformation>(C_TRANSFORMATION)->y>1.0f ) e.destroy();
}

inline static salt::ECS::System S_BULLET(&s_bullet, C_TRANSFORMATION);

//shoots bullet with the center on x, y
salt::ECS::Entity createBulletEntity(float x, float y){
    salt::ECS::Entity bullet( 
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


//shoot bullets on space from the top middle
void s_bullet_shooter(salt::ECS::Entity e)
{
    if (salt::Input::IsKeyPressed(SALT_KEY_SPACE)){
        float x =  e.component<c_transformation>(C_TRANSFORMATION)->x + 0.5*e.component<c_transformation>(C_TRANSFORMATION)->width;
        float y =  e.component<c_transformation>(C_TRANSFORMATION)->y+e.component<c_transformation>(C_TRANSFORMATION)->height;
        createBulletEntity(x, y);
    }
}
inline static salt::ECS::System S_BULLET_SHOOTER(&s_bullet_shooter, C_TRANSFORMATION);
#pragma once
#include "ECS.h"
#include "UCSL.h"

#define FPS_COUNTER_FONT "./Salt/res/fonts/JetBrains_Mono/static/JetBrainsMono-Medium.ttf"
#define FPS_COUNTER_FONT_RES 128
#define FPS_COUNTER_FONT_SIZE 0.05


#define RECORD_FRAMES 120

struct c_fps_counter {
public:
    //clock for fps counter
    int fps_measure_delta_ms = 300;
    std::chrono::system_clock::time_point fps_count_end_time = std::chrono::system_clock::now()+std::chrono::milliseconds(fps_measure_delta_ms);
    int fps_count = 0;
    std::chrono::system_clock::time_point prev_frames[RECORD_FRAMES];
};
inline static salt::ECS::Component<c_fps_counter> C_FPS_COUNTER;


static void s_fps_counter(salt::ECS::Entity e){

    int& fps_measure_delta_ms = e.component<c_fps_counter>(C_FPS_COUNTER)->fps_measure_delta_ms;
    std::chrono::system_clock::time_point& fps_count_end_time = e.component<c_fps_counter>(C_FPS_COUNTER)->fps_count_end_time;
    int& fps_count = e.component<c_fps_counter>(C_FPS_COUNTER)->fps_count;

    for(int i = 0; i<RECORD_FRAMES-1; i++){
        e.component<c_fps_counter>(C_FPS_COUNTER)->prev_frames[i] =   e.component<c_fps_counter>(C_FPS_COUNTER)->prev_frames[i+1];
    }
     e.component<c_fps_counter>(C_FPS_COUNTER)->prev_frames[RECORD_FRAMES-1] = std::chrono::system_clock::now();

    //if( std::chrono::microseconds(e.component<c_fps_counter>(C_FPS_COUNTER)->prev_frames[0])>0  ){
    if(e.component<c_model>(C_MODEL)->text) e.component<c_model>(C_MODEL)->text->setString( "FPS: "  +  std::to_string( int( 1000000.0/std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-e.component<c_fps_counter>(C_FPS_COUNTER)->prev_frames[0]).count()*RECORD_FRAMES  )  )  );
    //}

    /*
    //fps counter
    if(std::chrono::system_clock::now() > fps_count_end_time){
        if(e.component<c_model>(C_MODEL)->text) e.component<c_model>(C_MODEL)->text->setString(std::to_string(int(fps_count * (1000.0/fps_measure_delta_ms))));
        fps_count = 0;
        fps_count_end_time = std::chrono::system_clock::now()+std::chrono::milliseconds(fps_measure_delta_ms);
    }
    fps_count+=1;
    */



    //glm::vec3 color = e.component<c_message>(C_MESSAGE)->color;
    //if(e.component<c_model>(C_MODEL)->text) e.component<c_model>(C_MODEL)->text->setColor({color.r,color.g,color.b,a});
    
};
inline static salt::ECS::System S_FPS_COUNTER(&s_fps_counter, C_FPS_COUNTER | C_MODEL);


inline static salt::ECS::Entity createFPSCounter(){
    salt::ECS::Entity fps_counter( 
                            C_MODEL  | C_TRANSFORMATION | C_FPS_COUNTER, 
                            S_DRAW | S_FPS_COUNTER
    );

    //pos
    fps_counter.component<c_transformation>(C_TRANSFORMATION)->y = 1.0-FPS_COUNTER_FONT_SIZE;
    fps_counter.component<c_transformation>(C_TRANSFORMATION)->x = 1.0-7*FPS_COUNTER_FONT_SIZE;
    fps_counter.component<c_transformation>(C_TRANSFORMATION)->z = -1;

    //size
    fps_counter.component<c_transformation>(C_TRANSFORMATION)->width = FPS_COUNTER_FONT_SIZE;
    fps_counter.component<c_transformation>(C_TRANSFORMATION)->height = FPS_COUNTER_FONT_SIZE;

    //sprite
    fps_counter.component<c_model>(C_MODEL)->text = new Text("FPS", Font(FPS_COUNTER_FONT,FPS_COUNTER_FONT_RES), {1,1,1,1});
    fps_counter.component<c_model>(C_MODEL)->layer = 100;

    return fps_counter;
}
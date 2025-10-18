#pragma once
#include "stdint.h"

namespace salt{

    class Ticks{
    public:
        //goes to next tick
        inline static void Update(){current_tick+=1;};
        //returns current tick
        inline static uint64_t current(){return current_tick;};

    private:
        inline static uint64_t current_tick = 0;

    };

}
#pragma once

#include "Entity.h"
#include "Component.h"
#include "ECS_params.h"
#include "System.h"

namespace salt {
    namespace ECS {

        static void Init() {};

        static void Update() {
            //for all allocated entities
            for (uint64_t e = 0;e < ENTITIES_MAX;e++) {
                if (salt::ECS::EntityPack::_is_allocated[e]) {
                    //for all aded systems
                    for (uint64_t s = 0;s < SYSTEMS_MAX;s++) {
                        //if entity has system, run
                        if (EntityPack::_entities[e]._systems[s]==1) {
                            //passing an entity pointer to function
                            SystemPack::_systems[s].run(Entity(e));
                        }
                    }
                }
            }
        }

    }
}
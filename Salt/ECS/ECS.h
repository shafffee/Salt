#pragma once

#include "Entity.h"
#include "Component.h"
#include "ECS_params.h"
#include "System.h"

namespace salt {
    namespace ECS {

        static void Init() {};

        static void Update() {

            std::vector<std::pair<uint64_t, int>> entitiesToProcess;
            for (const auto& e : salt::ECS::EntityPack::id_index_map) {
                entitiesToProcess.push_back(e);
            }

            //for all allocated entities
            for (auto e: entitiesToProcess) {
                //for all aded systems
                for (uint64_t s = 0;s < SYSTEMS_MAX;s++) {
                        //if entity has system, run
                        if (EntityPack::_entities[e.second]._systems[s]==1) {
                            //passing an entity pointer to function
                            SystemPack::_systems[s].run(Entity(e.first));
                        }
                }
            }
        }

    }
}
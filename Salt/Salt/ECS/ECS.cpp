#include "ECS.h"

#include "Component/ComponentPack.h"
#include "ECS_params.h"
#include <bitset>
#include "System/SystemPack.h"
#include "Entity/EntityPack.h"

namespace salt {
	EntityPack ECS::entities;
	ComponentPack ECS::components;
	SystemPack ECS::systems;

	void ECS::Init()
	{

	}

	void ECS::Update()
	{
		
		for (uint16_t e = 0;e < ENTITIES_MAX;e++) {
			for (uint16_t s = 0;s < SYSTEMS_MAX;s++) {
				if (entities.getEntity(e) != nullptr) {
					if (entities.getEntity(e)->hasSystem(s))systems.getSystem(s)->run(e);
				}
			}
		}
		
	}
}
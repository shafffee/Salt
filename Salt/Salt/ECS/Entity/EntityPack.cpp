#include "EntityPack.h"
#include "../Component/ComponentPack.h"

namespace salt {
    uint16_t EntityPack::addEntity(Entity e, std::string name) {
		uint16_t id = entities.addItem(e, name);
		//creating actual component instances
		for (int c = 0; c < COMPONENTS_MAX;c++) {
			if (e.hasComponent(c)) {
				ECS::components.addComponent(c, id);
			}
		}
		return id;
	};
}

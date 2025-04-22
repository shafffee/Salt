#pragma once

#include <map>
#include <string>
#include <stdint.h>

#include "Entity.h"
#include "DataTypes/DataTypes.h"
#include "ECS/ECS.h"


namespace salt {
	class EntityPack {
	private:
		NameID_Container<Entity, ENTITIES_MAX> entities;
	public:
		//add returns an id of the added entity
		uint16_t addEntity(Entity e, std::string name = "");

		//get Entity pointer
		inline Entity* getEntity(std::string name) { return entities.getItem(name); };
		inline Entity* getEntity(uint16_t id) { return entities.getItem(id); };

		//remove Entity
		inline void removeEntity(std::string name) { entities.removeItem(name); };
		inline void removeEntity(uint16_t id) { entities.removeItem(id); };

		//getSize
		inline uint16_t getMaxEntities() { return entities.getSize(); };

		//get entity id/name
		inline uint16_t getEntityId(std::string name) { return entities.getItemId(name); };
		inline uint16_t getEntityId(Entity* e) { return entities.getItemId(e); };
		inline std::string getEntityName(uint16_t id) { return entities.getItemName(id); };
	};
}
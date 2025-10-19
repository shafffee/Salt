#pragma once

#include <map>
#include <stdint.h>
#include <bitset>
#include "ECS_params.h"
#include "Component.h"
#include "System.h"


/*

MAJOR CHANGE: id is now unique, created id_index_map

*/

namespace salt {
	namespace ECS {



		/*
		----ENTITY INSTANCE----
		is TWO BITMASKS for
		components and systems
		-------------------
		*/

		class EntityInstance {
		private:
			std::bitset<COMPONENT_TYPES_MAX> _components;
			std::bitset<SYSTEMS_MAX> _systems;

			//constructor
			EntityInstance(std::bitset<COMPONENT_TYPES_MAX> components=0, std::bitset<SYSTEMS_MAX> systems=0) : _components(components), _systems(systems) {};

			// copy constructor
			EntityInstance& operator=(const EntityInstance& other) {
				this->_components = other._components;
				this->_systems = other._systems;
				return *this;
			};

			friend class Entity;
			friend class EntityPack;
			friend static void Update();
		};




		/*
		----ENTITY PACK----
		is a collection of entity instances.
		you can both DELETE and ADD entities

		entities are managed by entity ID (before it was index in the array+1, now id is unique)
		id 0 is reserved
		-------------------
		*/

		class EntityPack {
		private:

			inline static bool _is_allocated[ENTITIES_MAX];
			inline static EntityInstance _entities[ENTITIES_MAX];

			inline static uint64_t next_id = 0;
			inline static std::map<uint64_t, int> id_index_map;

			//adds entity and returns its slot
			inline static uint64_t RegisterEntityInstance(std::bitset<COMPONENT_TYPES_MAX> components, std::bitset<SYSTEMS_MAX> systems) {

				//searching for the first free slot
				uint64_t first_empty_slot = 0;
				while (first_empty_slot < ENTITIES_MAX && _is_allocated[first_empty_slot])first_empty_slot++;
				if (first_empty_slot >= ENTITIES_MAX) {
					Logging::Error("Entity can not be added. ENTITIES_MAX limit is being exeeded");
					return 0;
				}

				_is_allocated[first_empty_slot] = true;
				_entities[first_empty_slot] = EntityInstance(components, systems);
				
				next_id+=1;
				id_index_map.insert({next_id, first_empty_slot});
				return next_id; // starts from 1 to leave 0 for broken entities
			};
			//deletes entity (but actually just allows to override it if needed)
			inline static void DeleteEntityInstance(uint64_t id) {

				if(id_index_map.count(id)==0){
					Logging::Error("EntityInstance can not be deleted. I has not been created or has been deleted before");
					return;
				}

				uint64_t index = id_index_map[id]; //id to index

				_is_allocated[index] = false;
				id_index_map.erase(id);

				return;
			};
			inline static bool EntityWithIdExists(uint64_t id) {
				if(id_index_map.count(id)==0){
					return 0;
				}
				return 1;
			};

			inline static int getIndexInPack(uint64_t id) {

				if(id_index_map.count(id)==0){
					Logging::Error("Error in getIndexInPack. Entity has not been created or has been deleted before");
					return 0;
				}

				uint64_t index = id_index_map[id]; //id to index

				return index;
			};


			friend class Entity;
			friend class EntityInstance;
			friend class SystemInstance;
			friend static void Update();
		};

		//has an id starting from 1 (0 for error)
		class Entity {
		private:
			int64_t _id=0;
		public:
			bool isNull() {
				return (EntityPack::EntityWithIdExists(_id) == 0);
			}
			//creates entity instance
			Entity(std::bitset<COMPONENT_TYPES_MAX> components, std::bitset<SYSTEMS_MAX> systems) {
				//check if entity contains all the needed components for the systems
				for (int i = 0;i < SYSTEMS_MAX; i++) {
					if (systems[i] == 1 && !(salt::ECS::SystemPack::_systems[i]._required_components & ~components).none() ) {
						Logging::Error("System requires a component, but the entity does not have it");
						return;
					}
				}
				_id = EntityPack::RegisterEntityInstance(components, systems);
			}
			//used in manager to send entities to functions without actually creating the entity
			Entity(uint64_t id) {
				_id = id;
			}
			template<typename T>
			std::shared_ptr<T> component(salt::ECS::Component<T> c) {
				if (EntityPack::EntityWithIdExists(_id)==0) {
					// entity with id does not exist
					Logging::Error("Trying to get component of an entity that does not exist");
					return std::shared_ptr<T>(new T);	//TO PREVENT CRASH
					//return nullptr;
				}

				// Retrieve the shared_ptr<void> from the component pack
				auto& component_instance = salt::ECS::ComponentPack::_components[c._id_in_pack];
				// Cast it to a shared_ptr<std::map<...>> using static_pointer_cast
				auto map_ptr = std::static_pointer_cast<std::map<uint64_t, T>>(component_instance);
				// Access the element in the map and create a shared_ptr<T> that shares ownership
				T& element = (*map_ptr)[EntityPack::getIndexInPack(_id)];
				return std::shared_ptr<T>(map_ptr, &element); // Aliasing constructor
				//return component pointer
			};
			void destroy() {
				if (EntityPack::EntityWithIdExists(_id) == 0) {
					// entity with id does not exist;
					Logging::Warning("Trying to delete entity that does not exist");
					return;
				}
				EntityPack::DeleteEntityInstance(_id);
				_id = 0;
			};
			friend class EntityInstance;
			friend class EntityPack;
			friend class SystemInstance;
			friend static void Update();

		};
	}
}
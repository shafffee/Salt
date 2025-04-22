#pragma once
#include <ECS/ECS_params.h>
#include <stdint.h>
#include "Component.h"
#include <map>
#include <bitset>
#include "DataTypes/DataTypes.h"
#include <Logging/Logging.h>

namespace salt {
	class ComponentPack {
	private:
	public:
		/*
		TEST_COMPONENT
			INT x
			FLOAT y
			STRING name
		*/
		NameID_Container<ComponentType, COMPONENT_TYPES_MAX> component_types;

		/*
		entity1	component instances: 123
		entity2	component instances: 45
		*/
		uint16_t entity_componentInstances[ENTITIES_MAX][COMPONENT_TYPES_MAX];
		/*
		{hello 2 3}
		{1.0 5}
		*/
		Pack_Container<ComponentInstance, COMPONENTS_MAX>instances;

		Pack_Container<int64_t, INT_FIELDS_MAX> int_fields;
		Pack_Container<float, FLOAT_FIELDS_MAX> float_fields;
		Pack_Container< std::string, STRING_FIELDS_MAX> string_fields;
	public:
		ComponentPack() {
			return;
		};

		uint16_t allocField(FieldType type);


		//-------------COMPONENT TYPES---------------------
		// can have a lot of issues when deleting component types. 
		// mb should avoid using remove function after entity creation
		// ??? availlable only from parser
		inline int16_t addComponentType(ComponentType c, std::string name) { return component_types.addItem(c, name); };;

		//get Entity pointer
		inline ComponentType* getComponentType(std::string name) { return component_types.getItem(name); };
		inline ComponentType* getComponentType(uint16_t id) { return component_types.getItem(id); };

		//getSize
		inline uint16_t getMaxComponentTypes() { return component_types.getSize(); };

		//get entity id/name
		inline uint16_t getComponentTypeId(std::string name) { return component_types.getItemId(name); };
		inline std::string getComponentTypeName(uint16_t id) { return component_types.getItemName(id); };

	private:
		friend class Entity;
		friend class EntityPack;
		//-------------COMPONENT INSTANCES---------------------
		// used only from entity
		// add component to the entity
		inline void addComponent(std::string component_type_name, uint16_t entity_id) {
			uint16_t id_in_instances = instances.addItem(ComponentInstance(component_types.getItem(component_type_name))) ;
			Salt::log::debug(" component type " + component_type_name + " added to " + std::to_string(entity_id) + " slot " + std::to_string(id_in_instances));
			entity_componentInstances[entity_id][component_types.getItemId(component_type_name)] = id_in_instances;
		};
		inline void addComponent(uint16_t component_type_id, uint16_t entity_id) {
			uint16_t id_in_instances = instances.addItem(ComponentInstance(component_types.getItem(component_type_id)));
			Salt::log::debug(" component type " + std::to_string(component_type_id) + " added to " + std::to_string(entity_id) + " slot " + std::to_string(id_in_instances));
			entity_componentInstances[entity_id][component_type_id] = id_in_instances;
		};
		//get component pointer
		//get component probably needs optimization, but since there is not a huge amount of components in a single entity it is fine
		ComponentInstance* getComponent(std::string component_type_name, uint16_t entity_id) {
			//Salt::log::debug(" getting component for entity " + std::to_string(entity_id) + " component type " + component_type_name + " slot " + std::to_string(entity_componentInstances[entity_id][component_types.getItemId(component_type_name)]));
			return instances.getItem( entity_componentInstances[entity_id][component_types.getItemId(component_type_name)] );
		};
		ComponentInstance* getComponent(uint16_t component_type_id, uint16_t entity_id) {
			//Salt::log::debug(" getting component for entity " + std::to_string(entity_id) + " component type " + std::to_string(component_type_id) + " slot " + std::to_string(entity_componentInstances[entity_id][component_type_id]));
			return instances.getItem(entity_componentInstances[entity_id][component_type_id]);
		}
	};
}
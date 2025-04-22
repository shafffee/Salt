#pragma once
#include <string>
#include <bitset>
#include <ECS/ECS_params.h>
#include "../Component/Component.h"

namespace salt {

	class Entity {
	private:
		std::bitset<COMPONENTS_MAX> components;
		std::bitset<SYSTEMS_MAX> systems;

	public:
		Entity();

		Entity& operator=(const Entity& other);

		//removes all components and systems flags
		void reset();
		
		//adds system/component flag to the bitset
		void addComponent(std::string name);
		void addSystem(std::string name);

		//remove system/component flag from the bitset
		void removeComponent(std::string name);
		void removeSystem(std::string name);

		//check if system/component is attached
		bool hasComponent(std::string name);
		bool hasComponent(uint16_t component_id);
		bool hasSystem(std::string name);
		bool hasSystem(uint16_t system_id);

		ComponentInstance* getComponent(std::string name);
	};

}
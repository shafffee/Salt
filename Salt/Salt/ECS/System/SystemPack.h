#pragma once
#include <vector>
#include "System.h"
#include <ECS/ECS_params.h>
#include <stdint.h>
#include <map>
#include "DataTypes/DataTypes.h"


namespace salt {
	class SystemPack {
	private:
		NameID_Container<System, SYSTEMS_MAX> systems;
	public:
		//add returns a pointer to the added system
		inline uint16_t addSystem(System s, std::string name) { return systems.addItem(s, name); };

		//getting Systems
		inline System* getSystem(std::string name) { return systems.getItem(name); };
		inline System* getSystem(uint16_t id) { return systems.getItem(id); };

		//remove System
		inline void removeSystem(std::string name) { systems.removeItem(name); };
		inline void removeSystem(uint16_t id) { systems.removeItem(id); };


		//getSize
		inline uint16_t getMaxSystems() { return systems.getSize(); };

		//get system id/name
		inline uint16_t getSystemId(std::string name) { return systems.getItemId(name); };
		inline std::string getSystemName(uint16_t id) { return systems.getItemName(id); };		 
	};
}
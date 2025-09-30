#pragma once
#include "ECS_params.h"
#include <stdint.h>
#include <map>
#include <bitset>

namespace salt {
	namespace ECS {

		class Entity;
		/*
		----SYSTEM INSTANCE----
		is a FUNCTION_POINTER
		and a BITMASK of required components
		-------------------
		*/

		class SystemInstance {
		private:
			void (*_foo)(Entity entity_id);
			std::bitset<COMPONENT_TYPES_MAX> _required_components;

			//constructor
			SystemInstance(void(*foo)(Entity) = nullptr, std::bitset<COMPONENT_TYPES_MAX> required_components = 0) : _foo(foo), _required_components(required_components) {};

			// copy constructor
			SystemInstance& operator=(const SystemInstance& other);

			//runs function for entity
			void run(Entity e);

			friend class System;
			friend class SystemPack;			
			friend static void Update();
			friend class Entity;
		};




		/*
		----SYSTEM PACK----
		is a collection of system instances.
		you CAN NOT DELETE existing system instances
		but you can add more of them if needed

		system instance with index 0 is reserved and should not be overwritten.
		this is a "null system" that does nothing
		it is used to avoid errors in case the system instance can not be used
		-------------------
		*/

		class SystemPack {
		private:
			inline static uint64_t _systems_count = 0;				//number of system instances currently added
			inline static SystemInstance _systems[SYSTEMS_MAX + 1];

			//called by System on create
			//adds new system instance and returns its id
			static uint64_t RegisterSystemInstance(void(*foo)(Entity), std::bitset<COMPONENT_TYPES_MAX> required_components);

			friend class System;
			friend class SystemInctance;
			friend static void Update();
			friend class Entity;
		};

		/*
		----SYSTEM----
		is actually just an INDEX
		of the SYSTEM INSTANCE in the SYSTEM PACK
		it is done for convinience and readability.
		When you create a system, you are actually creating the SYSTEM INSTANCE in the SYSTEM PACK
		-------------------
		*/

		class System {
		private:
			int64_t _id_in_pack;
		public:
			System(void(*foo)(Entity) = nullptr, std::bitset<COMPONENT_TYPES_MAX> required_components = 0);

			// Implicit conversion to std::bitset
			operator std::bitset<SYSTEMS_MAX>() const;

			// Define operator| for System-System
    		friend std::bitset<SYSTEMS_MAX> operator|(const System& lhs, const System& rhs) {
    		    return std::bitset<SYSTEMS_MAX>(lhs) | std::bitset<SYSTEMS_MAX>(rhs);
    		}
		
    		// Define operator| for System-bitset
    		friend std::bitset<SYSTEMS_MAX> operator|(const System& lhs, const std::bitset<SYSTEMS_MAX>& rhs) {
    		    return std::bitset<SYSTEMS_MAX>(lhs) | rhs;
    		}
		
    		// Define operator| for bitset-System
    		friend std::bitset<SYSTEMS_MAX> operator|(const std::bitset<SYSTEMS_MAX>& lhs, const System& rhs) {
    		    return lhs | std::bitset<SYSTEMS_MAX>(rhs);
    		}


			friend class SystemInctance;
			friend class SystemPack;
			friend static void Update();

		};
	}
}
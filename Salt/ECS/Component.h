#pragma once
#include "ECS_params.h"
#include <stdint.h>
#include <map>
#include <bitset>
#include <Logging.h>

namespace salt {
	namespace ECS {



		/*
		----COMPONENT INSTANCE----
		a map of structs
		-------------------
		*/
		template <class T>
		class ComponentInstance {
		private:
			std::map<uint64_t, T> entity_component_map; //stores an entity id as a key and component data as a value

			//constructor
			ComponentInstance(){};

			// copy constructor
			ComponentInstance& operator=(const ComponentInstance& other) {
				this->_foo = other._foo;
				this->_required_components = other._required_components;
				return *this;
			};

			friend class  ComponentPack;
			friend static void Update();

		};




		/*
		----COMPONENT PACK----
		is a collection of component instances.
		you CAN NOT DELETE existing component instances
		but you can add more of them if needed

		component instance with index 0 is reserved and should not be overwritten.
		this is a "null component" that does nothing
		it is used to avoid errors in case the component instance can not be used
		-------------------
		*/

		class ComponentPack {
		private:
			inline static uint64_t _components_count = 0;				//number of component instances currently added
			inline static std::shared_ptr<void> _components[COMPONENT_TYPES_MAX + 1];

		public:
			//called by Component on create
			//adds new component instance and returns its id
			template <class T>
			inline static uint64_t RegisterComponentInstance() {

				if (_components_count + 1 > COMPONENT_TYPES_MAX) {
					Logging::Error("Component can not be added. COMPONENT_TYPES_MAX limit is being exeeded");
					return 0;
				}

				//add component to array and return its id
				_components_count += 1;
				_components[_components_count] = std::shared_ptr<ComponentInstance<T>>(new ComponentInstance<T>());
				return _components_count;
			};
			friend static void Update();
			friend class Entity;
			template <class U>
			friend class ComponentInstance;

		};




		/*
		----COMPONENT----
		is actually just an INDEX
		of the COMPONENT INSTANCE in the COMPONENT PACK
		it is done for convinience and readability.
		When you create a component, you are actually creating the COMPONENT INSTANCE (map of structs) in the COMPONENT PACK
		-------------------
		*/

		template <class T>
		class Component {
		private:
			int64_t _id_in_pack;
		public:
			Component() {
				_id_in_pack = ComponentPack::RegisterComponentInstance<T>();
			}

			// Implicit conversion to std::bitset
			operator std::bitset<COMPONENT_TYPES_MAX>() const {
				std::bitset<COMPONENT_TYPES_MAX> bits;
				bits.set(_id_in_pack); // Set the bit corresponding to this component
				return bits;
			}

    		// Define operator| for Component-Component
    		template <class U>
    		friend std::bitset<COMPONENT_TYPES_MAX> operator|(const Component<T>& lhs, const Component<U>& rhs) {
    		    return std::bitset<COMPONENT_TYPES_MAX>(lhs) | std::bitset<COMPONENT_TYPES_MAX>(rhs);
    		}
		
    		// Define operator| for Component-bitset
    		friend std::bitset<COMPONENT_TYPES_MAX> operator|(const Component<T>& lhs, const std::bitset<COMPONENT_TYPES_MAX>& rhs) {
    		    return std::bitset<COMPONENT_TYPES_MAX>(lhs) | rhs;
    		}
		
    		// Define operator| for bitset-Component
    		friend std::bitset<COMPONENT_TYPES_MAX> operator|(const std::bitset<COMPONENT_TYPES_MAX>& lhs, const Component<T>& rhs) {
    		    return lhs | std::bitset<COMPONENT_TYPES_MAX>(rhs);
    		}

			template <class U>
			friend class ComponentInstance;
			friend class  ComponentPack;
			friend static void Update();
			friend class Entity;
		};

	}
}
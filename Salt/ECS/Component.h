#pragma once
#include "ECS_params.h"
#include <stdint.h>
#include <map>
#include <bitset>
#include <Logging.h>
#include <memory>

namespace salt {
	namespace ECS {




		// Базовый интерфейс для всех ComponentInstance (for delete entity)
		class IComponentInstance {
		public:
			virtual ~IComponentInstance() = default;
			virtual void clearEntityData(uint64_t id) = 0;
		};

		/*
		----COMPONENT INSTANCE----
		a map of structs
		-------------------
		*/
		template <class T>
		class ComponentInstance:public IComponentInstance {
		public:

			//returns pointer to data for a certain entity
			T* getComponentData(uint64_t entityId) {

				if (entity_component_map.count(entityId)) {
					return &entity_component_map[entityId];
				}
				//creating empty data if not found
				entity_component_map[entityId] = {};
				//salt::Logging::Error("Trying to get component data that does not exist for an entity");
				return &entity_component_map[entityId];
			}

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

			//delete 
			void clearEntityData(uint64_t id){
				if(entity_component_map.count(id)){
					entity_component_map.erase(id);
				}
			}



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
			inline static std::shared_ptr<IComponentInstance> _components[COMPONENT_TYPES_MAX + 1]= {};

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

			inline static void deleteEntityData(uint64_t id) {
				for(uint64_t i = 1; i <= _components_count; i++) {
					if (_components[i]) {
						_components[i]->clearEntityData(id);
					}
				}
			};


			template <class T>
			inline static std::shared_ptr<ComponentInstance<T>> GetComponentInstance(uint64_t componentId) {
				if (componentId > 0 && componentId <= _components_count && _components[componentId]) {
					return std::static_pointer_cast<ComponentInstance<T>>(_components[componentId]);
				}
				salt::Logging::Error("Trying to get component instance that does not exist");
				return nullptr;
			}

/*
			inline static void clearEntityData(uint64_t id) {
				for (uint64_t c = 1;c < COMPONENT_TYPES_MAX + 1;c++) {
                        if(_components[c]->entity_component_map.count(id) ) {
                        	_components[c]->entity_component_map.erase(e._id);
                        }
                }
			};
*/

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
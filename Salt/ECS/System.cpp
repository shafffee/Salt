#include "System.h"
#include "Entity.h"

namespace salt::ECS {

	SystemInstance& SystemInstance::operator=(const SystemInstance& other)
	{
		this->_foo = other._foo;
		this->_required_components = other._required_components;
		return *this;
	}

	void SystemInstance::run(Entity e)
	{
		//entity does not exist (no components)
		if (!EntityPack::EntityWithIdExists(e._id)) return;
		//function is not assigned
		if (_foo == nullptr) return;
		_foo(e);
	};

	uint64_t SystemPack::RegisterSystemInstance(void(*foo)(Entity), std::bitset<COMPONENT_TYPES_MAX> required_components)
	{

		if (_systems_count + 1 > SYSTEMS_MAX) {
			Logging::Error("System can not be added. SYSTEMS_MAX limit is being exeeded");
			return 0;
		}

		//add system to array and return its id
		_systems_count += 1;
		_systems[_systems_count] = SystemInstance(foo, required_components);
		return _systems_count;
	}

	System::System(void(*foo)(Entity), std::bitset<COMPONENT_TYPES_MAX> required_components)
	{
		_id_in_pack = SystemPack::RegisterSystemInstance(foo, required_components);
	}

	System::operator std::bitset<SYSTEMS_MAX>() const
	{
		std::bitset<SYSTEMS_MAX> bits;
		bits.set(_id_in_pack); // Set the bit corresponding to this component
		return bits;
	}

}
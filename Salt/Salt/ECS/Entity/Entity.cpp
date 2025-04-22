#include "Entity.h"
#include "ECS/ECS.h"
#include "../Component/ComponentPack.h"
#include "../System/SystemPack.h"
#include "../Entity/EntityPack.h"
#include <Logging/Logging.h>

namespace salt {

	Entity::Entity() {
		components.reset();
		systems.reset();
	};

	Entity& Entity::operator=(const Entity& other)
	{
		this->components = other.components;
		this->systems = other.systems;
		return *this;
	}

	void Entity::reset()
	{
		components.reset();
		systems.reset();
	}

	void Entity::addComponent(std::string name)
	{
		components[salt::ECS::components.getComponentTypeId(name)] = 1;
	}
	void Entity::addSystem(std::string name)
	{
		systems[salt::ECS::systems.getSystemId(name)] = 1;
	}
	void Entity::removeComponent(std::string name)
	{
		components[salt::ECS::components.getComponentTypeId(name)] = 0;
	}
	void Entity::removeSystem(std::string name)
	{
		systems[salt::ECS::systems.getSystemId(name)] = 0;
	}
	bool Entity::hasComponent(std::string name)
	{
		return components[salt::ECS::components.getComponentTypeId(name)] == 1;
	}
	bool Entity::hasSystem(std::string name)
	{
		return  systems[salt::ECS::systems.getSystemId(name)] == 1;
	}

	bool Entity::hasComponent(uint16_t component_id)
	{
		return components[component_id] == 1;
	}
	bool Entity::hasSystem(uint16_t system_id)
	{
		return  systems[system_id] == 1;
	}
	ComponentInstance* Entity::getComponent(std::string name)
	{
		return ECS::components.getComponent(name, ECS::entities.getEntityId(this));
	}
}
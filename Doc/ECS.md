# ECS

Entity-Component-System uses 3 groups of objects:
1. Entity
2. Component
3. System

to make readability better and programming easier, the classes ***Entity***, ***Component*** and ***System***
are just tools, operating on ***EntityInstance***, ***ComponentInstance*** and ***SystemInstance***
that are stored in static classes ***EntityPack***, ***ComponentPack*** and ***SystemPack***

---
# Entity

## EntityInstance
is two bitsets called *_components* and *_systems*

## EntityPack
is a collection of **EntityInstance**

## Entity
is a tool for simple usage of pack and instance.
it contains *_id_in_pack* variable, that resembles (index_in_the_Pack+1),
because *_id_in_pack = 0* is reserved for the **NullEntity**
**NullEntity** appears when it is impossible to create an entity or it is deleted

# Example of usage:

```c++

//creating an entity with components position and hp
//and a system to control character
salt::ECS::Entity player( POSITION | HP, CHAR_CONTROLS);

//get a shared pointer to the component (type position_comp and a component POSITION)
// set x variable to 0
//if entity does not have a component, there is a protection that will call ERROR, but will provide a fictional shared pointer to avoid crash
player.component<position_comp>(POSITION)->x = 0;

//player becomes NullEntity
player.delete()

```

---
# System

## SystemInstance
is a function pointer 
```c++ 
void (*_foo)(Entity entity_id)
```
and a bitset *_required_components*

## SystemPack
is a collection of **SystemInstance**
you can not delete SystemInstance from system pack.

## System
is a tool for simple usage of pack and instance.
it contains *_id_in_pack* variable, that resembles index_in_the_Pack,
*_id_in_pack = 0* is reserved for the **NullSystem** that has *_foo = nullptr*
**NullSystem** appears when it is impossible to create system
when calling **NullSystem**, it does nothing
when calling system for *NullEntity*, it does nothing

# Example of usage:

```c++

//function
void char2Dcontrols(salt::ECS::Entity e)
{

	int speed = 1;
	if (salt::Input::IsKeyPressed(SALT_KEY_A)) e.component<position_comp>(POSITION)->x -= speed;
	if (salt::Input::IsKeyPressed(SALT_KEY_D)) e.component<position_comp>(POSITION)->x += speed;
	if (salt::Input::IsKeyPressed(SALT_KEY_W)) e.component<position_comp>(POSITION)->y -= speed;
	if (salt::Input::IsKeyPressed(SALT_KEY_S)) e.component<position_comp>(POSITION)->y += speed;

}
//create CHAR_CONTROLS system that requires POSITION component
inline static salt::ECS::System CHAR_CONTROLS(&char2Dcontrols, POSITION);

```

---
# Component

## ComponentInstance
resembles a component type, for all entities
is a **map** of structs, containing component info
```c++ 
//key: entity._id_in_pack
//value: struct
std::map<uint64_t, T> entity_component_map;
```

## ComponentPack
is a collection of **ComponentInstance** stored as std::shared_ptr<void>
you can not delete ComponentInstance from component pack

## Component
is a tool for simple usage of pack and instance.
it contains *_id_in_pack* variable, that resembles index_in_the_Pack,
*_id_in_pack = 0* is reserved for the **NullComponent** (std::shared_ptr<void>(nullprt) storen in the pack)
**NullComponent** appears when it is impossible to create component

# Example of usage:

```c++

//class position
class position_comp {
public:
	float x = 0;
	float y = 0;
};
// position Component
inline static salt::ECS::Component<position_comp> POSITION;

```
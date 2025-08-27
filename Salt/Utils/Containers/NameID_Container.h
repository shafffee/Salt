
#pragma once
#include <map>
#include <string>
#include <bitset>
#include <stdint.h>
#include "Pack_Container.h"


/*
Pack container with named assigned for each element
*/

namespace salt::Utils {
	template<class T, uint16_t size> class NameID_Container {
	private:
		//maps to access Item by name or by id bidirectionally
		std::map<std::string, std::uint16_t> name_id_map;
		std::map<std::uint16_t, std::string> id_name_map;
		//pack of items
		Pack_Container<T, size> items;
	public:

		//add returns a pointer to the added Item
		uint16_t addItem(T item, std::string name = "");
		
		//get item
		T* getItem(std::string name);
		T* getItem(uint16_t id);

		//remove item
		void removeItem(std::string name);
		void removeItem(uint16_t id);

		//getSize
		uint16_t getSize();

		//get system id/name
		uint16_t getItemId(std::string name);
		uint16_t getItemId(T* item);
		std::string getItemName(uint16_t id);
	};

	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------

	template<class T, uint16_t size>
	inline uint16_t NameID_Container<T, size>::addItem(T item, std::string name)
	{
		uint16_t id = items.addItem(item);

		//changing name if needed
		if (name == "") name = "No_Name_" + std::to_string(id);
		//adding to maps
		name_id_map.insert(std::pair<std::string, uint16_t>(name, id));
		id_name_map.insert(std::pair<uint16_t, std::string>(id, name));

		return id;
	}

	template<class T, uint16_t size>
	inline T* NameID_Container<T, size>::getItem(std::string name)
	{
		return items.getItem(name_id_map[name]);
	}

	template<class T, uint16_t size>
	inline T* NameID_Container<T, size>::getItem(uint16_t id)
	{
		return items.getItem(id);
	}

	template<class T, uint16_t size>
	inline void NameID_Container<T, size>::removeItem(std::string name)
	{
		items.removeItem(name_id_map[name]);
	}

	template<class T, uint16_t size>
	inline void NameID_Container<T, size>::removeItem(uint16_t id)
	{
		items.removeItem(id);
	}

	template<class T, uint16_t size>
	inline uint16_t NameID_Container<T, size>::getSize()
	{
		return size;
	}

	template<class T, uint16_t size>
	inline uint16_t NameID_Container<T, size>::getItemId(std::string name)
	{
		return name_id_map[name];
	}

	template<class T, uint16_t size>
	inline uint16_t NameID_Container<T, size>::getItemId(T* item)
	{
		return items.getItemId(item);
	}

	template<class T, uint16_t size>
	inline std::string NameID_Container<T, size>::getItemName(uint16_t id)
	{
		return id_name_map[id];
	}
}
#pragma once
#include <stdint.h>
#include <Logging.h>

/*
Pack container
-------------------------------------------------------------------
allocates memory for sertain number of objects at the beginning
places new objects on free slots
doesn't move any objects, just inserts in free slots

bool allocated[]:	# # # #### # ##
T objects[]		:	1_1_1_1111_1_11
*/

namespace salt::Utils{


template<class T, uint16_t size>
class Pack_Container {
private:
	//bitset of occupied Item slots. 
	std::bitset<size> allocated;
	//array of Items
	T items[size];
public:
	Pack_Container() {
		allocated.reset();
	}
	uint16_t addItem(T item);
	T* getItem(uint16_t id);
	void removeItem(uint16_t id);
	uint16_t getSize();
	int16_t getItemId(T*);
};

template<class T, uint16_t size>
inline uint16_t Pack_Container<T, size>::addItem(T item)
{
	//searching for free space
	uint16_t id = 0;
	for (;id < size;id++) {
		if (allocated[id] == 0) break;
	}
	if (id == size) {
		//ERROR no free space
		return 0;
	}

	//placing Item
	allocated[id] = 1;
	items[id] = item;

	return id;
}

//returnt pointer to the item. returns nullptr if slot is empty
template<class T, uint16_t size>
inline T* Pack_Container<T, size>::getItem(uint16_t id)
{
	if (allocated[id]) {
		return &items[id];
	}
	else {
		//item does not exist
		return nullptr;
	}
}

template<class T, uint16_t size>
inline void Pack_Container<T, size>::removeItem(uint16_t id)
{
	allocated[id] = 0;
}

template<class T, uint16_t size>
inline uint16_t Pack_Container<T, size>::getSize()
{
	return size;
}

template<class T, uint16_t size>
inline int16_t Pack_Container<T, size>::getItemId(T* item)
{
	return static_cast<size_t>(item-items);
}


}
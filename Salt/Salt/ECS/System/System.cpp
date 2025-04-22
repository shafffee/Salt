#include "System.h"

namespace salt {
	void System::setFunction(void (*foo)(uint16_t entity_id))
	{
		this->foo = foo;
	}
	void System::run(uint16_t entity_id)
	{
		foo(entity_id);
	}
}
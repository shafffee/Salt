#pragma once
#include <string>
#include <ECS/Entity/Entity.h>
#include <stdint.h>

namespace salt {
	struct System {
	private:
		void (*foo)(uint16_t entity_id);
	public:
		void setFunction(void (*foo)(uint16_t entity_id));
		void run(uint16_t entity_id);

		System& operator=(const System& other) {
			this->foo = other.foo;
			return *this;
		}
		/*
		std::bitset<COMPONENTS_NUM> required_components;
		std::bitset<COMPONENTS_NUM> optional_components;
		void setRequiredComponent();
		void setOptionalComponent();
		*/
	};
}
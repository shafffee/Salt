#include "ComponentPack.h"

namespace salt {
	uint16_t ComponentPack::allocField(FieldType type) {
		uint16_t id = 0;
		if (type == FieldType::INT) {
			id = int_fields.addItem(int64_t(0));
		}
		if (type == FieldType::FLOAT) {
			id = float_fields.addItem(0.0f);
		}
		if (type == FieldType::STRING) {
			id = string_fields.addItem("");
		}
		Salt::log::debug("field of type " + std::to_string((int)type) + " added to slot " + std::to_string(id));
		return id;
	}
}
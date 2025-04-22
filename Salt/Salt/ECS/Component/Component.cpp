#include "Component.h"
#include "ComponentPack.h"
#include <ECS/ECS.h>

namespace salt {
	ComponentInstance::ComponentInstance(ComponentType* type)
	{
		c = type;
		for (uint16_t i = 0;i < c->fields.getSize();i++) {
			FieldType* t = c->fields.getItem(i);
			if (t) {
				value_id[i] = ECS::components.allocField(*t);
			}
		}
	};

	template<typename T>
	inline T ComponentInstance::getField(const std::string& field_name) const
	{
		//change to c->getFieldType; 
		FieldType type = *c->fields.getItem(field_name);
		uint16_t target_value_id = value_id[c->getFieldId(field_name)];
		if (type == FieldType::INT) {
			if constexpr(std::is_same_v<T, int64_t*>) {
				return  ECS::components.int_fields.getItem(target_value_id);
			}
			if constexpr(std::is_same_v<T, int64_t>) {
				return  *ECS::components.int_fields.getItem(target_value_id);
			}
		}
		else if (type == FieldType::FLOAT) {
			if constexpr(std::is_same_v<T, float*>) {
				return   ECS::components.float_fields.getItem(target_value_id);
			}
			if constexpr(std::is_same_v<T, float>) {
				return  *ECS::components.float_fields.getItem(target_value_id);
			}
		}
		else if (type == FieldType::STRING) {
			if constexpr(std::is_same_v<T, std::string*>) {
				return  ECS::components.string_fields.getItem(target_value_id);
			}
			if constexpr(std::is_same_v<T, std::string>) {
				return *ECS::components.string_fields.getItem(target_value_id);
			}
		}
	};

	template int64_t ComponentInstance::getField<int64_t>(const std::string& field_name) const;
	template int64_t* ComponentInstance::getField<int64_t*>(const std::string& field_name) const;
	template float ComponentInstance::getField<float>(const std::string& field_name) const;
	template float* ComponentInstance::getField<float*>(const std::string& field_name) const;
	template std::string ComponentInstance::getField<std::string>(const std::string& field_name) const;
	template std::string* ComponentInstance::getField<std::string*>(const std::string& field_name) const;
}

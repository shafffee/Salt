#pragma once
#include <vector>
#include "Field.h"
#include <ECS/ECS_params.h>
#include "DataTypes/DataTypes.h"


namespace salt {
	class ComponentType {
	public:
		NameID_Container<FieldType, FIELDS_IN_COMPONENT_MAX> fields;

		//add returns an id of the added field
		inline uint16_t addField(FieldType field_type, std::string name) { return fields.addItem(field_type, name); };

		//get FieldType pointer
		inline FieldType* getField(std::string name) { return fields.getItem(name); };
		inline FieldType* getField(uint16_t id) { return fields.getItem(id); };

		//remove Field
		inline void removeField(std::string name) { fields.removeItem(name); };
		inline void removeField(uint16_t id) { fields.removeItem(id); };

		//getSize
		inline uint16_t getMaxFields() { return fields.getSize(); };

		//get field id/name
		inline uint16_t getFieldId(std::string name) { return fields.getItemId(name); };
		inline std::string getFieldName(uint16_t id) { return fields.getItemName(id); };

	};
	class ComponentInstance {
	public:
		ComponentType* c;
		uint16_t value_id[FIELDS_IN_COMPONENT_MAX];

		ComponentInstance() {
			c = nullptr;
			for (int i = 0;i < FIELDS_IN_COMPONENT_MAX;i++) value_id[i] = 0;
		};
		ComponentInstance(ComponentType* type);

		// copy assignment (copy-and-swap idiom)
		ComponentInstance& operator=(const ComponentInstance& other)
		{
			this->c = other.c;
			for (int i = 0;i < FIELDS_IN_COMPONENT_MAX;i++) this->value_id[i] = other.value_id[i];
			return *this;
		}

		template<typename T>
		T getField(const std::string& field_name) const;

	};
	
}
#pragma once

namespace salt {
	class EntityPack;
	class ComponentPack;
	class SystemPack;
	class ECS
	{
	public:

		static salt::EntityPack entities;
		static salt::ComponentPack components;
		static salt::SystemPack systems;

		static void Init();

		static void Update();

	};
}
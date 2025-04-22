#include "Salt.h"

class MyApp : public salt::Application {


	void onInit() override{
		setFPS(60);

		salt::Renderer::texture_manager->LoadTexture("blank", "./Salt/res/textures/blank.png");
		salt::Renderer::texture_manager->LoadTexture("smile", "./Salt/res/textures/texture1.png");

		salt::Renderer::font_manager->addFont("./Salt/res/fonts/gohufont");



		salt::ComponentType	ct;
		ct.addField(salt::FieldType::FLOAT, "x");
		ct.addField(salt::FieldType::FLOAT, "y");
		salt::ECS::components.addComponentType(ct, "position");
		salt::ECS::components.addComponentType(ct, "speed");

		salt::System s;
		s.setFunction(&moveSystem);
		salt::ECS::systems.addSystem(s, "move");

		salt::Entity e;
		e.addSystem("move");
		e.addComponent("position");
		e.addComponent("speed");
		salt::ECS::entities.addEntity(e);

		for (int i = 0; i < 10;i++) {
			uint16_t ent_id = salt::ECS::entities.addEntity(e);
			*(salt::ECS::entities.getEntity(ent_id)->getComponent("position")->getField<float*>("x")) = (std::rand()%100)/100.0f;
			*(salt::ECS::entities.getEntity(ent_id)->getComponent("position")->getField<float*>("y")) = (std::rand() % 100) / 100.0f;

			*(salt::ECS::entities.getEntity(ent_id)->getComponent("speed")->getField<float*>("x")) = (std::rand() % 100) / 5000.0f;
			*(salt::ECS::entities.getEntity(ent_id)->getComponent("speed")->getField<float*>("y")) = (std::rand() % 100) / 5000.0f;
		}

	}
	void onUpdate() override{
	}
	void onExit() override {
	}
};

salt::Application* CreateApplication(){
	return new MyApp();
};
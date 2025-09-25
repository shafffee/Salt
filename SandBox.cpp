#include "Salt.h"

class MyApp : public salt::Application {

  //Model* backpack;
  Sprite* test_sprite;

	void onInit() override {
		setFPS(60);

    salt::Input::CaptureMouse();

    //backpack = new Model("./Salt/res/models/test_model.obj");
    //backpack = new Model("./Salt/res/models/backpack/backpack.obj");
    test_sprite = new Sprite("./Salt/res/textures/shrek.jpeg");

	}
	void onUpdate() override{
    //salt::Renderer::drawModel(backpack);
    salt::Renderer::draw(test_sprite);
	}
	void onExit() override {
	}
};

salt::Application* CreateApplication(){
	return new MyApp();
};

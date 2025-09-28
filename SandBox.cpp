#include "Salt.h"

class MyApp : public salt::Application {

  //Model* backpack;
  Sprite* test_sprite;
  Camera* camera;

	void onInit() override {
		setFPS(60);

    salt::Input::CaptureMouse();

    //backpack = new Model("./Salt/res/models/test_model.obj");
    //backpack = new Model("./Salt/res/models/backpack/backpack.obj");
    test_sprite = new Sprite("./Salt/res/textures/shrek.jpeg");
    camera = new Camera();
    salt::Renderer::setCamera(camera);
    test_sprite->transformation = glm::translate(test_sprite->transformation, glm::vec3(0.0f, 0.0f, -1.0f));
    test_sprite->transformation = glm::scale(test_sprite->transformation, glm::vec3(1.0f, 1.0f, 1.0f));

	}
	void onUpdate() override{
    //salt::Renderer::drawModel(backpack);
    salt::Renderer::draw(test_sprite);

    //capture/uncapture mouse
    if (salt::Input::IsKeyPressed(SALT_KEY_ESCAPE))salt::Input::UncaptureMouse();
    if (salt::Input::IsMouseButtonPressed(SALT_MOUSE_BUTTON_1))salt::Input::CaptureMouse();

	}
	void onExit() override {
	}
};

salt::Application* CreateApplication(){
	return new MyApp();
};

#include "Salt.h"
#include "Player.h"
#include "Planet.h"

class MyApp : public salt::Application {

  Camera* camera;

	void onInit() override {
		setFPS(60);
    salt::Input::CaptureMouse();

    camera = new Camera();
    salt::Renderer::setCamera(camera);

    salt::ECS::Entity player = createPlayerEntity();
    createPlanetEntity();

	}
	void onUpdate() override{

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

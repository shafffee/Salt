#include "Salt.h"
#include "Components.h"
#include "Systems.h"
#include "Player.h"

class MyApp : public salt::Application {

  Model* backpack;
  float angle = 0.0f;
  //Sprite* test_sprite;
  Camera* camera;

	void onInit() override {
		setFPS(60);

    salt::Input::CaptureMouse();

    //backpack = new Model("./Salt/res/models/test_model.obj");
    //backpack = new Model("./Salt/res/models/backpack/backpack.obj");
    //backpack = new Model("./res/earth/Earth.fbx");
    backpack = new Model("./res/low-poly-planet-earth/Planet.fbx");
    backpack->setPosition({0,0,-2});
    //test_sprite = new Sprite("./Salt/res/textures/shrek.jpeg");
    camera = new Camera();
    salt::Renderer::setCamera(camera);
    //test_sprite->setPosition({0,0,-1});


    salt::ECS::Entity player = createPlayerEntity();


	}
	void onUpdate() override{
    angle+=0.1;
    backpack->setRotation({angle/3,angle/2,angle});
    salt::Renderer::draw(backpack);
    //salt::Renderer::draw(test_sprite);

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

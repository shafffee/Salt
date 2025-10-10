#include "Salt.h"
#include "Player.h"
#include "Planet.h"


void camera3D_controller(Camera* cam){
  float velocity = 0.01;
  float mouse_sens = 0.1;

  if (salt::Input::IsKeyPressed(SALT_KEY_UP))
    cam->Position += cam->Front * velocity;
  if (salt::Input::IsKeyPressed(SALT_KEY_DOWN))
    cam->Position -= cam->Front * velocity;
  if (salt::Input::IsKeyPressed(SALT_KEY_LEFT))
    cam->Position -= cam->Right * velocity;
  if (salt::Input::IsKeyPressed(SALT_KEY_RIGHT))
    cam->Position += cam->Right * velocity;

}


class MyApp : public salt::Application {

  Camera* camera;

  Font* font;
  Text * text;

	void onInit() override {
		setFPS(60);
    salt::Input::CaptureMouse();

    camera = new Camera();
    salt::Renderer::setCamera(camera);

    salt::ECS::Entity player = createPlayerEntity();
    createPlanetEntity();

    font = new Font("./Salt/res/fonts/verdanai.ttf");
    text = new Text();
    text->setFont(*font);
    text->setString("Hello World!");
    text->setPosition({0,0,-1});
    text->setScale({0.01,0.01, 1});

	}
	void onUpdate() override{

    camera3D_controller(camera);

    salt::Renderer::drawT(text,10);

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

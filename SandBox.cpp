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


  float xoffset = -salt::Input::GetCapturedMouseMovementX();
  float yoffset = salt::Input::GetCapturedMouseMovementY();

  xoffset *= mouse_sens;
  yoffset *= mouse_sens;

  cam->Yaw += xoffset;
  cam->Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (cam->Pitch > 89.0f)
      cam->Pitch = 89.0f;
    if (cam->Pitch < -89.0f)
      cam->Pitch = -89.0f;

  // update Front, Right and Up Vectors using the updated Euler angles
  cam->updateCameraVectors();

}

void foo(){
  std::cout<<"HW"<<std::endl;
}

class MyApp : public salt::Application {

  bool freecam = false;
  Camera* camera;
  Camera* debug_camera;

  Font* font;
  Text * text;

	void onInit() override {
		setFPS(60);
    salt::Input::CaptureMouse();

    camera = new Camera();
    debug_camera = new Camera();

    salt::Renderer::setCamera(camera);

    salt::ECS::Entity player = createPlayerEntity();
    createPlanetEntity();

    
    salt::Console::addCommand(&foo, "hw");
    salt::Console::addCommand(&foo, "hw");
    salt::Console::run("nc");
    salt::Console::run("hw");
    salt::Console::print("test console", {1,1,0});
    

    font = new Font("./res/verdanai.ttf", 128);
    text = new Text();
    text->setFont(*font);
    text->setColor({1,1,1,1});
    text->setString("Hello World!");
    text->setPosition({0,0,-1});
    text->setScale({0.1,0.1, 1});

	}
	void onUpdate() override{

    salt::Renderer::draw(text,10);

    //capture/uncapture mouse
    if (salt::Input::IsKeyPressed(SALT_KEY_ESCAPE))salt::Input::UncaptureMouse();
    if (salt::Input::IsMouseButtonPressed(SALT_MOUSE_BUTTON_1))salt::Input::CaptureMouse();

    //debug camera
    if(freecam){
      camera3D_controller(debug_camera);
    }

    if (salt::Input::IsKeyPressed(SALT_KEY_V)){
      freecam = true;
      salt::Renderer::setCamera(debug_camera);
    }
    if (salt::Input::IsKeyPressed(SALT_KEY_B)){
      freecam = false;
      salt::Renderer::setCamera(camera);
    }

	}
	void onExit() override {
	}
};

salt::Application* CreateApplication(){
	return new MyApp(); 
};

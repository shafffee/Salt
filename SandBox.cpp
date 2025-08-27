#include "Salt.h"

void colored_cube(float x, float y, float z,
  float r, float g, float b, float a);
void cube();


class MyApp : public salt::Application {

	void onInit() override {
		setFPS(60);
		salt::Renderer::setVideomode(640, 640, false); //make it later
    salt::Input::CaptureMouse();

		//salt::Renderer::texture_manager->LoadTexture("jet", "./Salt/res/textures/jet.png");
		//salt::Renderer::font_manager->addFont("./Salt/res/fonts/gohufont");

		//salt::ECS::Entity player(POSITION, CHAR_CONTROLS);
    // --------------------
    //cube();
    colored_cube(3, 2, 1, 0.1, 0.3, 0.7, 1);

	}
	void onUpdate() override{
	}
	void onExit() override {
	}
};

salt::Application* CreateApplication(){
	return new MyApp();
};


void colored_cube(float x, float y, float z, 
                      float r, float g, float b, float a) {
  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f+x, -0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f+x, -0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f+x,  0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f)}   // Blue left
  );

  // --------------------
  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f,  0.0f, 1.0f), glm::vec2(0.0f)}   // Blue left
  );
  // --------------------
  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  // --------------------
  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  // --------------------
  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x, -0.5f + y,  0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x, -0.5f + y, -0.5f + z), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  // --------------------
  salt::Renderer::drawPolygon(
    { glm::vec3(-0.5f + x,  0.5f + y, -0.5F + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );

  salt::Renderer::drawPolygon(
    { glm::vec3(0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)},  // Red top
    { glm::vec3(-0.5f + x,  0.5f + y,  0.5f + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)},  // Green right
    { glm::vec3(-0.5f + x,  0.5f + y, -0.5f + z), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f)}   // Blue left
  );
}

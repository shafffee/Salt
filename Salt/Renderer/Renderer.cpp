#include "Renderer.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Utils.h"
#include "VertexArray.h"
#include "Input.h"
#include "Model.h"
#include "ObjLoader.h"


std::string GetOpenGLErrorString() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) return "GL_NO_ERROR";

	std::vector<std::string> errors;
	while (error != GL_NO_ERROR) {
		switch (error) {
		case GL_INVALID_ENUM:
			errors.push_back("GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			errors.push_back("GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			errors.push_back("GL_INVALID_OPERATION");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errors.push_back("GL_INVALID_FRAMEBUFFER_OPERATION");
			break;
		case GL_OUT_OF_MEMORY:
			errors.push_back("GL_OUT_OF_MEMORY");
			break;
		case GL_STACK_UNDERFLOW:
			errors.push_back("GL_STACK_UNDERFLOW");
			break;
		case GL_STACK_OVERFLOW:
			errors.push_back("GL_STACK_OVERFLOW");
			break;
		default:
			errors.push_back("UNKNOWN_ERROR (0x" +
				std::to_string(static_cast<unsigned int>(error)) + ")");
		}
		error = glGetError();
	}

	std::string result;
	for (const auto& err : errors) {
		if (!result.empty()) result += " | ";
		result += err;
	}
	return result;
}

namespace salt {

	//read_file
	std::string read_file(const std::string& file_path) {
		// Open the file in binary mode to preserve all characters
		std::ifstream file(file_path, std::ios::binary);

		// Check if the file was successfully opened
		if (!file.is_open()) {
			salt::Logging::Error("Can not open file " + file_path + " to read");
		}

		// Read the entire file content using stream iterators
		return std::string(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>()
		);
	}
}

namespace salt {

	void Renderer::draw(Model* model)
	{
		models.push_back(model);
	}
	void Renderer::draw(Sprite* sprite)
	{
		models.push_back(sprite);
	}


	void Renderer::Init()
	{
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		//DEFINES NUMBER OF TEXTURE SLOTS
		GLint max_units;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_units);
		//Salt::log::debug("Max texture units: " + std::to_string(max_units));

		default_shader = Shader(read_file("./Salt/res/shaders/default.vs"), read_file("./Salt/res/shaders/default.fs"));
		//load_obj(&_verticies, &_indices, read_file("./Salt/res/models/test_model.obj"), glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f)) );
		//salt::Utils::load_obj(&_verticies, &_indices, read_file("./Salt/res/models/backpack/backpack.obj"), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, -10.0f)) );

		//texture_manager = new TextureManager();
		//batch = new Batch();
		//font_manager = new FontManager();
		//backpack = new Model("./Salt/res/models/backpack/backpack.obj");

		Textures::Init();

	}

	void Renderer::Update() {

		// Get window dimensions
		int width, height;
		glfwGetWindowSize(salt::Window::getGLFWwindow(), &width, &height);


		//camera controls
		if (salt::Input::IsKeyPressed(SALT_KEY_W))camera.ProcessKeyboard(FORWARD, 1.0f/60);
		if (salt::Input::IsKeyPressed(SALT_KEY_A))camera.ProcessKeyboard(LEFT, 1.0f / 60);
		if (salt::Input::IsKeyPressed(SALT_KEY_S))camera.ProcessKeyboard(BACKWARD, 1.0f / 60);
		if (salt::Input::IsKeyPressed(SALT_KEY_D))camera.ProcessKeyboard(RIGHT, 1.0f / 60);
		//speedup (made not in the best way because it just increases delta time)
		if(salt::Input::IsKeyPressed(SALT_KEY_LEFT_SHIFT)){
			if (salt::Input::IsKeyPressed(SALT_KEY_W))camera.ProcessKeyboard(FORWARD, 1.0f/60*9);
			if (salt::Input::IsKeyPressed(SALT_KEY_A))camera.ProcessKeyboard(LEFT, 1.0f / 60*9);
			if (salt::Input::IsKeyPressed(SALT_KEY_S))camera.ProcessKeyboard(BACKWARD, 1.0f / 60*9);
			if (salt::Input::IsKeyPressed(SALT_KEY_D))camera.ProcessKeyboard(RIGHT, 1.0f / 60*9);
		}
		camera.ProcessMouseMovement(-salt::Input::GetCapturedMouseMovementX(), salt::Input::GetCapturedMouseMovementY());
		if (salt::Input::IsKeyPressed(SALT_KEY_ESCAPE))salt::Input::UncaptureMouse();
		if (salt::Input::IsMouseButtonPressed(SALT_MOUSE_BUTTON_1))salt::Input::CaptureMouse();



		// MVP matrices
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 1.0f*width/height, 0.1f, 100.0f);

		//clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//send matrices to shader
		default_shader.bind();
		default_shader.setMat4("model", model);
		default_shader.setMat4("view", view);
		default_shader.setMat4("projection", projection);
		default_shader.setVec3("viewPos", camera.Position);


		//draw all models
		for(int i=0; i<models.size(); i++){
			models[i]->Draw(default_shader);
		}
		models.clear();

		glfwSwapBuffers(salt::Window::getGLFWwindow());

	}
}
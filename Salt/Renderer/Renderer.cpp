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

	void Renderer::setVideomode(int64_t videomode_x, int64_t videomode_y, bool videomode_stretch)
	{
		_videomode_x = videomode_x;
		_videomode_y = videomode_y;
		_videomode_stretch = videomode_stretch;
	}
	void Renderer::drawPolygon(Vertex a, Vertex b, Vertex c)
	{
		_verticies.push_back(a);
		_verticies.push_back(b);
		_verticies.push_back(c);

		_indices.push_back(_verticies.size() - 3);
		_indices.push_back(_verticies.size() - 2);
		_indices.push_back(_verticies.size() - 1);
	}

	void Renderer::drawModel(Model* model)
	{
		models.push_back(model);
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

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 1.0f*width/height, 0.1f, 100.0f);

		VertexArray vao = VertexArray();
		VertexBuffer vbo = VertexBuffer();
		IndexBuffer ibo = IndexBuffer();
		

		//texture_manager->bindTextures();
		//
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//
		//batch->draw();
		//batch->clear();
		//glfwSwapBuffers(salt::Window::getGLFWwindow());
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//DEBUG(GetOpenGLErrorString());

		vao.bind();

		default_shader.bind();
		default_shader.setMat4("model", model);
		default_shader.setMat4("view", view);
		default_shader.setMat4("projection", projection);
		default_shader.setVec3("viewPos", camera.Position);

		vbo.bind();
		vbo.buffer(&_verticies[0], _verticies.size() * sizeof(Vertex));
		ibo.bind();
		ibo.buffer(&_indices[0], _indices.size() * sizeof(uint32_t));

		//glm::vec3 Position;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glEnableVertexAttribArray(0);

		//glm::vec3 Normal;
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//glm::vec2 TexCoords;
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		for(int i=0; i<models.size(); i++){
			models[i]->Draw(default_shader);
		}
		models.clear();

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(salt::Window::getGLFWwindow());

	}
}
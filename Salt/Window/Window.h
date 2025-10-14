#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace salt {

	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	inline void GLFW_init() {
		//Salt::log::debug("initializing GLFW");
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//Salt::log::debug("GLFW initialized");
	}

	inline void LogWindow(GLFWwindow* window) {
		//Salt::log::debug("Creating Window");

		if (window == NULL)
		{
			//Salt::log::error("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		else {
			//Salt::log::debug("Window created");
		}

		glfwMakeContextCurrent(window);
	}

	inline void GLAD_init() {
		//Salt::log::debug("Initializing GLAD");
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			//Salt::log::error("Failed to initialize GLAD");
		}
		else {
			//Salt::log::debug("GLAD initialized");
		}
	}

	class Window {
	private:
		inline static GLFWwindow* window;
	public:
		static void Init() {
			GLFW_init();
			window = glfwCreateWindow(640, 640, "SALT", NULL, NULL);
			LogWindow(window);
			glfwSwapInterval(0);
			GLAD_init();
			glViewport(0, 0, 640, 640);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		};
		static void Exit() {
			glfwTerminate();
		}
		static GLFWwindow* getGLFWwindow() {
			return window;
		}
		static bool shouldClose() {
			return glfwWindowShouldClose(window);
		};
		static void swapBuffers() {
			glfwSwapBuffers(window);
		};
		static float getWidth() {
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			return float(width);
		};
		static float getHeight() {
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			return float(height);
		};
	};

}
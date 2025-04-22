#pragma once

#include"Keycodes.h"
#include"Mousecodes.h"
#include "Core/Window.h"

namespace salt {

	class Input {
	public:
		static void Init() {
		};
		static void Update() {
			glfwPollEvents();
			return;
		};

		static bool IsKeyPressed(int keycode) {
			int state = glfwGetKey(salt::Window::getGLFWwindow(), keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		static bool IsMouseButtonPressed(int button) {
			int state = glfwGetMouseButton(salt::Window::getGLFWwindow(), button);
			return state == GLFW_PRESS;
		}

		static float GetMouseX() {
			double xpos, ypos;
			glfwGetCursorPos(salt::Window::getGLFWwindow(), &xpos, &ypos);
			return float(xpos);
		}
		static float GetMouseY() {
			double xpos, ypos;
			glfwGetCursorPos(salt::Window::getGLFWwindow(), &xpos, &ypos);
			return float(ypos);
		}
	};
}
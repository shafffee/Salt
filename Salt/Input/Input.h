#pragma once

#include"Keycodes.h"
#include"Mousecodes.h"
#include "Window.h"

namespace salt {

	class Input {
	private:
		inline static bool _mouse_captured = false;
		inline static double _prev_x = 0;
		inline static double _prev_y = 0;
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

		static void CaptureMouse() {
			glfwSetInputMode(salt::Window::getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			_mouse_captured = true;
			glfwGetCursorPos(salt::Window::getGLFWwindow(), &_prev_x, &_prev_y);
		}

		static float GetCapturedMouseMovementX() {
			if (!_mouse_captured) return 0.0f;
			double xpos, ypos;
			glfwGetCursorPos(salt::Window::getGLFWwindow(), &xpos, &ypos);
			double movement = float(_prev_x - xpos);
			_prev_x = xpos;
			return float(movement);
		}

		static float GetCapturedMouseMovementY() {
			if (!_mouse_captured) return 0.0f;
			double xpos, ypos;
			glfwGetCursorPos(salt::Window::getGLFWwindow(), &xpos, &ypos);
			double movement = float(_prev_y - ypos);
			_prev_y = ypos;
			return float(movement);
		}

		static void UncaptureMouse() {
			_mouse_captured = false;
			glfwSetInputMode(salt::Window::getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	};
}
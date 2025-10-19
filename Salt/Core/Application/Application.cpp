#include "Application.h"
#include "ECS.h"
#include "Renderer.h"
#include "Ticks.h"

namespace salt {
	void Application::setFPS(double fps_limit)
	{
		MAX_FPS = fps_limit;
		SINGLE_FRAME_TIME = std::chrono::microseconds(int(1000000.0 / MAX_FPS));
	}

	void Application::defaultOnInit()
	{
		//creates WINDOW, RENDERER and INPUT
		salt::Window::Init();
		salt::Renderer::Init();
		salt::Input::Init();
		//run user-defined init
		salt::ECS::Init();
		onInit();
	}

	void Application::defaultRun()
	{
		//clock for fps lock
		std::chrono::system_clock::time_point frame_end_time = std::chrono::system_clock::now();

		//main cycle
		while (true)
		{
			frame_end_time += SINGLE_FRAME_TIME;

			//exit
			if (salt::Window::shouldClose()) break;

			salt::Input::Update();
			salt::ECS::Update();
			salt::Renderer::Update();
			onUpdate();
			salt::Ticks::Update();

			//wait until next frame
			if (std::chrono::system_clock::now() < frame_end_time) {
				std::this_thread::sleep_until(frame_end_time);
			}
		}
	}

	void Application::defaultOnExit()
	{
		onExit();
	};

}
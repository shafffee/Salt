#pragma once
#include "Input.h"

#include <thread>
#include "Clock.h"

namespace salt {
	class Application {
	private:
		double MAX_FPS = 60.0;
		std::chrono::microseconds SINGLE_FRAME_TIME = std::chrono::microseconds(int(1000000.0 / MAX_FPS));
	public:

		virtual void onInit() = 0;
		virtual void onUpdate() = 0;
		virtual void onExit() = 0;

		void setFPS(double fps_limit);

		void defaultOnInit();
		void defaultRun();
		void defaultOnExit();
	};
}
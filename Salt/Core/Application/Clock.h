#pragma once
#include <chrono>

namespace salt::Utils{

class Clock {
private:
	std::chrono::system_clock::time_point begin;
	std::chrono::system_clock::time_point end;
	bool running;
public:
	Clock() {
		begin = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();;
		running = false;
	}

	void start() {
		running = true;
		begin = std::chrono::system_clock::now();
	};
	void stop() {
		running = false;
		end = std::chrono::system_clock::now();
	};
	void reset() {
		begin = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();
	};

	double ToMicroseconds() {
		std::chrono::duration<float> fsec;
		std::chrono::microseconds dt;
		if (running) {
			fsec = std::chrono::system_clock::now() - begin;
			dt = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
			return dt.count();
		}
		fsec = end - begin;
		dt = std::chrono::duration_cast<std::chrono::microseconds>(fsec);
		return dt.count();
	}

	double ToMilliseconds() {
		std::chrono::duration<float> fsec;
		std::chrono::seconds dt;
		if (running) {
			fsec = std::chrono::system_clock::now() - begin;
			dt = std::chrono::duration_cast<std::chrono::seconds>(fsec);
			return dt.count();
		}
		fsec = end - begin;
		dt = std::chrono::duration_cast<std::chrono::seconds>(fsec);
		return dt.count();
	}

	double ToSeconds() {
		std::chrono::duration<float> fsec;
		std::chrono::seconds dt;
		if (running) {
			fsec = std::chrono::system_clock::now() - begin;
			dt = std::chrono::duration_cast<std::chrono::seconds>(fsec);
			return dt.count();
		}
		fsec = end - begin;
		dt = std::chrono::duration_cast<std::chrono::seconds>(fsec);
		return dt.count();
	}
};

}
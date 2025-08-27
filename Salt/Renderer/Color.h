///refactor to create matrix4f


#pragma once
#include <cstdint>
#include <string>
namespace salt{
struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	Color() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {};
	Color(std::string hex) {
		bool tag = false;
		if (hex[0] == '#') {
			tag = true;
		}

		if (hex.length() != 6 + tag && hex.length() != 8 + tag) {
			Color();
			return;
		}

		r = std::stoi(hex.substr(0 + tag, 2), nullptr, 16);
		g = std::stoi(hex.substr(2 + tag, 2), nullptr, 16);
		b = std::stoi(hex.substr(4 + tag, 2), nullptr, 16);
		a = 255;
		if (hex.length() == 8) {
			a = std::stoi(hex.substr(6 + tag, 2), nullptr, 16);
		}
	};
	Color(const char* hex) : Color(std::string(hex)) {};
};
}
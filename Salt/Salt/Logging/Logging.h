#pragma once

#include <iostream>
#include <string>

namespace Salt{
	namespace log {

		void debug(const std::string& message);
		void error(const std::string& message);

	}
}
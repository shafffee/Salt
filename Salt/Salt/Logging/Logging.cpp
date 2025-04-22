#include "Logging.h"

namespace Salt {
	namespace log {

		void debug(const std::string& message) {
			std::cout << "[DEBUG]\t" << message << std::endl;
		}
		void error(const std::string& message)
		{
			std::cout << "\t[ERROR]\t" << message << std::endl;
		}

	}
}
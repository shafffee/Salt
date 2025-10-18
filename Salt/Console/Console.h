#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include "Logging.h"

namespace salt {

	class Application;

	struct ConsoleMessage{
      std::string message;
      uint64_t time_created;
      // Constructor
    };

	class Console{
	public:
		static void addCommand(void(*foo)(), std::string name);
	
		static void run(std::string command_name);
	
		static void print(std::string str, const glm::vec3& color = {1,1,1});
	
		static void AttachToLogging();

	private:

		inline static std::map<std::string, void(*)()> name_command_map;

		static void logToConsole(const std::string& message, salt::Logging::LoggingLevel level);

		friend class Application;


	};

}
#include "Console.h"
#include <stdint.h>
#include <map>
#include <bitset>
#include <string>
#include <iostream>
#include "ConsoleEntity.h"

namespace salt {

		void Console::addCommand(void(*foo)(), std::string name){
			if(name_command_map.count(name)){
				std::cout<<"Command \""<<name<<"\" has already been registered"<<std::endl;
				return;
			}
			name_command_map[name] = foo;
		}
	
		void Console::run(std::string command_name){
			if(name_command_map.count(command_name)){
				name_command_map[command_name]();
			}else{
				std::cout<<"No such command as \""<<command_name<<"\""<<std::endl;
			}
		}
	
		void Console::print(std::string str, const glm::vec3& color){
			createConsoleMessage(str, color);
		}



		void Console::logToConsole(const std::string& message, salt::Logging::LoggingLevel level){
			if(level == salt::Logging::LoggingLevel::DEBUG) createConsoleMessage(message, {1,1,1});
			if(level == salt::Logging::LoggingLevel::WARNING) createConsoleMessage(message, {1,1,0});
			if(level == salt::Logging::LoggingLevel::ERROR) createConsoleMessage(message, {1,0,0});
		}

		void Console::AttachToLogging(){
			salt::Logging::AttachConsoleLogging(&logToConsole);
		}


}
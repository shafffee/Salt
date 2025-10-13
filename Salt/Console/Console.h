#pragma once
#include <stdint.h>
#include <map>
#include <bitset>
#include <string>
#include <iostream>
#include "ConsoleEntity.h"

namespace salt::Console {

	std::map<std::string, void(*)()> name_command_map;

	void addCommand(void(*foo)(), std::string name){
		if(name_command_map.count(name)){
			std::cout<<"Command \""<<name<<"\" has already been registered"<<std::endl;
			return;
		}
		name_command_map[name] = foo;
	}

	void run(std::string command_name){
		if(name_command_map.count(command_name)){
			name_command_map[command_name]();
		}else{
			std::cout<<"No such command as \""<<command_name<<"\""<<std::endl;
		}
	}

	void print(std::string str){
		createConsoleMessage(str);
		std::cout<<str<<std::endl;
	}

}
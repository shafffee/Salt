#include "Logging.h"

#include <iostream>

namespace salt{

    void Logging::Debug(const std::string& message) {
      Log(message, DEBUG);
    }
    
    void Logging::Warning(const std::string& message) {
      Log(message, WARNING);
    }
    
    void Logging::Error(const std::string& message) {
      Log(message, ERROR);
    }

    void Logging::Log(const std::string& message, Logging::LoggingLevel level){

        history.push_back({message, level});

        if(LOG_TO_CMD){
            if(level == DEBUG) std::cout<<"[DEBUG]  \t";
            if(level == WARNING) std::cout<<"[WARNING]  \t";
            if(level == ERROR) std::cout<<"[ERROR]  \t";
            std::cout<<message<<std::endl;
        }

        if(LOG_TO_CONSOLE){
            if(_log_to_console)_log_to_console(message, level);
        };

    };

    void Logging::AttachConsoleLogging( void (*log_to_console)(const std::string&, LoggingLevel) ){
        _log_to_console = log_to_console;
        for(auto log: history){
            if(_log_to_console)_log_to_console(log.message, log.level);
        }
    };


}
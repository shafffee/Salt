#pragma once

#include <iostream>

namespace salt{

  class Logging{
  public:

    static void Debug(const std::string& message) {
      std::cout<<"[DEBUG]  \t"<<message<<std::endl;
    }
    
    static void Warning(const std::string& message) {
      std::cout<<"[WARNING]\t"<<message<<std::endl;
    }
    
    static void Error(const std::string& message) {
      std::cout<<"[ERROR]  \t"<<message<<std::endl;
    }

  };

}


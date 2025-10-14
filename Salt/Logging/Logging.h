#pragma once
#include <string>

#define LOG_TO_CMD true
#define LOG_TO_CONSOLE true

namespace salt{

  class Console;

  class Logging{
  public:

    enum LoggingLevel {DEBUG, WARNING, ERROR};

    static void Debug(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);

    static void Log(const std::string& message, LoggingLevel level);

  private:
    inline static void (*_log_to_console)(const std::string& message, LoggingLevel level) = nullptr;
    static void AttachConsoleLogging(void (*_log_to_console)(const std::string&, LoggingLevel));

    friend class Console;

  };

}


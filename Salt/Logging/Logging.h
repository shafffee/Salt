#pragma once
#include <string>
#include <vector>

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

    //used to save logging history (currently used to send it to console after it has been init)
    struct LogMessage{
      std::string message;
      LoggingLevel level;
      // Constructor
      LogMessage(const std::string& msg, LoggingLevel lvl) 
          : message(msg), level(lvl) {}
    };

    inline static std::vector<LogMessage> history;

    inline static void (*_log_to_console)(const std::string& message, LoggingLevel level) = nullptr;
    static void AttachConsoleLogging(void (*_log_to_console)(const std::string&, LoggingLevel));

    friend class Console;

  };


}


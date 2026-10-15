#pragma once

#include <sstream>

class Logger {

	public:
        enum class Level { Debug, Info, Warn, Error };

        explicit Logger(Logger::Level level);
        ~Logger();
              
        template <typename T>
        Logger& operator<<(const T& input) {
            _buffer << input;
            return *this;
        }

private:
    const Level _level;
    std::ostringstream _buffer;

    static const char* name(Level l) {
        switch (l) {
        case Logger::Level::Debug: return "DEBUG";
        case Logger::Level::Info:  return "INFO";
        case Logger::Level::Warn:  return "WARN";
        case Logger::Level::Error: return "ERROR";
        }
        return "UNKNOWN";
    }
};

#define LOG_DEBUG() Logger(Logger::Level::Debug)
#define LOG_INFO()  Logger(Logger::Level::Info)
#define LOG_WARN()  Logger(Logger::Level::Warn)
#define LOG_ERROR() Logger(Logger::Level::Error)
#define LOG()       LOG_INFO()
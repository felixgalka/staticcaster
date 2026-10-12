#pragma once

#include <cstdint>
#include <sstream>
#include <chrono>
#include <iostream>
#include <format>

namespace {
    constexpr std::size_t MAX_LOG_LENGTH = 512;

    std::string formatTimeZone(std::chrono::system_clock::time_point tp)
    {
        using namespace std::chrono;
        static auto const TZ = locate_zone("Etc/GMT-1");
        return std::format("{:%FT%T%z}", zoned_time{ TZ, floor<milliseconds>(tp) });
    }
}

class Logger {
	public:
        enum class Level { Debug, Info, Warn, Error };

        explicit Logger(Logger::Level level) : _level{ level }
            {};

            ~Logger() {
                try {
                    std::string msg = _buffer.str();

                    if (msg.size() > MAX_LOG_LENGTH) {
                        const std::size_t overflow = msg.size() - MAX_LOG_LENGTH;
                        msg.resize(MAX_LOG_LENGTH);
                        msg += std::format(" + {} characters truncated", overflow);
                    }

                    std::string timestamp{};
                    try {
                        timestamp = formatTimeZone(std::chrono::system_clock::now());
                    }
                    catch (...) {
                        timestamp = "[TIMESTAMP FAIL]";
                    }

                    const std::string line = std::format("[{}] {}: {}\n", timestamp, name(_level), msg);

                    std::ostream& out = (_level >= Level::Warn) ? std::cerr : std::cout;
                    out << line;
                }
                catch (...) {
                    // nothing sensible left to do; never throw from a destructor
                }
            }

        template <typename T>
        Logger& operator<<(const T& input) {
            _buffer << input;
            return *this;
        }

private:

    static const char* name(Level l) {
        switch (l) {
        case Logger::Level::Debug: return "DEBUG";
        case Logger::Level::Info:  return "INFO";
        case Logger::Level::Warn:  return "WARN";
        case Logger::Level::Error: return "ERROR";
        }
        return "UNKNOWN";
    }

	const Level _level;
    std::ostringstream _buffer;
};

#define LOG_DEBUG() Logger(Logger::Level::Debug)
#define LOG_INFO()  Logger(Logger::Level::Info)
#define LOG_WARN()  Logger(Logger::Level::Warn)
#define LOG_ERROR() Logger(Logger::Level::Error)
#define LOG()       LOG_INFO()
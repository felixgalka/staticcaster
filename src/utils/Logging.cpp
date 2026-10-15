#include "Logging.h"

#include <cstdint>
#include <chrono>
#include <iostream>
#include <format>

namespace {

    using namespace std::chrono;

    constexpr std::size_t MAX_LOG_LENGTH = 512;

    std::string formatTimeZone(std::chrono::system_clock::time_point tp)
    {
        static auto const TZ = locate_zone("Etc/GMT-1");
        return std::format("{:%FT%T%z}", zoned_time{ TZ, floor<milliseconds>(tp) });
    }
}

Logger(Logger::Level level) : _level{ level } {};

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
    catch (...) {}
}
#include "CLIParser.h"
#include "Logging.h"

#include <algorithm>
#include <string>

namespace {

    void displayHelpMessage() {
        LOG() << "Available commands:\n"
            << "--list : Displays a list of available devices\n"
            << "--input _ : Selects index _ as the input device\n"
            << "--output _ : Selects index _ as the output device\n"
            << "Example usage: staticcaster.exe device --list && staticcaster.exe device --output 2 --input 4";
    }

    bool IsInt(std::string_view s) {
        return !s.empty() && std::all_of(s.begin(), s.end(),
            [](unsigned char c) { return std::isdigit(c); });
    }

    std::optional<int> GetOptionalIntFromStr(std::string_view s) {
        if (IsInt(s)) {
            return std::stoi(std::string(s));
        }
        return std::nullopt;
    }
}

namespace CLIParser {

    std::optional<DeviceOptions> ParseDeviceArgs(std::span<const std::string_view> args) {
         
        const std::size_t argsLength = args.size();
        if (argsLength == 0) { return std::nullopt; }
        if (argsLength == 1 && args[0] == "device") {
            displayHelpMessage();
            return std::nullopt;
        }

        DeviceOptions opts{};

        for (std::size_t i{ 1 }; i < args.size(); ++i) {
            const std::string_view arg = args[i];

            if (arg == "--list") {
                opts.list = true;
            }
            else if (arg == "--input" || arg == "--output") {
                if (i + 1 >= args.size()) {
                    LOG_ERROR() << arg << " needs a value";
                    return std::nullopt;
                }
                const auto value = GetOptionalIntFromStr(args[++i]);
                if (!value) {
                    LOG_ERROR() << "Invalid number for: " << arg << " : " << args[i];
                    return std::nullopt;
                }
                (arg == "--input" ? opts.input : opts.output) = value;
            }
            else {
                LOG_ERROR() << "Unknown option: " << arg;
                return std::nullopt;
            }
        }
        return opts;
    }
}

#include <portaudio.h>

#include <optional>
#include <span>
#include <string_view>

struct DeviceOptions {
    bool list = false;
    std::optional<int> input;
    std::optional<int> output;
};

namespace CLIParser {
    std::optional<DeviceOptions> ParseDeviceArgs(std::span<const std::string_view> args);
}
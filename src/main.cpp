#include <portaudio.h>

#include "utils/Logging.h"
#include "utils/Types.h"
#include "utils/Devices.h"
#include "utils/CLIParser.h"
#include "audio/Context.h"
#include "audio/Stream.h"

#include <string_view>
#include <vector>

int main(int argc, char *argv[]) {
    LOG() << std::format("Portaudio version : {}", Pa_GetVersion());

    const Context ctx{ Context() };

    PaDeviceIndex input{Pa_GetDefaultInputDevice()};
    PaDeviceIndex output{Pa_GetDefaultOutputDevice()};

    const std::vector<std::string_view> args(argv + 1, argv + argc);
    const std::optional<DeviceOptions> _opts = CLIParser::ParseDeviceArgs(args);
        
    if (_opts) {
        const DeviceOptions opts = *_opts;
        if (opts.list) {
            Devices::Query();
            return 0;
        }
        if (opts.input) {
            input = *opts.input;
            LOG() << "Input chosen as: " << Pa_GetDeviceInfo(input)->name;
        }
        if (opts.output) {
            input = *opts.output; 
            LOG() << "Output chosen as: " << Pa_GetDeviceInfo(output)->name;
        }
    }

    const std::unique_ptr<TestData> data = std::make_unique<TestData>(0,0);
    // Stream stream{ paFloat32, callback, data.get() };
}



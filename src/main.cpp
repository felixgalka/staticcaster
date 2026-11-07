#include "audio/Context.h"
#include "audio/Engine.h"
#include "audio/fx/Distortion.h"
#include "audio/fx/Fuzz.h"
#include "audio/Stream.h"
#include "utils/CLIParser.h"
#include "utils/Devices.h"
#include "utils/Logging.h"
#include "utils/Types.h"

#include <portaudio.h>

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {
    LOG() << std::format("Portaudio version : {}", Pa_GetVersion());

    const Context ctx{Context()};

    PaDeviceIndex inputDevice{Pa_GetDefaultInputDevice()};
    PaDeviceIndex outputDevice{Pa_GetDefaultOutputDevice()};

    const std::vector<std::string_view> args(argv + 1, argv + argc);
    const std::optional<DeviceOptions> _opts = CLIParser::ParseDeviceArgs(args);

    if (_opts) {
        const DeviceOptions opts = *_opts;
        if (opts.list) {
            Devices::Query();
            return 0;
        }
        if (opts.input) {
            inputDevice = *opts.input;
        }
        if (opts.output) {
            outputDevice = *opts.output;
        }
    }
    LOG() << "Input chosen as: " << Pa_GetDeviceInfo(inputDevice)->name;
    LOG() << "Output chosen as: " << Pa_GetDeviceInfo(outputDevice)->name;

    PaStreamParameters in{};
    PaStreamParameters out{};

    in.device = inputDevice;
    in.channelCount = 1;
    in.sampleFormat = paFloat32;
    in.suggestedLatency = Pa_GetDeviceInfo(in.device)->defaultLowInputLatency;
    in.hostApiSpecificStreamInfo = nullptr;

    out.device = outputDevice;
    out.channelCount = 2;
    out.sampleFormat = paFloat32;
    out.suggestedLatency = Pa_GetDeviceInfo(out.device)->defaultLowOutputLatency;
    out.hostApiSpecificStreamInfo = nullptr;

    Types::StreamParams params{.in = in, .out = out, .framesPerBuffer = 256};
    auto engine{std::make_unique<AudioEngine>()};

    Stream stream{params, AudioEngine::Callback, engine.get()};
    engine->Prepare(256);
    stream.Start();

    std::cout << "Available commands during streaming:\n "
              << "q | quit :: Stops the stream\n"
              << "fuzz     :: Adds/removes fuzz effect\n"
              << "dist     :: Adds/removes distortion effect\n"
              << "voli [x] :: Increase volume by [x] amount\n"
              << "vold [x] :: Decrease volume by [x] amount\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream ss{line};
        std::string cmd;
        ss >> cmd;

        if (cmd == "quit" || cmd == "q")
            break;

        else if (cmd == "fuzz") {
            auto fuzzHandle = engine->GetEffect(Types::Effects::Fuzz);
            fuzzHandle->flag.store(!fuzzHandle->flag.load(std::memory_order_relaxed));
        } else if (cmd == "dist") {
            auto distHandle = engine->GetEffect(Types::Effects::Distortion);
            distHandle->flag.store(!distHandle->flag.load(std::memory_order_relaxed));
        } else if (cmd == "voli") {
            if (float v{}; ss >> v)
                engine->masterVolume.store(v);
        } else if (cmd == "voli") {
            if (float v{}; ss >> v)
                engine->masterVolume.store(v);
        }
    }

    stream.Stop();
}

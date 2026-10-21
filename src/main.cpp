#include <portaudio.h>

#include "utils/Logging.h"
#include "utils/Types.h"
#include "utils/Devices.h"
#include "utils/CLIParser.h"
#include "audio/Context.h"
#include "audio/Stream.h"

#include <string_view>
#include <vector>

static int patestCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    /* Cast data passed through stream to our structure. */
    Types::TestData* data = (Types::TestData*)userData;
    float* out = (float*)outputBuffer;
    unsigned int i;
    (void)inputBuffer; /* Prevent unused variable warning. */

    for (i = 0; i < framesPerBuffer; i++)
    {
        *out++ = data->left_phase;  /* left */
        *out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        if (data->left_phase >= 1.0f) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        data->right_phase += 0.03f;
        if (data->right_phase >= 1.0f) data->right_phase -= 2.0f;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    LOG() << std::format("Portaudio version : {}", Pa_GetVersion());

    const Context ctx{ Context() };

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
            LOG() << "Input chosen as: " << Pa_GetDeviceInfo(inputDevice)->name;
        }
        if (opts.output) {
            inputDevice = *opts.output; 
            LOG() << "Output chosen as: " << Pa_GetDeviceInfo(outputDevice)->name;
        }
    }
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

    Types::StreamParams params{ .in = in,.out = out ,.framesPerBuffer = 256 };

    const std::unique_ptr<Types::TestData> data = std::make_unique<Types::TestData>(0,0);
     
    Stream stream{ params, patestCallback, data.get() };
    stream.Start();
    stream.Stop();
}



#include "Engine.h"

#include <portaudio.h>

constexpr std::size_t NUM_OUTPUT_CHANNELS = 2;

int AudioEngine::Callback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo*,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    auto& eng{ *static_cast<AudioEngine*>(userData) };
    const auto frames{ static_cast<std::size_t>(frameCount) };

    const std::span<float> out{ static_cast<float*>(outputBuffer), frames * NUM_OUTPUT_CHANNELS };
    const std::span<float> buf{ eng.bufCopy.data(), frames };

    if (inputBuffer != nullptr) {
        const std::span<const float> in{ static_cast<const float*>(inputBuffer), frames };
        std::ranges::copy(in, buf.begin());
    }
    else {
        std::fill(buf.begin(), buf.end(), 0.0f);
    }

    eng.Process(buf);

    for (std::size_t i{ 0 }; i < frames; ++i) {
        out[i * NUM_OUTPUT_CHANNELS + 0] = buf[i];
        out[i * NUM_OUTPUT_CHANNELS + 1] = buf[i];
    }
    return paContinue;
}

void AudioEngine::Prepare(std::size_t maxFrames) { bufCopy.assign(maxFrames, 0.0f); } // Fill buffer copy with 0s

void AudioEngine::Process(std::span<float> buf) {
    if (!effects.load(std::memory_order_relaxed)) return;
    const float g = gain.load(std::memory_order_relaxed);
    for (float& f : buf) {
        f *= g;
    }
}

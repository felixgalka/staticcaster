#pragma once

#include <portaudio.h>

#include <atomic>
#include <span>
#include <ranges>
#include <algorithm>
#include <vector>

struct AudioEngine {

    std::atomic<float>    gain{ 1.0f };
    std::atomic<bool>     effects{ false };
    std::vector<float>    bufCopy;

    static int Callback(
        const void* inputBuffer,
        void* outputBuffer,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo*,
        PaStreamCallbackFlags statusFlags,
        void* userData);

    [[nodiscard]] static PaStreamCallback* GetCallback() noexcept { return &AudioEngine::Callback; };
    void Prepare(std::size_t maxFrames);
    void Process(std::span<float> buf);
};
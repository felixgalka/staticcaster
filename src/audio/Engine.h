#pragma once

#include "fx/IEffect.h"
#include "utils/Types.h"

#include <portaudio.h>

#include <atomic>
#include <ranges>
#include <vector>
#include <memory>
#include <cstdint>

struct AudioEngine {

    std::atomic<float>    masterVolume{ 1.0f };
    std::vector<float>    bufCopy;

    static int Callback(
        const void* inputBuffer,
        void* outputBuffer,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo*,
        PaStreamCallbackFlags statusFlags,
        void* userData);

    [[nodiscard]] static PaStreamCallback* GetCallback() noexcept { return &AudioEngine::Callback; };
    Effect* GetEffect(Types::Effects effect);
    void AddEffect(std::unique_ptr<Effect> effect);
    void Prepare(std::size_t maxFrames);
    void Process(std::span<float> buf);

    std::vector<std::unique_ptr<Effect>> effects;
};
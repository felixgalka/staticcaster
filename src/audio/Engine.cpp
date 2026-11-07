#include "Engine.h"

#include "fx/Distortion.h"
#include "fx/Fuzz.h"
#include "fx/Ieffect.h"
#include "utils/Types.h"

#include <portaudio.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <memory>
#include <span>

namespace {
    constexpr std::size_t NUM_OUTPUT_CHANNELS = 2;

    void Chain(std::span<float> buf, std::vector<std::unique_ptr<Effect>>& effects) {
        for (auto& effect : effects) {
            effect->Process(buf);
        }
    }
} // namespace

int AudioEngine::Callback(const void* inputBuffer, void* outputBuffer, unsigned long frameCount,
                          const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags statusFlags,
                          void* userData) {
    auto& eng{*static_cast<AudioEngine*>(userData)};
    const auto frames{static_cast<std::size_t>(frameCount)};

    const std::span<float> out{static_cast<float*>(outputBuffer), frames * NUM_OUTPUT_CHANNELS};
    const std::span<float> buf{eng.bufCopy.data(), frames};

    if (inputBuffer != nullptr) {
        const std::span<const float> in{static_cast<const float*>(inputBuffer), frames};
        std::ranges::copy(in, buf.begin());
    } else {
        std::fill(buf.begin(), buf.end(), 0.0f);
    }

    eng.Process(buf);

    for (std::size_t i{0}; i < frames; ++i) {
        out[i * NUM_OUTPUT_CHANNELS + 0] = buf[i];
        out[i * NUM_OUTPUT_CHANNELS + 1] = buf[i];
    }
    return paContinue;
}

Effect* AudioEngine::GetEffect(Types::Effects effect) {
    return effects[std::to_underlying(effect)].get();
}

void AudioEngine::AddEffect(std::unique_ptr<Effect> effect) {
    effects.push_back(std::move(effect));
}

void AudioEngine::Prepare(std::size_t maxFrames) {
    bufCopy.assign(maxFrames, 0.0f);

    auto fuzz{std::make_unique<Fuzz>()};
    this->AddEffect(std::move(fuzz));

    auto distortion{std::make_unique<Distortion>()};
    this->AddEffect(std::move(distortion));
}

void AudioEngine::Process(std::span<float> buf) {
    Chain(buf, effects);
    const float vol = masterVolume.load(std::memory_order_relaxed);
    for (float& f : buf) {
        f *= vol;
    }
}

#pragma once

#include "IEffect.h"

#include <atomic>
#include <cmath>
#include <cstdint>
#include <span>

struct Fuzz final : public Effect {
    std::atomic<uint16_t> drive{20};
    void Process(std::span<float> buf) override {
        if (flag.load(std::memory_order_relaxed)) {
            for (float& f : buf) {
                f = std::tanh(f * drive.load(std::memory_order_relaxed));
            }
        }
    }
};
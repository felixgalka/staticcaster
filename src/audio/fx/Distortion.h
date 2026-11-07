#pragma once

#include "IEffect.h"

#include <algorithm>
#include <span>
#include <atomic>
#include <cstdint>

struct Distortion final : public Effect {
    std::atomic<uint16_t> drive{ 20 };
    void Process(std::span<float> buf) override {
        if (flag.load(std::memory_order_relaxed)) {
            for (float& f : buf) {
                f = std::clamp(f * drive.load(std::memory_order_relaxed), -1.f, 1.f);
            }
        }
    }
};
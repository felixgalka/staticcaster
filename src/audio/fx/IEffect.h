#pragma once

#include <atomic>
#include <span>

struct Effect {
    virtual ~Effect() = default;
    virtual void Process(std::span<float> buf) = 0;

    std::atomic<bool> flag{false};
};
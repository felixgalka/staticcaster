#pragma once

#include <portaudio.h>

#include <cstdint>

namespace Types {
    
    struct StreamParams
    {
        PaStreamParameters in{};
        PaStreamParameters out{};
        int framesPerBuffer;
    };

    enum class Effects : uint8_t {
        Fuzz = 0,
        Distortion,
    };
}


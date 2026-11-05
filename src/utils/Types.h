#pragma once

#include <portaudio.h>

#include <atomic>
#include <span>
#include <ranges>
#include <algorithm>
#include <vector>

namespace Types {
    
    struct StreamParams
    {
        PaStreamParameters in{};
        PaStreamParameters out{};
        int framesPerBuffer;
    };
}


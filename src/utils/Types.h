#pragma once

#include <portaudio.h>

namespace Types {
    typedef struct
    {
        float left_phase;
        float right_phase;
    }
    TestData;

    typedef struct
    {
        PaStreamParameters in;
        PaStreamParameters out;
        int framesPerBuffer;
    }
    StreamParams;
}


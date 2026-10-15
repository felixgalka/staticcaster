#include <portaudio.h>

#include "utils/Logging.h"
#include "audio/AudioContext.h"

#include <iostream>
#include <format>


int main() {
    LOG() << "Main invoked";
    LOG() << std::format("Portaudio version : {}", Pa_GetVersion());

    auto ctx{ AudioContext() };
}


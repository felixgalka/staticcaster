#include "portaudio.h"

#include "Stream.h"

#include "utils/Errors.h"
#include "utils/Logging.h"
#include "utils/Types.h"

#include <cstdint>

#define SAMPLE_RATE 44100

Stream::Stream(PaSampleFormat fmt, PaStreamCallback* cb, TestData* data) {
    
    const PaError err = Pa_OpenDefaultStream(
        &stream_,
        0,
        2,
        fmt,
        SAMPLE_RATE,
        256,
        cb,
        &data);

    Errors::CheckFatal(err);
    LOG() << "Opened stream";
}

Stream::~Stream() {
    Errors::CheckNonFatal(Pa_CloseStream(stream_));
    LOG() << "Closed stream";

}

void Stream::Start() {
    Errors::CheckFatal(Pa_StartStream(stream_));
    LOG() << "Started stream";
}

void Stream::Stop() {
    Errors::CheckFatal(Pa_StopStream(stream_));
    LOG() << "Stopped stream";
}

void Stream::Abort() {
    Errors::CheckFatal(Pa_AbortStream(stream_));
    LOG() << "Aborted stream";
}


#include "portaudio.h"

#include "Stream.h"

#include "utils/Errors.h"
#include "utils/Logging.h"
#include "utils/Types.h"

#define SAMPLE_RATE 44100

Stream::Stream(Types::StreamParams params, PaStreamCallback* cb, Types::TestData* data) {
    
    const PaError err = Pa_OpenStream(
        &stream_,
        &params.in,
        &params.out,
        SAMPLE_RATE,
        params.framesPerBuffer,
        paNoFlag,
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


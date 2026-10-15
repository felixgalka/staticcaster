#include "portaudio.h"

#include "AudioContext.h"
#include "../utils/Logging.h"
#include "../utils/Errors.h"

#include <format>

AudioContext::AudioContext() { 
	LOG() << "Initialising PortAudio";
	PaError err = Pa_Initialize(); // Pa_Intialise must be called the same number of times as Pa_Terminate
	Errors::CheckFatal(err);
}

AudioContext::~AudioContext() {
	LOG() << "Terminating PortAudio";
	PaError err = Pa_Terminate();
	Errors::CheckNonFatal(err);
}
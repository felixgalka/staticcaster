#include "portaudio.h"

#include "Context.h"
#include "../utils/Logging.h"
#include "../utils/Errors.h"

Context::Context() { 
	LOG() << "Initialising PortAudio";
	PaError err = Pa_Initialize(); // Pa_Intialise must be called the same number of times as Pa_Terminate
	Errors::CheckFatal(err);
}

Context::~Context() {
	LOG() << "Terminating PortAudio";
	PaError err = Pa_Terminate();
	Errors::CheckNonFatal(err);
}
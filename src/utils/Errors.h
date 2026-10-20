#pragma once

#include <portaudio.h>

struct Errors {

	Errors() = default;
	~Errors() = default;

	static bool Check(PaError err);
	static void CheckFatal(PaError err);

	// Mainly for destructors, or where we simply want to log the error's message and not throw.
	static void CheckNonFatal(PaError err);

};
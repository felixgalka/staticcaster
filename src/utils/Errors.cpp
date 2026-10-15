#include "Errors.h"
#include "Logging.h"

#include <stdexcept>
#include <format>

bool Errors::Check(PaError err) {
	return err != paNoError;
}

void Errors::CheckFatal(PaError err) {
	if !(Check(err)) {
		return;
	}
	throw std::runtime_error(
		std::format("Error code: {}. Error text: {}", err, Pa_GetErrorText(err))
	);
}

void Errors::CheckNonFatal(PaError err) {
	if !(Check(err)) {
		return;
	}
	LOG_ERROR() << std::format("Error code: {}. Error text: {}", err, Pa_GetErrorText(err));
}
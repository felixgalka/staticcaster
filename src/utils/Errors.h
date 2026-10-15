#include <portaudio.h>

struct Errors {

	Errors::Errors() = default;
	Errors::~Errors() = default;

	static bool Check(PaError err);
	static void CheckFatal(paError err);
	static void CheckNonFatal(paError err);


};
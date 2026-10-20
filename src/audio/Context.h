#pragma once

/*
@brief RAII class to provide context from portaudio
*/
struct Context {

	Context();
	~Context();
	Context(const Context&) = delete;
	Context& operator= (const Context&) = delete;
};
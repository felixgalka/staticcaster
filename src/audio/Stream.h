#pragma once

#include "utils/Types.h"

#include <memory>
#include <utility>

class Stream {
public:
	Stream(Types::StreamParams params, PaStreamCallback* cb, void* userData);
	~Stream();
	Stream(const Stream&) = delete;
	Stream& operator= (const Stream&) = delete;

	void Start();
	void Stop();
	void Abort();

private:
	PaStream* stream_{};
};

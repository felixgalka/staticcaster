#pragma once

#include <memory>
#include "utils/Types.h"




class Stream {
public:
	Stream(PaSampleFormat fmt, PaStreamCallback* cb, TestData* data);
	~Stream();
	Stream(const Stream&) = delete;
	Stream& operator= (const Stream&) = delete;

	void Start();
	void Stop();
	void Abort();

private:
	PaStream* stream_{};
};

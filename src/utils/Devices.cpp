#include "Devices.h"

#include "utils/Errors.h"
#include "utils/Logging.h"

#include <cstdint>
#include <sstream>

namespace {
	
	std::string DeviceInfoToStr(const PaDeviceInfo& info, int idx) {
		std::ostringstream os;
		os << "Device: " << idx << ": " << (info.name ? info.name : "(unnamed)") << '\n'
		   << "  Host API index:      " << info.hostApi << '\n'
		   << "  Max input channels:  " << info.maxInputChannels << '\n'
		   << "  Max output channels: " << info.maxOutputChannels << '\n'
		   << "  Default sample rate: " << info.defaultSampleRate << " Hz\n"
		   << "  Low latency (in/out):  " << info.defaultLowInputLatency
		   << " / " << info.defaultLowOutputLatency << " s\n"
		   << "  High latency (in/out): " << info.defaultHighInputLatency
		   << " / " << info.defaultHighOutputLatency << " s";
		return os.str();
	}
} // namespace

namespace Devices { // Consider Devices as a class

	void Query() {
		int numDevices = Pa_GetDeviceCount();
		if (numDevices < 0) {
			Errors::CheckNonFatal(numDevices);
			return;
		}
		LOG() << numDevices << " devices available.";
		LOG() << "Default input device: " << Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->name;	
		LOG() << "Default output device: " << Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->name << "\n";

		for (uint8_t i{ 0 }; i < numDevices; i++) {
			const auto deviceInfo = Pa_GetDeviceInfo(i);
			if (deviceInfo != nullptr) {
				LOG() << DeviceInfoToStr(*deviceInfo, i);
			}
		}
	}
} // namespace Devices



#ifndef _Devices_AudioDeviceManager_h_
#define _Devices_AudioDeviceManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct AudioDevice {
	Upp::String name;
	Upp::String id;
	int input_channels;
	int output_channels;
	Upp::Vector<int> supported_sample_rates;
};

class AudioDeviceManager {
public:
	AudioDeviceManager();
	const Upp::Vector<AudioDevice>& GetAvailableDevices() const { return available_devices; }
	AudioDevice GetDefaultInputDevice() const;
	AudioDevice GetDefaultOutputDevice() const;
	bool SetInputDevice(const Upp::String& deviceId);
	bool SetOutputDevice(const Upp::String& deviceId);
	void RefreshDeviceList();
	
private:
	Upp::Vector<AudioDevice> available_devices;
	Upp::String current_input_device;
	Upp::String current_output_device;
};

}

#endif
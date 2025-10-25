#ifndef _Devices_AudioDeviceManager_h_
#define _Devices_AudioDeviceManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct AudioDevice {
	String name;
	String id;
	int input_channels;
	int output_channels;
	Vector<int> supported_sample_rates;
};

class AudioDeviceManager {
public:
	AudioDeviceManager();
	Vector<AudioDevice> GetAvailableDevices() const { return available_devices; }
	AudioDevice GetDefaultInputDevice() const;
	AudioDevice GetDefaultOutputDevice() const;
	bool SetInputDevice(const String& deviceId);
	bool SetOutputDevice(const String& deviceId);
	void RefreshDeviceList();
	
private:
	Vector<AudioDevice> available_devices;
	String current_input_device;
	String current_output_device;
};

}

#endif
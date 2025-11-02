#ifndef _Devices_AudioDeviceManager_h_
#define _Devices_AudioDeviceManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct AudioDevice : public Moveable<AudioDevice> {
	Upp::String name;
	Upp::String id;
	int input_channels = 0;
	int output_channels = 0;
	Upp::Vector<int> supported_sample_rates;
	bool is_default_input = false;
	bool is_default_output = false;
	
	// Add explicit constructors for U++ compatibility
	AudioDevice() = default;
	// Note: Cannot have copy constructor because Vector<int> has deleted copy constructor
	AudioDevice(AudioDevice&& other) = default;
	AudioDevice& operator=(AudioDevice&& other) = default;
};

class AudioDeviceManager {
public:
	AudioDeviceManager();
	Upp::Vector<AudioDevice> GetAvailableDevices() const;
	AudioDevice GetDefaultInputDevice() const;
	AudioDevice GetDefaultOutputDevice() const;
	bool SetInputDevice(const Upp::String& deviceId);
	bool SetOutputDevice(const Upp::String& deviceId);
	Upp::String GetCurrentInputDevice() const { return current_input_device; }
	Upp::String GetCurrentOutputDevice() const { return current_output_device; }
	void RefreshDeviceList();
	
private:
	Upp::Vector<AudioDevice> available_devices;
	Upp::String current_input_device;
	Upp::String current_output_device;
};

}

#endif
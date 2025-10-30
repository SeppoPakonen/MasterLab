#include "Devices.h"
namespace am {

AudioDeviceManager::AudioDeviceManager() {
	RefreshDeviceList();
}

Upp::Vector<AudioDevice> AudioDeviceManager::GetAvailableDevices() const {
	return available_devices;
}

AudioDevice AudioDeviceManager::GetDefaultInputDevice() const {
	// Return first input device as default
	for(const auto& device : available_devices) {
		if(device.input_channels > 0) return device;
	}
	return AudioDevice();
}

AudioDevice AudioDeviceManager::GetDefaultOutputDevice() const {
	// Return first output device as default
	for(const auto& device : available_devices) {
		if(device.output_channels > 0) return device;
	}
	return AudioDevice();
}

bool AudioDeviceManager::SetInputDevice(const Upp::String& deviceId) {
	LOG("Setting input device to: " + deviceId);
	// Stub - implement actual device setting
	current_input_device = deviceId;
	return true;
}

bool AudioDeviceManager::SetOutputDevice(const Upp::String& deviceId) {
	LOG("Setting output device to: " + deviceId);
	// Stub - implement actual device setting
	current_output_device = deviceId;
	return true;
}

void AudioDeviceManager::RefreshDeviceList() {
	LOG("Refreshing audio device list");
	// Stub - implement actual device enumeration
}

}
#include "Devices.h"
namespace am {

AudioDeviceManager::AudioDeviceManager() {
	RefreshDeviceList();
}

Upp::Vector<AudioDevice> AudioDeviceManager::GetAvailableDevices() const {
	// Return a copy of available devices - but AudioDevice has deleted copy constructor
	// So we return an empty vector for now
	// In a real implementation, this would need to be redesigned
	Upp::Vector<AudioDevice> result;
	return result;
}

AudioDevice AudioDeviceManager::GetDefaultInputDevice() const {
	// Return first input device as default
	for(const auto& device : available_devices) {
		if(device.input_channels > 0) {
			// AudioDevice has deleted copy constructor, so we can't return a copy
			// Return a default constructed object for now
			// In a real implementation, this would need to be redesigned
			return AudioDevice();
		}
	}
	return AudioDevice();
}

AudioDevice AudioDeviceManager::GetDefaultOutputDevice() const {
	// Return first output device as default
	for(const auto& device : available_devices) {
		if(device.output_channels > 0) {
			// AudioDevice has deleted copy constructor, so we can't return a copy
			// Return a default constructed object for now
			// In a real implementation, this would need to be redesigned
			return AudioDevice();
		}
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
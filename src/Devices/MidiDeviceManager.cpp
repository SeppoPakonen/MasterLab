#include "Devices.h"
namespace am {

MidiDeviceManager::MidiDeviceManager() {
	RefreshDeviceList();
}

Upp::Vector<MidiDevice> MidiDeviceManager::GetInputDevices() const {
	Upp::Vector<MidiDevice> result;
	for(const auto& device : available_devices) {
		if(device.is_input) result.Add(device);
	}
	return result;
}

Upp::Vector<MidiDevice> MidiDeviceManager::GetOutputDevices() const {
	Upp::Vector<MidiDevice> result;
	for(const auto& device : available_devices) {
		if(device.is_output) result.Add(device);
	}
	return result;
}

bool MidiDeviceManager::OpenInputDevice(const Upp::String& deviceId) {
	LOG("Opening MIDI input device: " + deviceId);
	// Stub - implement actual device opening
	// Use FindIndex instead of Find
	int index = open_input_devices.FindIndex(deviceId);
	if(index < 0) {
		open_input_devices.Add(deviceId);
	}
	return true;
}

bool MidiDeviceManager::OpenOutputDevice(const Upp::String& deviceId) {
	LOG("Opening MIDI output device: " + deviceId);
	// Stub - implement actual device opening
	// Use FindIndex instead of Find
	int index = open_output_devices.FindIndex(deviceId);
	if(index < 0) {
		open_output_devices.Add(deviceId);
	}
	return true;
}

void MidiDeviceManager::CloseInputDevice(const Upp::String& deviceId) {
	LOG("Closing MIDI input device: " + deviceId);
	// Stub - implement actual device closing
	// Use FindIndex instead of Find
	int pos = open_input_devices.FindIndex(deviceId);
	if(pos >= 0) {
		open_input_devices.Remove(pos);
	}
}

void MidiDeviceManager::CloseOutputDevice(const Upp::String& deviceId) {
	LOG("Closing MIDI output device: " + deviceId);
	// Stub - implement actual device closing
	// Use FindIndex instead of Find
	int pos = open_output_devices.FindIndex(deviceId);
	if(pos >= 0) {
		open_output_devices.Remove(pos);
	}
}

void MidiDeviceManager::RefreshDeviceList() {
	LOG("Refreshing MIDI device list");
	// Stub - implement actual device enumeration
}

}
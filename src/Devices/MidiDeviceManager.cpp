#include "Devices.h"
namespace am {

MidiDeviceManager::MidiDeviceManager() {
	RefreshDeviceList();
}

Vector<MidiDevice> MidiDeviceManager::GetInputDevices() const {
	Vector<MidiDevice> result;
	for(const auto& device : available_devices) {
		if(device.is_input) result.Add(device);
	}
	return result;
}

Vector<MidiDevice> MidiDeviceManager::GetOutputDevices() const {
	Vector<MidiDevice> result;
	for(const auto& device : available_devices) {
		if(device.is_output) result.Add(device);
	}
	return result;
}

bool MidiDeviceManager::OpenInputDevice(const String& deviceId) {
	LOG("Opening MIDI input device: " + deviceId);
	// Stub - implement actual device opening
	if(open_input_devices.Find(deviceId) < 0) {
		open_input_devices.Add(deviceId);
	}
	return true;
}

bool MidiDeviceManager::OpenOutputDevice(const String& deviceId) {
	LOG("Opening MIDI output device: " + deviceId);
	// Stub - implement actual device opening
	if(open_output_devices.Find(deviceId) < 0) {
		open_output_devices.Add(deviceId);
	}
	return true;
}

void MidiDeviceManager::CloseInputDevice(const String& deviceId) {
	LOG("Closing MIDI input device: " + deviceId);
	// Stub - implement actual device closing
	int pos = open_input_devices.Find(deviceId);
	if(pos >= 0) {
		open_input_devices.Remove(pos);
	}
}

void MidiDeviceManager::CloseOutputDevice(const String& deviceId) {
	LOG("Closing MIDI output device: " + deviceId);
	// Stub - implement actual device closing
	int pos = open_output_devices.Find(deviceId);
	if(pos >= 0) {
		open_output_devices.Remove(pos);
	}
}

void MidiDeviceManager::RefreshDeviceList() {
	LOG("Refreshing MIDI device list");
	// Stub - implement actual device enumeration
}

}
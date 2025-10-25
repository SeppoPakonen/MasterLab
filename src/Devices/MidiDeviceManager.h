#ifndef _Devices_MidiDeviceManager_h_
#define _Devices_MidiDeviceManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MidiDevice {
	String name;
	String id;
	bool is_input;
	bool is_output;
};

class MidiDeviceManager {
public:
	MidiDeviceManager();
	Vector<MidiDevice> GetAvailableDevices() const { return available_devices; }
	Vector<MidiDevice> GetInputDevices() const;
	Vector<MidiDevice> GetOutputDevices() const;
	bool OpenInputDevice(const String& deviceId);
	bool OpenOutputDevice(const String& deviceId);
	void CloseInputDevice(const String& deviceId);
	void CloseOutputDevice(const String& deviceId);
	void RefreshDeviceList();
	
private:
	Vector<MidiDevice> available_devices;
	Vector<String> open_input_devices;
	Vector<String> open_output_devices;
};

}

#endif
#ifndef _Devices_MidiDeviceManager_h_
#define _Devices_MidiDeviceManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MidiDevice {
	Upp::String name;
	Upp::String id;
	bool is_input;
	bool is_output;
};

class MidiDeviceManager {
public:
	MidiDeviceManager();
	const Upp::Vector<MidiDevice>& GetAvailableDevices() const { return available_devices; }
	Upp::Vector<MidiDevice> GetInputDevices() const;
	Upp::Vector<MidiDevice> GetOutputDevices() const;
	bool OpenInputDevice(const Upp::String& deviceId);
	bool OpenOutputDevice(const Upp::String& deviceId);
	void CloseInputDevice(const Upp::String& deviceId);
	void CloseOutputDevice(const Upp::String& deviceId);
	void RefreshDeviceList();
	
private:
	Upp::Vector<MidiDevice> available_devices;
	Upp::Vector<Upp::String> open_input_devices;
	Upp::Vector<Upp::String> open_output_devices;
};

}

#endif
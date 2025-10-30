#ifndef _Devices_VideoDevice_h_
#define _Devices_VideoDevice_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct VideoDeviceInfo {
	Upp::String name;
	Upp::String id;
	int width;
	int height;
	double frame_rate;
};

class VideoDevice {
public:
	VideoDevice();
	const Upp::Vector<VideoDeviceInfo>& GetAvailableDevices() const { return available_devices; }
	bool OpenDevice(const Upp::String& deviceId);
	void CloseDevice();
	bool IsOpen() const { return open; }
	void SetResolution(int width, int height);
	void SetFrameRate(double fps);
	
private:
	Upp::Vector<VideoDeviceInfo> available_devices;
	bool open = false;
	Upp::String current_device_id;
	int resolution_width = 1920;
	int resolution_height = 1080;
	double frame_rate = 30.0;
};

}

#endif
#ifndef _Devices_VideoDevice_h_
#define _Devices_VideoDevice_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct VideoDeviceInfo : public Moveable<VideoDeviceInfo> {
	Upp::String name;
	Upp::String id;
	int width = 0;
	int height = 0;
	double frame_rate = 0.0;
	
	// Add explicit constructors for U++ compatibility
	VideoDeviceInfo() = default;
	VideoDeviceInfo(const VideoDeviceInfo& other) = default;
	VideoDeviceInfo& operator=(const VideoDeviceInfo& other) = default;
	VideoDeviceInfo(VideoDeviceInfo&& other) = default;
	VideoDeviceInfo& operator=(VideoDeviceInfo&& other) = default;
};

class VideoDevice {
public:
	VideoDevice();
	Upp::Vector<VideoDeviceInfo> GetAvailableDevices() const;
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
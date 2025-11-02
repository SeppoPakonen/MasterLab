#include "Devices.h"
namespace am {

VideoDevice::VideoDevice() {
	// Initialize with default values
}

Upp::Vector<VideoDeviceInfo> VideoDevice::GetAvailableDevices() const {
	// Use <<= for deep copy to avoid copy constructor issues
	Upp::Vector<VideoDeviceInfo> result;
	result <<= available_devices;
	return result;
}

bool VideoDevice::OpenDevice(const Upp::String& deviceId) {
	LOG("Opening video device: " + deviceId);
	// Stub - implement actual device opening
	open = true;
	current_device_id = deviceId;
	return true;
}

void VideoDevice::CloseDevice() {
	LOG("Closing video device: " + current_device_id);
	// Stub - implement actual device closing
	open = false;
	current_device_id.Clear();
}

void VideoDevice::SetResolution(int width, int height) {
	LOG("Setting video resolution to: " + IntStr(width) + "x" + IntStr(height));
	resolution_width = width;
	resolution_height = height;
}

void VideoDevice::SetFrameRate(double fps) {
	LOG("Setting video frame rate to: " + DblStr(fps));
	frame_rate = fps;
}

}
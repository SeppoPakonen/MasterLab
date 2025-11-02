#include "Devices.h"
namespace am {

ReWireHost::ReWireHost() {
	RefreshAvailableApps();
}

bool ReWireHost::ConnectTo(const Upp::String& appName) {
	LOG("Connecting to ReWire app: " + appName);
	// Stub - implement actual ReWire connection
	// Use manual search instead of FindIndex
	int index = -1;
	for(int i = 0; i < available_apps.GetCount(); i++) {
		if(available_apps[i] == appName) {
			index = i;
			break;
		}
	}
	if(index >= 0) {
		connected = true;
		connected_app = appName;
		return true;
	}
	return false;
}

void ReWireHost::Disconnect() {
	LOG("Disconnecting from ReWire app: " + connected_app);
	// Stub - implement actual ReWire disconnection
	connected = false;
	connected_app.Clear();
}

void ReWireHost::RefreshAvailableApps() {
	LOG("Refreshing available ReWire apps");
	// Stub - implement actual app discovery
	available_apps.Clear();
	available_apps.Add("Reaper");
	available_apps.Add("Pro Tools");
	available_apps.Add("Cubase");
}

}
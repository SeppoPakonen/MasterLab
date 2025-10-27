#ifndef _Devices_ReWireHost_h_
#define _Devices_ReWireHost_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class ReWireHost {
public:
	ReWireHost();
	bool ConnectTo(const String& appName);
	void Disconnect();
	bool IsConnected() const { return connected; }
	void RefreshAvailableApps();
	const Vector<String>& GetAvailableApps() const { return available_apps; }
	
private:
	bool connected = false;
	String connected_app;
	Vector<String> available_apps;
};

}

#endif
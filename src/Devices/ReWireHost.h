#ifndef _Devices_ReWireHost_h_
#define _Devices_ReWireHost_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

class ReWireHost {
public:
	ReWireHost();
	bool ConnectTo(const Upp::String& appName);
	void Disconnect();
	bool IsConnected() const { return connected; }
	void RefreshAvailableApps();
	const Upp::Vector<Upp::String>& GetAvailableApps() const { return available_apps; }
	
private:
	bool connected = false;
	Upp::String connected_app;
	Upp::Vector<Upp::String> available_apps;
};

}

#endif
#ifndef _Windowing_WindowRegistry_h_
#define _Windowing_WindowRegistry_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class WindowRegistry {
public:
	WindowRegistry();
	void RegisterWindow(const Upp::String& name, TopWindow* window);
	void UnregisterWindow(const Upp::String& name);
	Upp::Vector<Upp::String> GetRegisteredWindows() const;
	void CloseAllWindows();
	void MinimizeAllWindows();
	void RestoreAllWindows();
	void CloseWindow(const Upp::String& name);
	void ActivateWindow(const Upp::String& name);
	
private:
	VectorMap<Upp::String, TopWindow*> registered_windows;
};

}

#endif
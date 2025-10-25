#ifndef _Windowing_WindowRegistry_h_
#define _Windowing_WindowRegistry_h_

#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

class WindowRegistry {
public:
	WindowRegistry();
	void RegisterWindow(const String& name, TopWindow* window);
	void UnregisterWindow(const String& name);
	Vector<String> GetRegisteredWindows() const;
	void CloseAllWindows();
	void MinimizeAllWindows();
	void RestoreAllWindows();
	void CloseWindow(const String& name);
	void ActivateWindow(const String& name);
	
private:
	HashMap<String, TopWindow*> registered_windows;
};

}

#endif
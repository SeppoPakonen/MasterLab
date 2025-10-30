#include "Windowing.h"
namespace am {

WindowRegistry::WindowRegistry() {
	// Initialize window registry
}

void WindowRegistry::RegisterWindow(const Upp::String& name, TopWindow* window) {
	LOG("Registering window: " + name);
	registered_windows.GetAdd(name) = window;
}

void WindowRegistry::UnregisterWindow(const Upp::String& name) {
	LOG("Unregistering window: " + name);
	registered_windows.RemoveKey(name);
}

Upp::Vector<Upp::String> WindowRegistry::GetRegisteredWindows() const {
	Upp::Vector<Upp::String> result;
	for(int i = 0; i < registered_windows.GetCount(); ++i) {
		result.Add(registered_windows.GetKey(i));
	}
	return result;
}

void WindowRegistry::CloseAllWindows() {
	LOG("Closing all registered windows");
	for(int i = 0; i < registered_windows.GetCount(); ++i) {
		TopWindow* window = registered_windows[i];
		if(window) {
			window->Close();
		}
	}
}

void WindowRegistry::MinimizeAllWindows() {
	LOG("Minimizing all registered windows");
	for(int i = 0; i < registered_windows.GetCount(); ++i) {
		TopWindow* window = registered_windows[i];
		if(window) {
			window->Minimize();
		}
	}
}

void WindowRegistry::RestoreAllWindows() {
	LOG("Restoring all registered windows");
	for(int i = 0; i < registered_windows.GetCount(); ++i) {
		TopWindow* window = registered_windows[i];
		if(window && !window->IsOpen()) {
			window->Open();
		}
	}
}

void WindowRegistry::CloseWindow(const Upp::String& name) {
	LOG("Closing window: " + name);
	if(registered_windows.Find(name) >= 0) {
		TopWindow* window = registered_windows.Get(name);
		if(window) {
			window->Close();
		}
	}
}

void WindowRegistry::ActivateWindow(const Upp::String& name) {
	LOG("Activating window: " + name);
	if(registered_windows.Find(name) >= 0) {
		TopWindow* window = registered_windows.Get(name);
		if(window) {
			window->Activate();
		}
	}
}

}
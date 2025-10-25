#include "Windowing.h"
namespace am {

WindowRegistry::WindowRegistry() {
	// Initialize window registry
}

void WindowRegistry::RegisterWindow(const String& name, TopWindow* window) {
	LOG("Registering window: " + name);
	registered_windows.GetAdd(name) = window;
}

void WindowRegistry::UnregisterWindow(const String& name) {
	LOG("Unregistering window: " + name);
	registered_windows.RemoveKey(name);
}

Vector<String> WindowRegistry::GetRegisteredWindows() const {
	Vector<String> result;
	for(const auto& kv : registered_windows) {
		result.Add(kv.key);
	}
	return result;
}

void WindowRegistry::CloseAllWindows() {
	LOG("Closing all registered windows");
	for(const auto& kv : registered_windows) {
		if(kv.value) {
			kv.value->Close();
		}
	}
}

void WindowRegistry::MinimizeAllWindows() {
	LOG("Minimizing all registered windows");
	for(const auto& kv : registered_windows) {
		if(kv.value) {
			kv.value->Minimize();
		}
	}
}

void WindowRegistry::RestoreAllWindows() {
	LOG("Restoring all registered windows");
	for(const auto& kv : registered_windows) {
		if(kv.value && !kv.value->IsOpen()) {
			kv.value->Open();
		}
	}
}

void WindowRegistry::CloseWindow(const String& name) {
	LOG("Closing window: " + name);
	if(registered_windows.Find(name) >= 0) {
		TopWindow* window = registered_windows.Get(name);
		if(window) {
			window->Close();
		}
	}
}

void WindowRegistry::ActivateWindow(const String& name) {
	LOG("Activating window: " + name);
	if(registered_windows.Find(name) >= 0) {
		TopWindow* window = registered_windows.Get(name);
		if(window) {
			window->Activate();
		}
	}
}

}
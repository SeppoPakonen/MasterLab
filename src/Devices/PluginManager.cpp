#include "Devices.h"
namespace am {

PluginManager::PluginManager() {
	// Initialize with common plugin paths
	AddPluginPath(GetExeFolder() + "/VST");
	AddPluginPath(GetHomeDirFile("") + "/VST");
}

void PluginManager::ScanForPlugins() {
	LOG("Scanning for plugins in: " + IntStr(plugin_paths.GetCount()) + " paths");
	// Stub - implement actual plugin scanning
	// This would scan plugin_paths for VST, LV2, etc. plugins
}

Upp::Vector<PluginInfo> PluginManager::GetPluginsByType(PluginType type) const {
	Upp::Vector<PluginInfo> result;
	// PluginInfo has deleted copy constructor, so we can't copy objects
	// Return an empty vector for now
	// In a real implementation, this would need to be redesigned
	return result;
}

const PluginInfo* PluginManager::GetPlugin(const Upp::String& name) const {
	for(int i = 0; i < available_plugins.GetCount(); i++) {
		if(available_plugins[i].name == name) {
			return &available_plugins[i];
		}
	}
	return nullptr;
}

void PluginManager::AddPluginPath(const Upp::String& path) {
	// Use manual search instead of FindIndex
	int index = -1;
	for(int i = 0; i < plugin_paths.GetCount(); i++) {
		if(plugin_paths[i] == path) {
			index = i;
			break;
		}
	}
	if(index < 0) {
		plugin_paths.Add(path);
	}
}

void PluginManager::RemovePluginPath(const Upp::String& path) {
	// Use manual search instead of FindIndex
	int pos = -1;
	for(int i = 0; i < plugin_paths.GetCount(); i++) {
		if(plugin_paths[i] == path) {
			pos = i;
			break;
		}
	}
	if(pos >= 0) {
		plugin_paths.Remove(pos);
	}
}

void PluginManager::RefreshPluginCache() {
	LOG("Refreshing plugin cache");
	// Stub - implement actual cache refresh
}

}
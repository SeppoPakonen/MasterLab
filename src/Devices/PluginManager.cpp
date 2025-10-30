#include "Devices.h"
namespace am {

PluginManager::PluginManager() {
	// Initialize with common plugin paths
	AddPluginPath(GetExeFolder() + "/VST");
	AddPluginPath(GetHomeDirFile() + "/VST");
}

void PluginManager::ScanForPlugins() {
	LOG("Scanning for plugins in: " + IntStr(plugin_paths.GetCount()) + " paths");
	// Stub - implement actual plugin scanning
	// This would scan plugin_paths for VST, LV2, etc. plugins
}

Vector<PluginInfo> PluginManager::GetPluginsByType(PluginType type) const {
	Vector<PluginInfo> result;
	for(const auto& plugin : available_plugins) {
		if(plugin.type == type) result.Add(plugin);
	}
	return result;
}

PluginInfo PluginManager::GetPlugin(const String& name) const {
	for(const auto& plugin : available_plugins) {
		if(plugin.name == name) return plugin;
	}
	return PluginInfo();
}

void PluginManager::AddPluginPath(const String& path) {
	if(plugin_paths.Find(path) < 0) {
		plugin_paths.Add(path);
	}
}

void PluginManager::RemovePluginPath(const String& path) {
	int pos = plugin_paths.Find(path);
	if(pos >= 0) {
		plugin_paths.Remove(pos);
	}
}

void PluginManager::RefreshPluginCache() {
	LOG("Refreshing plugin cache");
	// Stub - implement actual cache refresh
}

}
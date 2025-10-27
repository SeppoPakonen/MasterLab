#ifndef _Devices_PluginManager_h_
#define _Devices_PluginManager_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

enum PluginType {
	VST,
	LV2,
	LADSPA,
	CLAP
};

struct PluginInfo {
	String name;
	String vendor;
	String path;
	PluginType type;
	int version;
	Vector<String> parameters;  // Names of parameters
};

class PluginManager {
public:
	PluginManager();
	void ScanForPlugins();
	const Vector<PluginInfo>& GetAvailablePlugins() const { return available_plugins; }
	Vector<PluginInfo> GetPluginsByType(PluginType type) const;
	PluginInfo GetPlugin(const String& name) const;
	void AddPluginPath(const String& path);
	void RemovePluginPath(const String& path);
	void RefreshPluginCache();  // Cache of discovered plugins
	
private:
	Vector<PluginInfo> available_plugins;
	Vector<String> plugin_paths;
};

}

#endif
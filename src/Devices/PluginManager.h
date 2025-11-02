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

struct PluginInfo : public Moveable<PluginInfo> {
	Upp::String name;
	Upp::String vendor;
	Upp::String path;
	PluginType type;
	int version;
	Upp::Vector<Upp::String> parameters;  // Names of parameters
	
	// Add explicit constructors for U++ compatibility
	PluginInfo() = default;
	PluginInfo(const PluginInfo& other) = delete;
	PluginInfo& operator=(const PluginInfo& other) = delete;
	PluginInfo(PluginInfo&& other) = default;
	PluginInfo& operator=(PluginInfo&& other) = default;
};

class PluginManager {
public:
	PluginManager();
	void ScanForPlugins();
	const Upp::Vector<PluginInfo>& GetAvailablePlugins() const { return available_plugins; }
	Upp::Vector<PluginInfo> GetPluginsByType(PluginType type) const;
	const PluginInfo* GetPlugin(const Upp::String& name) const;
	void AddPluginPath(const Upp::String& path);
	void RemovePluginPath(const Upp::String& path);
	void RefreshPluginCache();  // Cache of discovered plugins
	
private:
	Upp::Vector<PluginInfo> available_plugins;
	Upp::Vector<Upp::String> plugin_paths;
};

}

#endif
#include "VSTHost.h"

CutePluginScan::CutePluginScan() {}
void CutePluginScan::SetPluginPaths(const Vector<String>& plugin_paths) { this->plugin_paths = plugin_paths; }
const Vector<String>& CutePluginScan::GetPluginPaths() const { return plugin_paths; }
int CutePluginScan::RunScan() { CutePluginFactory& factory = CutePluginFactory::Get(); factory.UpdatePluginPaths(plugin_paths); return factory.Scan(); }

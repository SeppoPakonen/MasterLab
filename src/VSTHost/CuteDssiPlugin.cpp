#include "VSTHost.h"

CuteDssiPluginType::CuteDssiPluginType() {}
bool CuteDssiPluginType::Open() { has_editor = true; return true; }
void CuteDssiPluginType::Close() { has_editor = false; }
bool CuteDssiPluginType::HasEditor() const { return has_editor; }
CuteDssiPlugin::CuteDssiPlugin() {}
bool CuteDssiPlugin::Activate() { active = true; return true; }
void CuteDssiPlugin::Deactivate() { active = false; }
void CuteDssiPlugin::ProcessEvents() {}

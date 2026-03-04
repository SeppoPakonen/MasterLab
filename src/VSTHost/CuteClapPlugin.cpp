#include "VSTHost.h"

CuteClapPluginType::CuteClapPluginType() : name("CLAP") {}
bool CuteClapPluginType::Open() { return true; }
void CuteClapPluginType::Close() {}
String CuteClapPluginType::GetName() const { return name; }

CuteClapPlugin::CuteClapPlugin() : label("Cute CLAP Plugin") {}
bool CuteClapPlugin::Open() { return true; }
void CuteClapPlugin::Close() { active = false; }
bool CuteClapPlugin::Activate() { active = true; return true; }
void CuteClapPlugin::Deactivate() { active = false; }
void CuteClapPlugin::Process() {}
String CuteClapPlugin::GetLabel() const { return label; }

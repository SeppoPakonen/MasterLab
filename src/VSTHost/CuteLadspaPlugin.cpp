#include "VSTHost.h"

CuteLadspaPluginType::CuteLadspaPluginType() {}
bool CuteLadspaPluginType::Open() { return true; }
void CuteLadspaPluginType::Close() {}
String CuteLadspaPluginType::GetLabel() const { return label; }
CuteLadspaPlugin::Param::Param() {}
void CuteLadspaPlugin::Param::SetValue(float value) { this->value = value; }
float CuteLadspaPlugin::Param::GetValue() const { return value; }
CuteLadspaPlugin::CuteLadspaPlugin() {}
bool CuteLadspaPlugin::Open() { return true; }
void CuteLadspaPlugin::Close() {}
void CuteLadspaPlugin::Process() {}
String CuteLadspaPlugin::GetName() const { return name; }

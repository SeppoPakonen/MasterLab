#include "VSTHost.h"

CuteLv2PluginType::CuteLv2PluginType() {}
bool CuteLv2PluginType::Open() { return true; }
void CuteLv2PluginType::Close() {}
String CuteLv2PluginType::GetUri() const { return uri; }
CuteLv2Plugin::Param::Param() {}
void CuteLv2Plugin::Param::SetValue(float value) { this->value = value; }
float CuteLv2Plugin::Param::GetValue() const { return value; }
CuteLv2Plugin::Property::Property() {}
void CuteLv2Plugin::Property::SetKey(const String& key) { this->key = key; }
const String& CuteLv2Plugin::Property::GetKey() const { return key; }
void CuteLv2Plugin::Property::SetValue(const Value& value) { this->value = value; }
const Value& CuteLv2Plugin::Property::GetValue() const { return value; }
CuteLv2Plugin::CuteLv2Plugin() {}
bool CuteLv2Plugin::Open() { return true; }
void CuteLv2Plugin::Close() { active = false; }
void CuteLv2Plugin::Activate() { active = true; }
void CuteLv2Plugin::Deactivate() { active = false; }
void CuteLv2Plugin::Process() {}

#include "MIDI.h"

CuteMidiControlPluginType::CuteMidiControlPluginType() {}
String CuteMidiControlPluginType::GetName() const { return name; }
CuteMidiControlPlugin::Param::Param() {}
void CuteMidiControlPlugin::Param::SetValue(float value) { this->value = value; }
float CuteMidiControlPlugin::Param::GetValue() const { return value; }
CuteMidiControlPlugin::CuteMidiControlPlugin() {}
bool CuteMidiControlPlugin::Open() { opened = true; return true; }
void CuteMidiControlPlugin::Close() { opened = false; }
void CuteMidiControlPlugin::Process() {}

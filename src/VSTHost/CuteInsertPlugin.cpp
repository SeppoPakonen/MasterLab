#include "VSTHost.h"

CuteInsertPluginType::CuteInsertPluginType() {}
String CuteInsertPluginType::GetName() const { return name; }
CuteInsertPlugin::Param::Param() {}
void CuteInsertPlugin::Param::SetName(const String& name) { this->name = name; }
const String& CuteInsertPlugin::Param::GetName() const { return name; }
CuteInsertPlugin::CuteInsertPlugin() {}
CuteInsertPlugin::~CuteInsertPlugin() {}
bool CuteInsertPlugin::Open() { opened = true; return true; }
void CuteInsertPlugin::Close() { opened = false; }

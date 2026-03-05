#include "VSTHost.h"

CuteVst2Plugin::CuteVst2Plugin() {}
bool CuteVst2Plugin::Activate() { active = true; SetActivated(true); return true; }
void CuteVst2Plugin::Deactivate() { active = false; SetActivated(false); }
void CuteVst2Plugin::Process() {}
bool CuteVst2Plugin::OpenEditor() { return CutePlugin::OpenEditor(); }
void CuteVst2Plugin::CloseEditor() { CutePlugin::CloseEditor(); }

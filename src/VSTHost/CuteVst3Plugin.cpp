#include "VSTHost.h"

CuteVst3Plugin::CuteVst3Plugin() {}
bool CuteVst3Plugin::Activate() { active = true; SetActivated(true); return true; }
void CuteVst3Plugin::Deactivate() { active = false; SetActivated(false); }
void CuteVst3Plugin::Process() {}
bool CuteVst3Plugin::OpenEditor() { return CutePlugin::OpenEditor(); }
void CuteVst3Plugin::CloseEditor() { CutePlugin::CloseEditor(); }

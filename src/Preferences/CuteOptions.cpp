#include "Preferences.h"

CuteOptions::CuteOptions() {}
void CuteOptions::LoadOptions() {}
void CuteOptions::SaveOptions() {}
bool CuteOptions::ParseArgs(const Vector<String>& args) { session_files = clone(args); return true; }
void CuteOptions::ShowError(const String& msg) { PromptOK(msg); }

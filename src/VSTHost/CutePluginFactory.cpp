#include "VSTHost.h"

CutePluginFactory::Scanner::Scanner() {}
bool CutePluginFactory::Scanner::Open() { is_open = true; return true; }
void CutePluginFactory::Scanner::Close() { is_open = false; }
void CutePluginFactory::Scanner::AddTypes(Vector<CutePluginType*>& type_list) const { for (const String& file : files) { type_list.Add(nullptr); (void)file; } }
const Vector<String>& CutePluginFactory::Scanner::GetFiles() const { return files; }
const VectorMap<String, String>& CutePluginFactory::Scanner::GetDummyPluginMap() const { return dummy_plugin_map; }

CutePluginFactory::CutePluginFactory() {}
void CutePluginFactory::SetTypeHint(CutePluginType::Hint type_hint) { this->type_hint = type_hint; }
CutePluginType::Hint CutePluginFactory::GetTypeHint() const { return type_hint; }
void CutePluginFactory::SetRescan(bool rescan) { this->rescan = rescan; }
bool CutePluginFactory::IsRescan() const { return rescan; }
int CutePluginFactory::Scan() { return types.GetCount(); }
const Array<CutePluginType>& CutePluginFactory::GetTypes() const { return types; }
CutePluginType& CutePluginFactory::AddType() { return types.Add(); }
void CutePluginFactory::Clear() { types.Clear(); }
void CutePluginFactory::ClearAll() { types.Clear(); plugin_paths.Clear(); blacklist.Clear(); }
Vector<String>& CutePluginFactory::GetPluginPaths() { return plugin_paths; }
const Vector<String>& CutePluginFactory::GetPluginPaths() const { return plugin_paths; }
void CutePluginFactory::UpdatePluginPaths(const Vector<String>& plugin_paths) { this->plugin_paths = plugin_paths; }
void CutePluginFactory::SetBlacklist(const Index<String>& blacklist) { this->blacklist = blacklist; }
const Index<String>& CutePluginFactory::GetBlacklist() const { return blacklist; }
CutePluginFactory& CutePluginFactory::Get() { static CutePluginFactory factory; return factory; }

CuteDummyPluginType::CuteDummyPluginType() {}
bool CuteDummyPluginType::Open() { return true; }
void CuteDummyPluginType::Close() {}
String CuteDummyPluginType::GetFilename() const { return GetFile() ? GetFile()->GetFilename() : String(); }

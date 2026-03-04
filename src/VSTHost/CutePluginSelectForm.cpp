#include "VSTHost.h"

CutePluginSelectForm::CutePluginSelectForm() { Title("Select Plugin"); Sizeable().Zoomable(); Add(plugin_table.SizePos()); plugin_table.AddColumn("Plugin"); plugin_table.AddColumn("Type"); }
void CutePluginSelectForm::SetPluginList(CutePluginList* plugin_list) { this->plugin_list = plugin_list; plugin_table.Clear(); if (!plugin_list) return; for (int i = 0; i < plugin_list->GetPluginCount(); ++i) { const CutePlugin* plugin = plugin_list->GetPlugin(i); plugin_table.Add(plugin ? plugin->GetLabel() : String(), plugin && plugin->GetType() ? CutePluginType::GetHintText(plugin->GetType()->GetTypeHint()) : String()); } }
CutePluginList* CutePluginSelectForm::GetPluginList() const { return plugin_list; }
int CutePluginSelectForm::GetPluginCount() const { return plugin_list ? plugin_list->GetPluginCount() : 0; }
String CutePluginSelectForm::GetPluginFilename() const { int row = plugin_table.GetCursor(); const CutePlugin* plugin = plugin_list ? plugin_list->GetPlugin(row) : nullptr; return plugin && plugin->GetType() && plugin->GetType()->GetFile() ? plugin->GetType()->GetFile()->GetFilename() : String(); }
int CutePluginSelectForm::GetPluginIndex() const { return plugin_table.GetCursor(); }
CutePluginType::Hint CutePluginSelectForm::GetPluginTypeHint() const { int row = plugin_table.GetCursor(); const CutePlugin* plugin = plugin_list ? plugin_list->GetPlugin(row) : nullptr; return plugin && plugin->GetType() ? plugin->GetType()->GetTypeHint() : CutePluginType::Any; }

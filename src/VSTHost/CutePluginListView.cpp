#include "VSTHost.h"

CutePluginListItem::CutePluginListItem() { Add(caption.HSizePosZ(8, 36).VSizePos()); Add(activated.RightPosZ(8, 20).VCenterPosZ(20)); }
void CutePluginListItem::SetPlugin(CutePlugin* plugin) { this->plugin = plugin; caption.SetLabel(plugin ? plugin->GetLabel() : String()); }
CutePlugin* CutePluginListItem::GetPlugin() const { return plugin; }
void CutePluginListItem::SetPluginForm(CutePluginForm* plugin_form) { this->plugin_form = plugin_form; }
CutePluginForm* CutePluginListItem::GetPluginForm() const { return plugin_form; }
void CutePluginListItem::UpdateActivated() { activated = plugin && plugin->IsActivated(); }
void CutePluginListItem::SetDirectAccessWidth(int direct_access_width) { this->direct_access_width = direct_access_width; }
int CutePluginListItem::GetDirectAccessWidth() const { return direct_access_width; }

CutePluginListView::CutePluginListView() { AddColumn("Plugin"); }
void CutePluginListView::SetPluginList(CutePluginList* plugin_list) { this->plugin_list = plugin_list; Refresh(); }
CutePluginList* CutePluginListView::GetPluginList() const { return plugin_list; }
void CutePluginListView::SetTinyScrollBar(bool tiny_scroll_bar) { this->tiny_scroll_bar = tiny_scroll_bar; }
bool CutePluginListView::IsTinyScrollBar() const { return tiny_scroll_bar; }
void CutePluginListView::Refresh() { Clear(); if (!plugin_list) return; for (int i = 0; i < plugin_list->GetPluginCount(); ++i) Add(plugin_list->GetPlugin(i)->GetLabel()); }
void CutePluginListView::Clear() { ArrayCtrl::Clear(); items.Clear(); }
CutePluginListItem* CutePluginListView::GetPluginItem(int index) { return index >= 0 && index < items.GetCount() ? &items[index] : nullptr; }
void CutePluginListView::InsertPluginBus(CutePluginList& plugin_list, CutePlugin& plugin) { plugin_list.AddPlugin(plugin); }
void CutePluginListView::UpdateAuxSendPluginBus(CutePluginList& plugin_list, const String& bus_name) { plugin_list.SetAudioOutputBusName(bus_name); }
void CutePluginListView::AddPlugin() {}
void CutePluginListView::RemovePlugin() {}
void CutePluginListView::MoveUpPlugin() { if (!plugin_list) return; int cursor = GetCursor(); if (cursor > 0) plugin_list->MovePlugin(cursor, cursor - 1); Refresh(); SetCursor(cursor - 1); }
void CutePluginListView::MoveDownPlugin() { if (!plugin_list) return; int cursor = GetCursor(); if (cursor >= 0 && cursor + 1 < plugin_list->GetPluginCount()) plugin_list->MovePlugin(cursor, cursor + 1); Refresh(); SetCursor(cursor + 1); }

#include "MIDI.h"

CuteMidiControlPluginWidget::CuteMidiControlPluginWidget() {
    Add(name_label.TopPos(0, 20).HSizePos());
    Add(mapping_list.VSizePos(20, 0).HSizePos());
    mapping_list.AddColumn("Control");
    mapping_list.AddColumn("Target");
}
void CuteMidiControlPluginWidget::SetPlugin(CuteMidiControlPlugin* plugin) { this->plugin = plugin; }
CuteMidiControlPlugin* CuteMidiControlPluginWidget::GetPlugin() const { return plugin; }

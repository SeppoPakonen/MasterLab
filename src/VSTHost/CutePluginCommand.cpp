#include "VSTHost.h"

CutePluginCommand::CutePluginCommand(const String& name, CutePluginList* plugin_list) : name(name), plugin_list(plugin_list) {}
CutePluginCommand::~CutePluginCommand() {}
const String& CutePluginCommand::GetName() const { return name; }
CutePluginList* CutePluginCommand::GetPluginList() const { return plugin_list; }
bool CutePluginCommand::Redo() { return true; }
bool CutePluginCommand::Undo() { return true; }
void CutePluginCommand::AddPlugin(CutePlugin* plugin) { plugins.Add(plugin); }
Vector<CutePlugin*>& CutePluginCommand::GetPlugins() { return plugins; }

CuteAddPluginCommand::CuteAddPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin) : CutePluginCommand("Add Plugin", plugin_list) { AddPlugin(plugin); }
bool CuteAddPluginCommand::Redo() { return true; }
bool CuteAddPluginCommand::Undo() { return true; }
CuteAddInsertPluginCommand::CuteAddInsertPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin) : CutePluginCommand("Add Insert Plugin", plugin_list) { AddPlugin(plugin); }
bool CuteAddInsertPluginCommand::Redo() { return true; }
bool CuteAddInsertPluginCommand::Undo() { return true; }
CuteAddAuxSendPluginCommand::CuteAddAuxSendPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin) : CutePluginCommand("Add Aux Send Plugin", plugin_list) { AddPlugin(plugin); }
bool CuteAddAuxSendPluginCommand::Redo() { return true; }
bool CuteAddAuxSendPluginCommand::Undo() { return true; }
CuteAddMidiControlPluginCommand::CuteAddMidiControlPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin) : CutePluginCommand("Add Midi Control Plugin", plugin_list) { AddPlugin(plugin); }
bool CuteAddMidiControlPluginCommand::Redo() { return true; }
bool CuteAddMidiControlPluginCommand::Undo() { return true; }
CuteAuxSendPluginCommand::CuteAuxSendPluginCommand(CutePluginList* plugin_list, CutePlugin* plugin, const String& bus_name) : CutePluginCommand("Aux Send Plugin", plugin_list), bus_name(bus_name) { AddPlugin(plugin); }
bool CuteAuxSendPluginCommand::Redo() { return true; }
bool CuteAuxSendPluginCommand::Undo() { return true; }
CuteAuxSendIOMatrixCommand::CuteAuxSendIOMatrixCommand(CutePluginList* plugin_list, CutePlugin* plugin, const String& matrix_text) : CutePluginCommand("Aux Send IO Matrix", plugin_list), matrix_text(matrix_text) { AddPlugin(plugin); }
bool CuteAuxSendIOMatrixCommand::Redo() { return true; }
bool CuteAuxSendIOMatrixCommand::Undo() { return true; }
CuteRemovePluginCommand::CuteRemovePluginCommand(CutePluginList* plugin_list, int plugin_index) : CutePluginCommand("Remove Plugin", plugin_list), plugin_index(plugin_index) {}
bool CuteRemovePluginCommand::Redo() { return true; }
bool CuteRemovePluginCommand::Undo() { return true; }
CuteInsertPluginCommand::CuteInsertPluginCommand(const String& name, CutePluginList* plugin_list, CutePlugin* plugin, int insert_index) : CutePluginCommand(name, plugin_list), insert_index(insert_index) { AddPlugin(plugin); }
bool CuteInsertPluginCommand::Redo() { return true; }
bool CuteInsertPluginCommand::Undo() { return true; }
CuteMovePluginCommand::CuteMovePluginCommand(CutePluginList* plugin_list, int from_index, int to_index) : CutePluginCommand("Move Plugin", plugin_list), from_index(from_index), to_index(to_index) {}
bool CuteMovePluginCommand::Redo() { if (GetPluginList()) GetPluginList()->MovePlugin(from_index, to_index); return true; }
bool CuteMovePluginCommand::Undo() { if (GetPluginList()) GetPluginList()->MovePlugin(to_index, from_index); return true; }

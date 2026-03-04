#include "Preferences.h"

CuteShortcutTableItemEdit::CuteShortcutTableItemEdit() {}
CuteShortcutTableItemEditor::CuteShortcutTableItemEditor() { Add(edit.SizePos()); }
void CuteShortcutTableItemEditor::SetText(const String& text) { edit.SetData(text); }
String CuteShortcutTableItemEditor::GetText() const { return edit.GetData(); }
void CuteShortcutTableItemEditor::SetIndex(int index) { this->index = index; }
int CuteShortcutTableItemEditor::GetIndex() const { return index; }
void CuteShortcutTableItemEditor::SetDefaultText(const String& default_text) { this->default_text = default_text; }
const String& CuteShortcutTableItemEditor::GetDefaultText() const { return default_text; }
void CuteShortcutTableItemEditor::Clear() { edit.Clear(); }
CuteShortcutTableItemDelegate::CuteShortcutTableItemDelegate() {}
CuteShortcutForm::CuteShortcutForm() { Title("Shortcuts"); Sizeable().Zoomable(); Add(table_widget.SizePos()); table_widget.AddColumn("Command"); table_widget.AddColumn("Shortcut"); }
ArrayCtrl& CuteShortcutForm::GetTableWidget() { return table_widget; }
void CuteShortcutForm::SetActionControl(CuteActionControl* action_control) { this->action_control = action_control; }
CuteActionControl* CuteShortcutForm::GetActionControl() const { return action_control; }
bool CuteShortcutForm::IsDirtyActionShortcuts() const { return dirty_action_shortcuts; }
bool CuteShortcutForm::IsDirtyActionControls() const { return dirty_action_controls; }
void CuteShortcutForm::CommitEditor() { dirty_action_shortcuts = true; }

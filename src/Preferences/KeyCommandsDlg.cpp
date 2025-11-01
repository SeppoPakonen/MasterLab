#include "Preferences.h"
#include "KeyCommandsDlg.h"
#include "WithPresetsLayout.h"
#include <CtrlLib/CtrlLib.h>
// using namespace Upp;  // Removed to avoid namespace conflicts

namespace am {

KeyCommandsDlg::KeyCommandsDlg() {
	Title("Key Commands");
	Sizeable().Zoomable();
	
	// Add controls to the dialog
	Add(functions_tree.LeftPos(0, 200).VSizePos(0, 30));
	Add(right_panel.HSizePos(200).VSizePos(0, 30));
	Add(presets_list.BottomPos(0, 25).HSizePos());
	Add(ok_btn.BottomPos(0, 25).RightPos(0, 80));
	Add(cancel_btn.BottomPos(0, 25).RightPos(80, 80));
	
	// Setup the functions tree
	functions_tree.NoWantFocus();
	functions_tree.WhenSel = THISBACK(OnTreeSel);
	
	// Setup keys array
	keys_array.AddColumn("Key", 150);
	keys_array.AddColumn("Description", 200);
	right_panel.Add(keys_array.HSizePos().VSizePos(0, 30));
	
	// Setup preset controls
	presets_list.Add("Default");
	presets_list.SetIndex(0);
	
	// Connect events
	ok_btn.WhenAction = THISBACK(OnOK);
	cancel_btn.WhenAction = THISBACK(OnCancel);
	
	// Load data
	DataIn();
}

void KeyCommandsDlg::DataIn() {
	// Load key commands
	key_commands.LoadCommands();
	
	// Populate the functions tree
	RefreshTree();
	
	// Populate presets list
	preset_names.Clear();
	preset_names.Add("Default");
	preset_names.Add("Custom");
	presets_list.Clear();
	for(const Upp::String& preset : preset_names) {
		presets_list.Add(preset);
	}
	presets_list.SetIndex(0);
}

void KeyCommandsDlg::DataOut() {
	// Save key commands
	key_commands.SaveCommands();
}

void KeyCommandsDlg::RefreshTree() {
	functions_tree.Clear();
	
	// Populate the tree with command categories
	// In U++, we need to use integer IDs for tree nodes
	int file_node = functions_tree.Add(0); // Root node for "File"
	functions_tree.SetLabel(file_node, "File");
	
	int new_project_node = functions_tree.Add(file_node);
	functions_tree.SetLabel(new_project_node, "New Project");
	int open_node = functions_tree.Add(file_node);
	functions_tree.SetLabel(open_node, "Open...");
	int save_node = functions_tree.Add(file_node);
	functions_tree.SetLabel(save_node, "Save");
	int save_as_node = functions_tree.Add(file_node);
	functions_tree.SetLabel(save_as_node, "Save As...");
	int close_node = functions_tree.Add(file_node);
	functions_tree.SetLabel(close_node, "Close");
	
	int edit_node = functions_tree.Add(0); // Root node for "Edit"
	functions_tree.SetLabel(edit_node, "Edit");
	
	int undo_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(undo_node, "Undo");
	int redo_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(redo_node, "Redo");
	int cut_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(cut_node, "Cut");
	int copy_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(copy_node, "Copy");
	int paste_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(paste_node, "Paste");
	int delete_node = functions_tree.Add(edit_node);
	functions_tree.SetLabel(delete_node, "Delete");
	
	int transport_node = functions_tree.Add(0); // Root node for "Transport"
	functions_tree.SetLabel(transport_node, "Transport");
	
	int play_node = functions_tree.Add(transport_node);
	functions_tree.SetLabel(play_node, "Play");
	int stop_node = functions_tree.Add(transport_node);
	functions_tree.SetLabel(stop_node, "Stop");
	int record_node = functions_tree.Add(transport_node);
	functions_tree.SetLabel(record_node, "Record");
	
	int preferences_node = functions_tree.Add(0); // Root node for "Preferences"
	functions_tree.SetLabel(preferences_node, "Preferences");
	
	int prefs_node = functions_tree.Add(preferences_node);
	functions_tree.SetLabel(prefs_node, "Preferences...");
}

void KeyCommandsDlg::OnTreeSel() {
	// When a function is selected in the tree, update the right panel
	Upp::LOG("Tree selection changed");
	// Implementation would update the keys array with shortcuts for the selected function
}

void KeyCommandsDlg::OnAssign() {
	// Assign the key in key_input to the currently selected function
	Upp::LOG("Assigning key: " + key_input.GetData());
	// Implementation would assign the key to the function and update the UI
}

void KeyCommandsDlg::OnDelete() {
	// Delete the selected shortcut
	Upp::LOG("Deleting selected key");
	// Implementation would remove the selected key from the array
}

void KeyCommandsDlg::OnPresetSel() {
	// Load the selected preset
	Upp::LOG("Loading preset");
}

void KeyCommandsDlg::OnPresetSave() {
	// Save the current key configuration as a preset
	Upp::LOG("Saving preset");
}

void KeyCommandsDlg::OnPresetOpen() {
	// Open the selected preset
	Upp::LOG("Opening preset");
}

void KeyCommandsDlg::OnPresetDelete() {
	// Delete the selected preset
	Upp::LOG("Deleting preset");
}

void KeyCommandsDlg::OnShowMacros() {
	// Toggle the visibility of the macro section
	Upp::LOG("Toggling macro section");
}

void KeyCommandsDlg::OnResetAll() {
	// Reset all key bindings to defaults
	Upp::LOG("Resetting all key bindings to defaults");
	key_commands.LoadCommands(); // Reload defaults
	RefreshTree();
}

void KeyCommandsDlg::OnOK() {
	// Save current configuration and close
	DataOut();
	Upp::OK();
}

void KeyCommandsDlg::OnCancel() {
	// Close without saving
	Upp::Cancel();
}

void KeyCommandsDlg::OnHelp() {
	// Show help
	Upp::LOG("Showing help");
}

}
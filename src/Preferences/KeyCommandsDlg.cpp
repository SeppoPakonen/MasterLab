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
	functions_tree.Set(file_node, "File", 0);
	
	int new_project_node = functions_tree.Add(file_node);
	functions_tree.Set(new_project_node, "New Project", 0);
	int open_node = functions_tree.Add(file_node);
	functions_tree.Set(open_node, "Open...", 0);
	int save_node = functions_tree.Add(file_node);
	functions_tree.Set(save_node, "Save", 0);
	int save_as_node = functions_tree.Add(file_node);
	functions_tree.Set(save_as_node, "Save As...", 0);
	int close_node = functions_tree.Add(file_node);
	functions_tree.Set(close_node, "Close", 0);
	
	int edit_node = functions_tree.Add(0); // Root node for "Edit"
	functions_tree.Set(edit_node, "Edit", 0);
	
	int undo_node = functions_tree.Add(edit_node);
	functions_tree.Set(undo_node, "Undo", 0);
	int redo_node = functions_tree.Add(edit_node);
	functions_tree.Set(redo_node, "Redo", 0);
	int cut_node = functions_tree.Add(edit_node);
	functions_tree.Set(cut_node, "Cut", 0);
	int copy_node = functions_tree.Add(edit_node);
	functions_tree.Set(copy_node, "Copy", 0);
	int paste_node = functions_tree.Add(edit_node);
	functions_tree.Set(paste_node, "Paste", 0);
	int delete_node = functions_tree.Add(edit_node);
	functions_tree.Set(delete_node, "Delete", 0);
	
	int transport_node = functions_tree.Add(0); // Root node for "Transport"
	functions_tree.Set(transport_node, "Transport", 0);
	
	int play_node = functions_tree.Add(transport_node);
	functions_tree.Set(play_node, "Play", 0);
	int stop_node = functions_tree.Add(transport_node);
	functions_tree.Set(stop_node, "Stop", 0);
	int record_node = functions_tree.Add(transport_node);
	functions_tree.Set(record_node, "Record", 0);
	
	int preferences_node = functions_tree.Add(0); // Root node for "Preferences"
	functions_tree.Set(preferences_node, "Preferences", 0);
	
	int prefs_node = functions_tree.Add(preferences_node);
	functions_tree.Set(prefs_node, "Preferences...", 0);
}

void KeyCommandsDlg::OnTreeSel() {
	// When a function is selected in the tree, update the right panel
	LOG("Tree selection changed");
	// Implementation would update the keys array with shortcuts for the selected function
}

void KeyCommandsDlg::OnAssign() {
	// Assign the key in key_input to the currently selected function
	LOG("Assigning key: " + AsString(key_input.GetData()));
	// Implementation would assign the key to the function and update the UI
}

void KeyCommandsDlg::OnDelete() {
	// Delete the selected shortcut
	LOG("Deleting selected key");
	// Implementation would remove the selected key from the array
}

void KeyCommandsDlg::OnPresetSel() {
	// Load the selected preset
	LOG("Loading preset");
}

void KeyCommandsDlg::OnPresetSave() {
	// Save the current key configuration as a preset
	LOG("Saving preset");
}

void KeyCommandsDlg::OnPresetOpen() {
	// Open the selected preset
	LOG("Opening preset");
}

void KeyCommandsDlg::OnPresetDelete() {
	// Delete the selected preset
	LOG("Deleting preset");
}

void KeyCommandsDlg::OnShowMacros() {
	// Toggle the visibility of the macro section
	LOG("Toggling macro section");
}

void KeyCommandsDlg::OnResetAll() {
	// Reset all key bindings to defaults
	LOG("Resetting all key bindings to defaults");
	key_commands.LoadCommands(); // Reload defaults
	RefreshTree();
}

void KeyCommandsDlg::OnOK() {
	// Save current configuration and close
	DataOut();
	Accept();
}

void KeyCommandsDlg::OnCancel() {
	// Close without saving
	Reject();
}

void KeyCommandsDlg::OnHelp() {
	// Show help
	LOG("Showing help");
}

}
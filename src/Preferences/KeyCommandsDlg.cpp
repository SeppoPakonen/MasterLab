#include "Preferences.h"
#include "KeyCommandsDlg.h"
#include "WithPresetsLayout.h"

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
	functions_tree.SetNodeText(file_node, "File");
	
	functions_tree.Add(file_node, Value(), "New Project");
	functions_tree.Add(file_node, Value(), "Open...");
	functions_tree.Add(file_node, Value(), "Save");
	functions_tree.Add(file_node, Value(), "Save As...");
	functions_tree.Add(file_node, Value(), "Close");
	
	int edit_node = functions_tree.Add(0); // Root node for "Edit"
	functions_tree.SetNodeText(edit_node, "Edit");
	
	functions_tree.Add(edit_node, Value(), "Undo");
	functions_tree.Add(edit_node, Value(), "Redo");
	functions_tree.Add(edit_node, Value(), "Cut");
	functions_tree.Add(edit_node, Value(), "Copy");
	functions_tree.Add(edit_node, Value(), "Paste");
	functions_tree.Add(edit_node, Value(), "Delete");
	
	int transport_node = functions_tree.Add(0); // Root node for "Transport"
	functions_tree.SetNodeText(transport_node, "Transport");
	
	functions_tree.Add(transport_node, Value(), "Play");
	functions_tree.Add(transport_node, Value(), "Stop");
	functions_tree.Add(transport_node, Value(), "Record");
	
	int preferences_node = functions_tree.Add(0); // Root node for "Preferences"
	functions_tree.SetNodeText(preferences_node, "Preferences");
	
	functions_tree.Add(preferences_node, Value(), "Preferences...");
}

void KeyCommandsDlg::OnTreeSel() {
	// When a function is selected in the tree, update the right panel
	LOG("Tree selection changed");
	// Implementation would update the keys array with shortcuts for the selected function
}

void KeyCommandsDlg::OnAssign() {
	// Assign the key in key_input to the currently selected function
	LOG("Assigning key: " + key_input.GetData());
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
	OK();
}

void KeyCommandsDlg::OnCancel() {
	// Close without saving
	Cancel();
}

void KeyCommandsDlg::OnHelp() {
	// Show help
	LOG("Showing help");
}

}
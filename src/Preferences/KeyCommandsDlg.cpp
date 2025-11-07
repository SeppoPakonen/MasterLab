#include "Preferences.h"
#include "KeyCommandsDlg.h"
#include "WithPresetsLayout.h"
#include <CtrlLib/CtrlLib.h>
#include <ProjectMgmt/AK.h>
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
	
	// Get all key commands to build the tree
	const Vector<KeyCommand>& all_commands = key_commands.GetCommands();
	
	// Group commands by category (based on description)
	VectorMap<String, Vector<int>> categories;
	
	for (int i = 0; i < all_commands.GetCount(); i++) {
		const KeyCommand& cmd = all_commands[i];
		String category = cmd.description;
		
		// Extract the category part (before the last slash)
		int last_slash = category.ReverseFind('/');
		if (last_slash != -1) {
			String cat_name = category.Mid(0, last_slash);
			String func_name = category.Mid(last_slash + 1);
			categories.GetAdd(cat_name).Add(i);
		} else {
			// If no slash, put in "Other" category
			categories.GetAdd("Other").Add(i);
		}
	}
	
	// Build the tree from the categorized commands
	for (int cat_idx = 0; cat_idx < categories.GetCount(); cat_idx++) {
		const String& category = categories.GetKey(cat_idx);
		const Vector<int>& cmd_indices = categories[cat_idx];
		
		// Add category node
		int cat_node = functions_tree.Add(0, CtrlImg::smallright(), category);
		functions_tree.Set(cat_node, category);
		
		// Add command nodes under this category
		for (int idx : cmd_indices) {
			const KeyCommand& cmd = all_commands[idx];
			String func_name = cmd.description;
			
			// Extract just the function name part (after the last slash)
			int last_slash = func_name.ReverseFind('/');
			if (last_slash != -1) {
				func_name = func_name.Mid(last_slash + 1);
			}
			
			// Add command node
			int cmd_node = functions_tree.Add(cat_node, CtrlImg::smallright(), func_name);
			
			// Set the command description in the node
			functions_tree.Set(cmd_node, func_name);
		}
		
		// Expand the category
		functions_tree.Open(cat_node, true);
	}
}

void KeyCommandsDlg::OnTreeSel() {
	// When a function is selected in the tree, update the right panel
	LOG("Tree selection changed");
	
	int sel_node = functions_tree.GetCursor();
	if (sel_node < 0) return;
	
	// Get the node text value which represents the command description
	Value node_value = functions_tree.Get(sel_node);
	if (!node_value.Is<String>()) return;
	String node_text = node_value;
	
	// Find the key command that matches this node text
	const Vector<KeyCommand>& all_commands = key_commands.GetCommands();
	const KeyCommand* found_cmd = nullptr;
	for (const KeyCommand& cmd : all_commands) {
		if (cmd.description == node_text) {
			found_cmd = &cmd;
			break;
		}
	}
	
	if (!found_cmd) return;
	
	// Update the keys array with this command's key sequence
	keys_array.Clear();
	if (!found_cmd->key_sequence.IsEmpty()) {
		keys_array.Add(found_cmd->key_sequence, found_cmd->description);
	}
}

void KeyCommandsDlg::OnAssign() {
	// Assign the key in key_input to the currently selected function
	LOG("Assigning key: " + AsString(key_input.GetData()));
	
	int sel_node = functions_tree.GetCursor();
	if (sel_node < 0) return;
	
	// Get the node text value which represents the command description
	Value node_value = functions_tree.Get(sel_node);
	if (!node_value.Is<String>()) return;
	String node_text = node_value;
	
	// Find the key command that matches this node text
	const Vector<KeyCommand>& all_commands = key_commands.GetCommands();
	const KeyCommand* found_cmd = nullptr;
	for (const KeyCommand& cmd : all_commands) {
		if (cmd.description == node_text) {
			found_cmd = &cmd;
			break;
		}
	}
	
	if (!found_cmd) return;
	
	String new_key_sequence = AsString(key_input.GetData());
	
	// Update the command with the new key sequence
	key_commands.UpdateCommand(found_cmd->command_id, new_key_sequence);
	
	// Update UI
	OnTreeSel(); // Refresh the keys array
}

void KeyCommandsDlg::OnDelete() {
	// Delete the selected shortcut
	LOG("Deleting selected key");
	
	int sel_node = functions_tree.GetCursor();
	if (sel_node < 0) return;
	
	// Get the node text value which represents the command description
	Value node_value = functions_tree.Get(sel_node);
	if (!node_value.Is<String>()) return;
	String node_text = node_value;
	
	// Find the key command that matches this node text
	const Vector<KeyCommand>& all_commands = key_commands.GetCommands();
	const KeyCommand* found_cmd = nullptr;
	for (const KeyCommand& cmd : all_commands) {
		if (cmd.description == node_text) {
			found_cmd = &cmd;
			break;
		}
	}
	
	if (!found_cmd) return;
	
	// Clear the key sequence for this command
	key_commands.UpdateCommand(found_cmd->command_id, "");
	
	// Update UI
	OnTreeSel(); // Refresh the keys array
}

void KeyCommandsDlg::OnPresetSel() {
	// Load the selected preset
	LOG("Loading preset: " + AsString(presets_list.Get())); // Use Get() instead of GetText()
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
	
	// Update UI
	RefreshTree();
	OnTreeSel();
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
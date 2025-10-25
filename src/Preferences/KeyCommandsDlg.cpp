#include "Preferences.h"
#include "KeyCommandsDlg.h"
#include "WithPresetsLayout.h"

namespace am {

KeyCommandsDlg::KeyCommandsDlg() {
	Title("Key Commands");
	Sizeable().Zoomable();
	
	// Top row controls
	TopMargin(25);
	
	// Initialize top row
	open_all.SetImage(AwpImg::plus()).SetToolTip("Open All");
	close_all.SetImage(AwpImg::minus()).SetToolTip("Close All");
	
	// Top row layout
	ToolBar top_toolbar;
	top_toolbar.Add(open_all);
	top_toolbar.Add(close_all);
	top_toolbar.Add(search_filter.HSizePos());
	top_toolbar.Add(search_btn.SetLabel("Search").SetImage(AwpImg::magnifying_glass()));
	
	AddTop(top_toolbar);
	
	// Main content
	main_splitter.Horz(3300, 6700); // 33% for tree, 66% for right panel
	
	// Initialize functions tree
	functions_tree.NoWantFocus();
	functions_tree.WhenSel = THISBACK(OnTreeSel);
	
	// Initialize keys array (for shortcuts)
	keys_array.AddColumn("Key", 150);
	keys_array.AddColumn("Description", 200);
	
	// Initialize macro section (hidden initially)
	macro_splitter.Horz(5000, 5000); // Initially right section is hidden (macro section)
	
	macros_tree.NoWantFocus();
	
	new_macro_btn.SetLabel("New Macro");
	add_command_btn.SetLabel("Add Command");
	macro_delete_btn.SetLabel("Delete");
	
	// Setup right panel controls
	right_panel.Add(keys_array.VSizePos(0, 20).HSizePos());
	right_panel.Add(delete_key_btn.VSizePos(25, 45).HSizePos());
	delete_key_btn.SetLabel("Delete").SetImage(AwpImg::trashbin());
	right_panel.Add(assign_btn.VSizePos(50, 70).HSizePos());
	assign_btn.SetLabel("Assign");
	right_panel.Add(key_input.VSizePos(75, 95).HSizePos());
	key_input.SetPrompt("Press keys to assign...");
	right_panel.Add(assigned_to_label.VSizePos(100, 115).HSizePos());
	assigned_to_label.SetLabel("Assigned to:");
	right_panel.Add(colliding_function.VSizePos(120, 135).HSizePos());
	select_btn.SetLabel("Select");
	right_panel.Add(select_btn.VSizePos(140, 160).HSizePos());
	
	// Presets section - using layout
	CtrlLayoutOKCancel(presets_layout, "Presets");
	presets_layout.preset_list = presets_list;
	presets_layout.preset_save = preset_save_btn;
	presets_layout.preset_delete = preset_delete_btn;
	presets_layout.preset_open = preset_open_btn;
	
	// Add presets controls to bottom area
	BottomPos(25, 25).HSizePos(); // Position presets in bottom area
	
	// Bottom row buttons
	help_btn.SetLabel("Help");
	show_macros_btn.SetLabel("Show Macros");
	reset_all_btn.SetLabel("Reset All");
	ok_btn.SetLabel("OK");
	cancel_btn.SetLabel("Cancel");
	
	// Button layout - align left and right
	StaticRect button_bg;
	button_bg.SetFrame(1);
	
	// Create a layout for bottom buttons
	ToolBar button_bar;
	button_bar.Right().Add(help_btn);
	button_bar.Right().Add(show_macros_btn);
	button_bar.Right().Add(reset_all_btn);
	button_bar.Right().Add(ok_btn);
	button_bar.Right().Add(cancel_btn);
	
	AddBottom(button_bar);
	
	// Add the main splitter to the window
	Add(main_splitter.SizePos(25, 50, 0, 25)); // Below top row, above preset buttons, above bottom buttons
	main_splitter << functions_tree << right_panel;
	
	// Connect events
	assign_btn.WhenAction = THISBACK(OnAssign);
	delete_key_btn.WhenAction = THISBACK(OnDelete);
	presets_list.WhenAction = THISBACK(OnPresetSel);
	preset_save_btn.WhenAction = THISBACK(OnPresetSave);
	preset_open_btn.WhenAction = THISBACK(OnPresetOpen);
	preset_delete_btn.WhenAction = THISBACK(OnPresetDelete);
	show_macros_btn.WhenAction = THISBACK(OnShowMacros);
	reset_all_btn.WhenAction = THISBACK(OnResetAll);
	ok_btn.WhenAction = THISBACK(OnOK);
	cancel_btn.WhenAction = THISBACK(OnCancel);
	help_btn.WhenAction = THISBACK(OnHelp);
	
	// Initially hide macro section
	macro_splitter.SetPos(9999); // Hide the macro section initially
	
	// Load data
	DataIn();
}

void KeyCommandsDlg::DataIn() {
	// Load key commands
	key_commands.LoadCommands();
	
	// Populate the functions tree
	RefreshTree();
	
	// Populate presets list (for now, just add a default)
	preset_names.Clear();
	preset_names.Add("Default");
	preset_names.Add("Custom");
	presets_list.Clear();
	for(const String& preset : preset_names) {
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
	TreeCtrl::Node& file_node = functions_tree.Add("File");
	file_node.Add("New Project");
	file_node.Add("Open...");
	file_node.Add("Save");
	file_node.Add("Save As...");
	file_node.Add("Close");
	
	TreeCtrl::Node& edit_node = functions_tree.Add("Edit");
	edit_node.Add("Undo");
	edit_node.Add("Redo");
	edit_node.Add("Cut");
	edit_node.Add("Copy");
	edit_node.Add("Paste");
	edit_node.Add("Delete");
	
	TreeCtrl::Node& transport_node = functions_tree.Add("Transport");
	transport_node.Add("Play");
	transport_node.Add("Stop");
	transport_node.Add("Record");
	
	TreeCtrl::Node& preferences_node = functions_tree.Add("Preferences");
	preferences_node.Add("Preferences...");
	
	// Add more categories as needed...
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
	if (macro_splitter.GetPos() == 9999) {
		// Show macro section
		macro_splitter.SetPos(5000); // 50/50 split
		main_splitter.Clear();
		main_splitter << functions_tree << macro_splitter;
		macro_splitter << macros_tree << macro_panel;
		show_macros_btn.SetLabel("Hide Macros");
	} else {
		// Hide macro section, go back to functions view
		macro_splitter.SetPos(9999);
		main_splitter.Clear();
		main_splitter << functions_tree << right_panel;
		show_macros_btn.SetLabel("Show Macros");
	}
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
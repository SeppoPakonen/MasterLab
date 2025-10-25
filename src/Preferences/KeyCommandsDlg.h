#ifndef _Preferences_KeyCommandsDialog_h_
#define _Preferences_KeyCommandsDialog_h_

#include <CtrlLib/CtrlLib.h>
#include "KeyCommands.h"
#include <ProjectMgmt/AK.h>
using namespace Upp;

namespace am {

// Key Commands dialog implementation
class KeyCommandsDlg : public TopWindow {
public:
	typedef KeyCommandsDlg CLASSNAME;
	KeyCommandsDlg();
	
private:
	void DataIn();
	void DataOut();
	void RefreshTree();
	void OnTreeSel();
	void OnAssign();
	void OnDelete();
	void OnPresetSel();
	void OnPresetSave();
	void OnPresetOpen();
	void OnPresetDelete();
	void OnShowMacros();
	void OnResetAll();
	void OnOK();
	void OnCancel();
	void OnHelp();
	
	// Top row controls
	Button open_all, close_all;
	EditString search_filter;
	Button search_btn;
	
	// Main area - horizontal splitter
	Splitter main_splitter;
	TreeCtrl functions_tree;     // Left side - functions
	ParentCtrl right_panel;      // Right side - controls for shortcuts
	
	// Right panel controls
	ArrayCtrl keys_array;        // ArrayCtrl(Columns=Keys) - Shortcut keyboard keys for selected TreeCtrl item
	Button delete_key_btn;
	Button assign_btn;
	EditString key_input;        // EditString that listens to keyboard events
	Label assigned_to_label;     // "Assigned to:" label
	Label colliding_function;    // Label showing function that already has the shortcut
	Button select_btn;           // Button to set TreeCtrl cursor to colliding function
	
	// Presets section
	Label presets_label;
	DropList presets_list;
	Button preset_save_btn;
	Button preset_delete_btn;
	Button preset_open_btn;
	
	// Macro section - initially hidden
	Splitter macro_splitter;
	TreeCtrl macros_tree;        // TreeCtrl for macros
	ParentCtrl macro_panel;      // ParentCtrl for macro controls
	Button new_macro_btn;
	Button add_command_btn;
	Button macro_delete_btn;
	
	// Bottom row buttons
	Button help_btn;
	Button show_macros_btn;
	Button reset_all_btn;
	Button ok_btn;
	Button cancel_btn;
	
	// Internal state
	KeyCommands key_commands;
	Vector<String> preset_names;
};

}

#endif
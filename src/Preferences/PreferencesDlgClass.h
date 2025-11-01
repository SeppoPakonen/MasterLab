class PreferencesDlg : public TopWindow {
public:
	typedef PreferencesDlg CLASSNAME;
	PreferencesDlg();
	
private:
	void DataIn();
	void DataOut();
	void RefreshTree();
	void SelectTree(const Upp::String& category, const Upp::String& subcategory);
	void OnTreeSel();
	void OnApply();
	void OnOK();
	void OnCancel();
	void OnDefaults();
	void OnHelp();
	void OnPresetChange();
	void OnPresetStore();
	void OnPresetRename();
	void OnPresetDelete();
	
	// UI elements
	Upp::TreeCtrl tree;
	Upp::Splitter main_splitter;
	Upp::ParentCtrl right_panel;
	Upp::DropList presets_list;
	Upp::Button preset_save_btn;
	Upp::Button preset_rename_btn;
	Upp::Button preset_delete_btn;
	Upp::Button preset_open_btn;
	Upp::Option preset_marked_only;
	Upp::Button apply;
	Upp::Button ok;
	Upp::Button cancel;
	Upp::Button defaults;
	Upp::Button help;
	
	// View holder for preference panels
	Upp::ParentCtrl view_holder;
	
	PreferencesPane* current_panel = nullptr;
	PreferencesModel model;
	Upp::Button preset_store;
	
	// Preset manager
	PreferencePresetManager preset_mgr;
};
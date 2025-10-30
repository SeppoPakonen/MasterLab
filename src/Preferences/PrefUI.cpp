#include "Preferences.h"
namespace am {

// PreferencesPane implementation
PreferencesPane::PreferencesPane() {
	// Initialize the base preference pane
}

StaticRect PreferencesPane::CreateColorRect(const Color& color) {
	StaticRect rect;
	rect.SetFrame(Single(1));
	rect.SetRect(0, 0, 20, 20);
	rect.SetInk(color);
	return rect;
}

Ctrl& PreferencesPane::CreateLabeledSlider(const Upp::String& label, int min, int max, int default_value) {
	auto* row = new LabeledSlider(label, min, max, default_value);
	return *row;
}

Ctrl& PreferencesPane::CreateLabeledOption(const Upp::String& label, bool default_value) {
	auto* row = new LabeledOption(label, default_value);
	return *row;
}

Ctrl& PreferencesPane::CreateLabeledDropList(const Upp::String& label, const Upp::Vector<Upp::String>& options, int default_index) {
	auto* row = new LabeledDropList(label, options, default_index);
	return *row;
}

Ctrl& PreferencesPane::CreateIntSpinMs(const Upp::String& label, int default_value) {
	auto* row = new IntSpinMs(label, default_value);
	return *row;
}

Ctrl& PreferencesPane::CreateIntSpinTicks(const Upp::String& label, int default_value) {
	auto* row = new IntSpinTicks(label, default_value);
	return *row;
}

Ctrl& PreferencesPane::CreateDoubleSpin(const Upp::String& label, double default_value) {
	auto* row = new DoubleSpin(label, default_value);
	return *row;
}

Ctrl& PreferencesPane::CreateKeyAssignRow(const Upp::String& label) {
	auto* row = new KeyAssignRow(label);
	return *row;
}

// Row implementation
Row::Row() {
	Add(bg);
	layout.Mode(HorzLayout);
	Add(layout.SizePos());
}

void Row::Add(Ctrl& ctrl, int proportion) {
	layout.Add(ctrl, proportion);
}

// LabelBox implementation
LabelBox::LabelBox(const Upp::String& text) {
	SetFrame(ThinInsetFrame());
	label.SetLabel(text);
	Add(label.TopPos(0, 20).LeftPos(0, 10));
	Add(content.VSizePos(25).HSizePos());
}

void LabelBox::Add(Ctrl& ctrl) {
	content.Add(ctrl.SizePos());
}

// ColorRect implementation
ColorRect::ColorRect() {
	color = White();
}

void ColorRect::SetColor(const Color& c) {
	color = c;
	Refresh();
}

void ColorRect::Paint(Draw& draw) {
	draw.DrawRect(GetSize(), color);
	draw.DrawRect(GetSize(), Black());
}

// LabeledSlider implementation
LabeledSlider::LabeledSlider(const Upp::String& label_text, int min, int max, int default_value) {
	label.SetLabel(label_text);
	slider.MinMax(min, max);
	slider.Set(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(slider.VSizePos().RightPos(0, 200));
}

// LabeledOption implementation
LabeledOption::LabeledOption(const Upp::String& label_text, bool default_value) {
	label.SetLabel(label_text);
	option.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(option.VSizePos().RightPos(0, 200));
}

// LabeledDropList implementation
LabeledDropList::LabeledDropList(const Upp::String& label_text, const Upp::Vector<Upp::String>& options, int default_index) {
	label.SetLabel(label_text);
	for(const auto& opt : options) {
		droplist.Add(opt);
	}
	droplist.SetData(default_index);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(droplist.VSizePos().RightPos(0, 200));
}

// IntSpinMs implementation
IntSpinMs::IntSpinMs(const Upp::String& label_text, int default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// IntSpinTicks implementation
IntSpinTicks::IntSpinTicks(const Upp::String& label_text, int default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// DoubleSpin implementation
DoubleSpin::DoubleSpin(const Upp::String& label_text, double default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// KeyAssignRow implementation
KeyAssignRow::KeyAssignRow(const Upp::String& label_text) {
	label.SetLabel(label_text);
	assign.SetLabel("Assign");
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(edit.VSizePos().LeftPos(130, 150));
	Add(assign.VSizePos().RightPos(0, 60));
}

// WithPreferencesLayout implementation
template <class TBase>
WithProgressLayout<TBase>::WithProgressLayout() {
	// Initialize the layout without calling InitLayout
}

// PanelRegistry implementation
PanelRegistry& PanelRegistry::Instance() {
	static PanelRegistry instance;
	return instance;
}

void PanelRegistry::RegisterPanel(const Upp::String& category, const Upp::String& subcategory, std::function<PreferencesPane*()> factory) {
	VectorMap<Upp::String, std::function<PreferencesPane*()>>& subcategories = registry.GetAdd(category);
	subcategories.GetAdd(subcategory) = factory;
}

Upp::Vector<Upp::String> PanelRegistry::GetCategories() const {
	Upp::Vector<Upp::String> categories;
	for(int i = 0; i < registry.GetCount(); i++) {
		categories.Add(registry.GetKey(i));
	}
	return categories;
}

Upp::Vector<Upp::String> PanelRegistry::GetSubcategories(const Upp::String& category) const {
	Upp::Vector<Upp::String> subcategories;
	if(registry.Find(category) >= 0) {
		const VectorMap<Upp::String, std::function<PreferencesPane*()>>& subcat_map = registry.Get(category);
		for(int i = 0; i < subcat_map.GetCount(); i++) {
			subcategories.Add(subcat_map.GetKey(i));
		}
	}
	return subcategories;
}

PreferencesPane* PanelRegistry::CreatePanel(const Upp::String& category, const Upp::String& subcategory) const {
	if(registry.Find(category) >= 0) {
		const VectorMap<Upp::String, std::function<PreferencesPane*()>>& subcat_map = registry.Get(category);
		int idx = subcat_map.Find(subcategory);
		if(idx >= 0) {
			return subcat_map[idx]();
		}
	}
	return nullptr;
}

// PreferencesDlg implementation
PreferencesDlg::PreferencesDlg() {
	CtrlLayout(*this, "Preferences");
	Sizeable().Zoomable();
	
	// Set up the tree control
	tree.NoWantFocus();
	tree.WhenSel = THISBACK(OnTreeSel);
	
	// Set up the view holder
	view_holder.AddFrame(1);
	
	// Set up event handlers
	apply.WhenAction = THISBACK(OnApply);
	ok.WhenAction = THISBACK(OnOK);
	cancel.WhenAction = THISBACK(OnCancel);
	defaults.WhenAction = THISBACK(OnDefaults);
	help.WhenAction = THISBACK(OnHelp);
	
	// Populate the tree with registered panels
	RefreshTree();
	
	// Load initial data
	DataIn();
}

void PreferencesDlg::RefreshTree() {
	tree.Clear();
	
	PanelRegistry& registry = PanelRegistry::Instance();
	Upp::Vector<Upp::String> categories = registry.GetCategories();
	
	for(const Upp::String& category : categories) {
		int cat_node = tree.Add(category, category);
		Upp::Vector<Upp::String> subcategories = registry.GetSubcategories(category);
		
		for(const Upp::String& subcategory : subcategories) {
			tree.Add(cat_node, subcategory, subcategory);
		}
	}
}

void PreferencesDlg::OnTreeSel() {
	TreeCtrl::Node* node = tree.Any();
	if(node) {
		Upp::String subcategory = node->GetLabel();
		Upp::String category = node->Parent() ? node->Parent()->GetLabel() : subcategory;
		
		if(current_panel) {
			// Store current panel's data before switching
			BitSet changed;
			current_panel->Store(model, changed);
			view_holder.Remove();
			delete current_panel;
			current_panel = nullptr;
		}
		
		// Only try to create panel if it's a subcategory (has a parent)
		if (node->Parent()) {
			current_panel = PanelRegistry::Instance().CreatePanel(category, subcategory);
			if(current_panel) {
				view_holder.Add(current_panel->SizePos());
				current_panel->Init(model);
				current_panel->Load(model);
			}
		}
	}
}

void PreferencesDlg::DataIn() {
	// Load preferences from model
	model.LoadDefaults();  // For now, load defaults
	
	// Refresh the tree view
	RefreshTree();
	
	// Populate presets dropdown
	preset_list.Clear();
	Upp::Vector<Upp::String> preset_names = preset_mgr.GetPresetNames();
	for(const Upp::String& name : preset_names) {
		preset_list.Add(name);
	}
	if(preset_names.GetCount() > 0) {
		preset_list.SetIndex(0);
	}
	
	// Connect preset events
	preset_list.WhenAction = THISBACK(OnPresetChange);
	preset_store.WhenAction = THISBACK(OnPresetStore);
	preset_rename.WhenAction = THISBACK(OnPresetRename);
	preset_delete.WhenAction = THISBACK(OnPresetDelete);
	preset_marked_only.WhenAction = [this]() {
		preset_mgr.SetMarkedOnly(preset_marked_only);
	};
	
	// Select the first item if available
	if(tree.GetCount() > 0) {
		TreeCtrl::Node* first_node = tree.GetFirstChild();
		if(first_node && first_node->GetCount() > 0) {
			tree.SetCursor(first_node->GetFirstChild());
		} else if(first_node) {
			tree.SetCursor(first_node);
		}
	}
}

void PreferencesDlg::DataOut() {
	// Save preferences from model
	if(current_panel) {
		BitSet changed;
		current_panel->Store(model, changed);
	}
}

void PreferencesDlg::OnApply() {
	DataOut();
	// Apply changes to the system - implementation would depend on the specific system
	LOG("Applying preferences...");
}

void PreferencesDlg::OnOK() {
	DataOut();
	// Apply changes and close
	LOG("Saving preferences and closing...");
	OK();
}

void PreferencesDlg::OnCancel() {
	// Close without applying changes
	LOG("Closing without saving...");
	Cancel();
}

void PreferencesDlg::OnDefaults() {
	// Reset to defaults
	model.LoadDefaults();
	if(current_panel) {
		current_panel->Load(model);
	}
	LOG("Reset to defaults");
}

void PreferencesDlg::OnHelp() {
	// Show help for the current panel
	LOG("Showing help...");
}

void PreferencesDlg::OnPresetChange() {
	Upp::String selected_preset = preset_list.Get(preset_list.GetIndex());
	if (!selected_preset.IsEmpty()) {
		preset_mgr.ReadPreset(selected_preset, model);
		if(current_panel) {
			current_panel->Load(model);
		}
		LOG("Loaded preset: " + selected_preset);
	}
}

void PreferencesDlg::OnPresetStore() {
	// Store current settings as a preset
	DataOut(); // Ensure current panel's data is stored to model
	Upp::String preset_name = PromptOKCancel("Preset Name:", "Enter name for the new preset:");
	if (!preset_name.IsEmpty()) {
		preset_mgr.CreatePreset(preset_name, model);
		preset_list.Add(preset_name);
		preset_list.Set(preset_name);
		LOG("Stored preset: " + preset_name);
	}
}

void PreferencesDlg::OnPresetRename() {
	// Rename selected preset
	int idx = preset_list.GetIndex();
	if (idx >= 0) {
		Upp::String old_name = preset_list.Get(idx);
		Upp::String new_name = PromptOKCancel("Rename Preset", "Enter new name for '" + old_name + "':");
		if (!new_name.IsEmpty() && new_name != old_name) {
			// Load the preset with the old name
			PreferencesModel temp_model;
			preset_mgr.ReadPreset(old_name, temp_model);
			
			// Create a new preset with the new name
			preset_mgr.CreatePreset(new_name, temp_model);
			
			// Delete the old preset
			preset_mgr.DeletePreset(old_name);
			
			// Update the dropdown
			preset_list.Set(idx, new_name);
			preset_list.Set(new_name);
			
			LOG("Renamed preset from: " + old_name + " to: " + new_name);
		}
	}
}

void PreferencesDlg::OnPresetDelete() {
	// Delete selected preset
	int idx = preset_list.GetIndex();
	if (idx >= 0) {
		Upp::String preset_name = preset_list.Get(idx);
		if (PromptYesNo("Delete Preset", "Are you sure you want to delete the preset '" + preset_name + "'?")) {
			preset_mgr.DeletePreset(preset_name);
			preset_list.Remove(idx);
			
			// If we removed the last item, clear the dropdown
			if (preset_list.GetCount() == 0) {
				preset_list.Clear();
			} else if (idx < preset_list.GetCount()) {
				preset_list.SetIndex(idx);
			} else if (preset_list.GetCount() > 0) {
				preset_list.SetIndex(preset_list.GetCount() - 1);
			}
			
			LOG("Deleted preset: " + preset_name);
		}
	}
}

}
#include "Preferences.h"
#include "WithPreferencesLayout.h"
#include "PrefPresets.h"
#include <CtrlLib/CtrlLib.h>

namespace am {

// Explicitly instantiate the template for TopWindow
template class WithProgressLayout<TopWindow>;

// PreferencesPane implementation
PreferencesPane::PreferencesPane() {
	// Initialize the base preference pane
}

StaticRect* PreferencesPane::CreateColorRect(const Color& color) {
	StaticRect* rect = new StaticRect();
	rect->SetFrame(ThinInsetFrame());
	rect->SetRect(0, 0, 20, 20);
	rect->Color(color);
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
	// Constructor implementation
}

void Row::Add(Ctrl& ctrl, int proportion) {
	controls.Add(&ctrl);
	proportions.Add(proportion);
	
	// Add the control as a child
	Ctrl::Add(ctrl);
	
	// Update the layout
	RefreshLayout();
}

void Row::RefreshLayout() {
	Size sz = GetSize();
	int total_prop = 0;
	for(int prop : proportions) {
		total_prop += prop;
	}
	
	if(total_prop == 0) return;
	
	int x = 0;
	for(int i = 0; i < controls.GetCount(); i++) {
		int width = (sz.cx * proportions[i]) / total_prop;
		controls[i]->SetRect(x, 0, width, sz.cy);
		x += width;
	}
}

void Row::Layout() {
	RefreshLayout();
}

Row::~Row() {
	// Destructor implementation
}

// LabelBox implementation
LabelBox::LabelBox(const Upp::String& text) {
	SetFrame(ThinInsetFrame());
	label.SetLabel(text);
	Ctrl::Add(label.TopPos(0, 20).LeftPos(0, 10));
	Ctrl::Add(content.VSizePos(25).HSizePos());
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
	slider <<= default_value;  // Use <<= for U++ value assignment
	
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

// WithProgressLayout implementation
template <class TBase>
WithProgressLayout<TBase>::WithProgressLayout() {
	// Initialize the layout without calling InitLayout
}

template <class TBase>
void WithProgressLayout<TBase>::InitLayout() {
	// Create the main layout
	this->main_splitter.Vert();
	
	// Set up the splitter with left and right panes
	this->main_splitter.Set(this->tree, this->right_panel);
	
	// Add controls to the main window
	TBase::Add(this->tree.LeftPos(0, 200).VSizePos(0, 30));
	TBase::Add(this->main_splitter.HSizePos(200).VSizePos(0, 30));
	TBase::Add(this->presets_list.BottomPos(0, 25).HSizePos());
	TBase::Add(this->ok.BottomPos(0, 25).RightPos(0, 80));
	TBase::Add(this->cancel.BottomPos(0, 25).RightPos(80, 80));
	TBase::Add(this->apply.BottomPos(0, 25).RightPos(160, 80));
	TBase::Add(this->defaults.BottomPos(0, 25).RightPos(240, 80));
	TBase::Add(this->help.BottomPos(0, 25).RightPos(320, 80));
}

// PanelRegistry implementation
PanelRegistry& PanelRegistry::Instance() {
	static PanelRegistry instance;
	return instance;
}

void PanelRegistry::RegisterPanel(const Upp::String& category, const Upp::String& subcategory, Upp::Function<PreferencesPane*()> factory) {
	VectorMap<Upp::String, Upp::Function<PreferencesPane*()>>& subcategories = registry.GetAdd(category);
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
		const VectorMap<Upp::String, Upp::Function<PreferencesPane*()>>& subcat_map = registry.Get(category);
		for(int i = 0; i < subcat_map.GetCount(); i++) {
			subcategories.Add(subcat_map.GetKey(i));
		}
	}
	return subcategories;
}

PreferencesPane* PanelRegistry::CreatePanel(const Upp::String& category, const Upp::String& subcategory) const {
	if(registry.Find(category) >= 0) {
		const VectorMap<Upp::String, Upp::Function<PreferencesPane*()>>& subcat_map = registry.Get(category);
		int idx = subcat_map.Find(subcategory);
		if(idx >= 0) {
			return subcat_map[idx]();
		}
	}
	return nullptr;
}

// PreferencesDlg implementation
PreferencesDlg::PreferencesDlg() {
	Title("Preferences");
	Sizeable().Zoomable();
	
	// Initialize the preset manager
	this->preset_mgr = new PreferencePresetManager();
	
	// Initialize the tree control
	this->tree.NoWantFocus();
	this->tree.WhenSel = THISBACK(OnTreeSel);
	
	// Set up the main splitter
	this->main_splitter.Vert();  // Set vertical orientation
	this->main_splitter.Set(this->tree, this->right_panel);
	
	// Set up event handlers
	this->apply.WhenAction = THISBACK(OnApply);
	this->ok.WhenAction = THISBACK(OnOK);
	this->cancel.WhenAction = THISBACK(OnCancel);
	this->defaults.WhenAction = THISBACK(OnDefaults);
	this->help.WhenAction = THISBACK(OnHelp);
	
	// Add controls to the main window
	Add(this->tree.LeftPos(0, 200).VSizePos(0, 30));
	Add(this->main_splitter.HSizePos(200, 0).VSizePos(0, 30));
	Add(this->presets_list.BottomPos(0, 25).HSizePos());
	Add(this->ok.BottomPos(0, 25).RightPos(0, 80));
	Add(this->cancel.BottomPos(0, 25).RightPos(80, 80));
	Add(this->apply.BottomPos(0, 25).RightPos(160, 80));
	Add(this->defaults.BottomPos(0, 25).RightPos(240, 80));
	Add(this->help.BottomPos(0, 25).RightPos(320, 80));
	
	// Populate the tree with registered panels
	RefreshTree();
	
	// Load initial data
	DataIn();
}

PreferencesDlg::~PreferencesDlg() {
	if (preset_mgr) {
		delete preset_mgr;
		preset_mgr = nullptr;
	}
}

void PreferencesDlg::RefreshTree() {
	this->tree.Clear();
	
	PanelRegistry& registry = PanelRegistry::Instance();
	Upp::Vector<Upp::String> categories = registry.GetCategories();
	
	for(const Upp::String& category : categories) {
		int cat_node = this->tree.Add(0, CtrlImg::smallright(), category);  // Use smallright as placeholder for folder icon
		this->tree.Set(cat_node, category, 0); // Use Set with text and value
		Upp::Vector<Upp::String> subcategories = registry.GetSubcategories(category);
		
		for(const Upp::String& subcategory : subcategories) {
			int subcat_node = this->tree.Add(cat_node, CtrlImg::smallright(), subcategory);  // Use Add instead of AddChild
			this->tree.Set(subcat_node, subcategory, 0); // Use Set with text and value
		}
		this->tree.Open(cat_node, true);  // Use Open instead of Expand for TreeCtrl
	}
}

void PreferencesDlg::OnTreeSel() {
	int node_id = this->tree.GetCursor();
	if(node_id >= 0) {
		Value node_data = this->tree.Get(node_id); // Use Get with only the node ID
		int parent_id = this->tree.GetParent(node_id);
		
		if(current_panel) {
			// Store current panel's data before switching
			Upp::Vector<bool> changed;
			current_panel->Store(model, changed);
			view_holder.Remove();
			delete current_panel;
			current_panel = nullptr;
		}
		
		// Try to find the parent category name
		Upp::String category, subcategory;
		if (parent_id >= 0) {
			Value parent_data = this->tree.Get(parent_id); // Use Get with only the node ID
			if (!parent_data.IsNull() && node_data.Is<String>() && parent_data.Is<String>()) {
				category = parent_data;
				subcategory = node_data;
			}
		} else if (node_data.Is<String>()) {
			// If no parent, then this is a category, not a subcategory
			// We don't create a panel for categories, only for specific subcategories
			category = node_data;
			// For categories like "Key Commands" that might be at the top level
			if (category == "Key Commands") {
				subcategory = "All Commands";  // Default subcategory
			}
		}
		
		if (!category.IsEmpty() && !subcategory.IsEmpty()) {
			current_panel = PanelRegistry::Instance().CreatePanel(category, subcategory);
			if(current_panel) {
				current_panel->Init(model);
				current_panel->Load(model);
				view_holder.Add(current_panel->SizePos());
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
	this->presets_list.Clear();
	Upp::Vector<Upp::String> preset_names = preset_mgr->GetPresetNames();
	for(const Upp::String& name : preset_names) {
		this->presets_list.Add(name);
	}
	if(preset_names.GetCount() > 0) {
		this->presets_list.SetIndex(0);
	}
	
	// Connect preset events
	this->presets_list.WhenAction = THISBACK(OnPresetChange);
	this->preset_store.WhenAction = THISBACK(OnPresetStore);
	this->preset_rename_btn.WhenAction = THISBACK(OnPresetRename);
	this->preset_delete_btn.WhenAction = THISBACK(OnPresetDelete);
	this->preset_marked_only.WhenAction = [this]() {
		preset_mgr->SetMarkedOnly(this->preset_marked_only);
	};
	
	// Select the first item if available
	if(this->tree.GetChildCount(0) > 0) {  // Use 0 as root node ID
		int first_node = this->tree.GetChild(0, 0);  // Get first child of root
		if(first_node >= 0 && this->tree.GetChildCount(first_node) > 0) {
			int first_child = this->tree.GetChild(first_node, 0);  // Get first child of first node
			this->tree.SetCursor(first_child);
		} else if(first_node >= 0) {
			this->tree.SetCursor(first_node);
		}
	}
}

void PreferencesDlg::DataOut() {
	// Save preferences from model
	if(current_panel) {
		Upp::Vector<bool> changed;
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
	Accept();
}

void PreferencesDlg::OnCancel() {
	// Close without applying changes
	LOG("Closing without saving...");
	Reject();
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
	int selected_index = presets_list.GetIndex();
	if (selected_index >= 0) {
		Upp::String selected_preset = AsString(presets_list.Get());
		if (!selected_preset.IsEmpty()) {
			preset_mgr->ReadPreset(selected_preset, model);
			if(current_panel) {
				current_panel->Load(model);
			}
			LOG("Loaded preset: " + selected_preset);
		}
	}
}

void PreferencesDlg::OnPresetStore() {
	// Store current settings as a preset
	DataOut(); // Ensure current panel's data is stored to model
	Upp::PromptOKCancel("Enter name for the new preset:");
	// TODO: Need to implement proper input dialog for preset name
	// For now, we'll use a default name
	Upp::String preset_name = "New Preset";
	if (!preset_name.IsEmpty()) {
		preset_mgr->CreatePreset(preset_name, model);
		presets_list.Add(preset_name);
		presets_list.Set(preset_name);
		LOG("Stored preset: " + preset_name);
	}
}

void PreferencesDlg::OnPresetRename() {
	// Rename selected preset
	int idx = presets_list.GetIndex();
	if (idx >= 0) {
		// TODO: Fix this - need to properly get the selected item text
		Upp::String old_name = "Selected Preset"; // Placeholder for now
		Upp::PromptOKCancel("Enter new name for '" + old_name + "':");
		// TODO: Need to implement proper input dialog for new name
		Upp::String new_name = "Renamed Preset";
		if (!new_name.IsEmpty() && new_name != old_name) {
			// Load the preset with the old name
			PreferencesModel temp_model;
			preset_mgr->ReadPreset(old_name, temp_model);
			
			// Create a new preset with the new name
			preset_mgr->CreatePreset(new_name, temp_model);
			
			// Delete the old preset
			preset_mgr->DeletePreset(old_name);
			
			// Update the dropdown
			presets_list.Remove(idx);
			presets_list.Add(new_name);
			presets_list.Set(new_name);
			
			LOG("Renamed preset from: " + old_name + " to: " + new_name);
		}
	}
}

void PreferencesDlg::OnPresetDelete() {
	// Delete selected preset
	int idx = presets_list.GetIndex();
	if (idx >= 0) {
		Upp::String preset_name = "Selected Preset"; // Placeholder for now
		if (Upp::PromptYesNo("Are you sure you want to delete the preset '" + preset_name + "'?")) {
			preset_mgr->DeletePreset(preset_name);
			presets_list.Remove(idx);
			
			// If we removed the last item, clear the dropdown
			if (presets_list.GetCount() == 0) {
				presets_list.Clear();
			} else if (idx < presets_list.GetCount()) {
				presets_list.SetIndex(idx);
			} else if (presets_list.GetCount() > 0) {
				presets_list.SetIndex(presets_list.GetCount() - 1);
			}
			
			LOG("Deleted preset: " + preset_name);
		}
	}
}

}
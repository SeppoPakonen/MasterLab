#ifndef _Preferences_PrefUI_h_
#define _Preferences_PrefUI_h_

#include <CtrlLib/CtrlLib.h>
#include "PrefModel.h"
// using namespace Upp;  // Removed to avoid namespace conflicts

namespace am {

// Base class for all preference panels
class PreferencesPane : public Ctrl {
public:
	typedef PreferencesPane CLASSNAME;
	PreferencesPane();
	virtual ~PreferencesPane() {}
	
	// Panel lifecycle methods
	virtual void Init(PreferencesModel& model) = 0;
	virtual void Load(const PreferencesModel& model) = 0;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) = 0;
	
protected:
	// Helper methods for creating common controls
	StaticRect* CreateColorRect(const Color& color);
	Ctrl& CreateLabeledSlider(const Upp::String& label, int min, int max, int default_value);
	Ctrl& CreateLabeledOption(const Upp::String& label, bool default_value);
	Ctrl& CreateLabeledDropList(const Upp::String& label, const Upp::Vector<Upp::String>& options, int default_index);
	Ctrl& CreateIntSpinMs(const Upp::String& label, int default_value);
	Ctrl& CreateIntSpinTicks(const Upp::String& label, int default_value);
	Ctrl& CreateDoubleSpin(const Upp::String& label, double default_value);
	Ctrl& CreateKeyAssignRow(const Upp::String& label);
};

// Preference panel registry
class PanelRegistry {
public:
	static PanelRegistry& Instance();
	
	void RegisterPanel(const Upp::String& category, const Upp::String& subcategory, Upp::Function<PreferencesPane*()> factory);
	Upp::Vector<Upp::String> GetCategories() const;
	Upp::Vector<Upp::String> GetSubcategories(const Upp::String& category) const;
	PreferencesPane* CreatePanel(const Upp::String& category, const Upp::String& subcategory) const;
	
private:
	PanelRegistry() = default;
	VectorMap<Upp::String, VectorMap<Upp::String, Upp::Function<PreferencesPane*()>>> registry;
};

// Registration helper macro
#define REGISTER_PREF_PANEL(category, subcategory, panel_class) \
	static struct panel_class##Registrar { \
		panel_class##Registrar() { \
			PanelRegistry::Instance().RegisterPanel(category, subcategory, []() { return new panel_class(); }); \
		} \
	} panel_class##_registrar;

// Preference dialog implementation
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

// Supporting UI controls
class Row : public ParentCtrl {
public:
	typedef Row CLASSNAME;
	Row();
	~Row();
	void Add(Ctrl& ctrl, int proportion = 1);
	virtual void Layout() override;
	
private:
	void RefreshLayout();
	Vector<Ctrl*> controls;
	Vector<int> proportions;
};

class LabelBox : public ParentCtrl {
public:
	typedef LabelBox CLASSNAME;
	LabelBox(const Upp::String& text);
	void Add(Ctrl& ctrl);
	
private:
	Label label;
	ParentCtrl content;
	// Removed reference member that was causing issues
	// CtrlFrame& border;
};

class ColorRect : public Ctrl {
public:
	typedef ColorRect CLASSNAME;
	ColorRect();
	void SetColor(const Color& color);
	Color GetColor() const { return color; }
	
private:
	Color color;
	virtual void Paint(Draw& draw);
	
};

class LabeledSlider : public Row {
public:
	typedef LabeledSlider CLASSNAME;
	LabeledSlider(const Upp::String& label, int min, int max, int default_value);
	Value GetData() const { return slider.GetData(); }
	void SetData(int value) { slider.SetData(value); }
	
private:
	Label label;
	SliderCtrl slider;
};

class LabeledOption : public Row {
public:
	typedef LabeledOption CLASSNAME;
	LabeledOption(const Upp::String& label, bool default_value);
	Value GetData() const { return option.GetData(); }
	void SetData(bool value) { option.SetData(value); }
	
private:
	Label label;
	Option option;
};

class LabeledDropList : public Row {
public:
	typedef LabeledDropList CLASSNAME;
	LabeledDropList(const Upp::String& label, const Upp::Vector<Upp::String>& options, int default_index);
	Value GetData() const { return droplist.GetData(); }
	void SetData(int value) { droplist.SetData(value); }
	
private:
	Label label;
	DropList droplist;
};

class IntSpinMs : public Row {
public:
	typedef IntSpinMs CLASSNAME;
	IntSpinMs(const Upp::String& label, int default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class IntSpinTicks : public Row {
public:
	typedef IntSpinTicks CLASSNAME;
	IntSpinTicks(const Upp::String& label, int default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class DoubleSpin : public Row {
public:
	typedef DoubleSpin CLASSNAME;
	DoubleSpin(const Upp::String& label, double default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(double value) { spin.SetData(value); }
	
private:
	Label label;
	EditDoubleSpin spin;
};

class KeyAssignRow : public Row {
public:
	typedef KeyAssignRow CLASSNAME;
	KeyAssignRow(const Upp::String& label);
	Value GetData() const { return edit.GetData(); }
	void SetData(const Upp::String& value) { edit.SetData(value); }
	
private:
	Label label;
	Upp::EditString edit;
	Button assign;
};

#include "WithPreferencesLayout.h"

// Use the layout defined in the .lay file
typedef WithProgressLayout<TopWindow> WithPreferencesLayout;

// PrefKey template for typed key bindings
template<typename T>
struct PrefKey {
	Upp::String key;
	T default_value;
	
	PrefKey(const Upp::String& k, const T& def) : key(k), default_value(def) {}
};

}

#endif
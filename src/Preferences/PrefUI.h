#ifndef _Preferences_PrefUI_h_
#define _Preferences_PrefUI_h_

#include <CtrlLib/CtrlLib.h>
#include "PrefModel.h"
using namespace Upp;

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
	virtual void Store(PreferencesModel& model, Vector<bool>& changed) = 0;
	
protected:
	// Helper methods for creating common controls
	StaticRect CreateColorRect(const Color& color);
	Ctrl& CreateLabeledSlider(const String& label, int min, int max, int default_value);
	Ctrl& CreateLabeledOption(const String& label, bool default_value);
	Ctrl& CreateLabeledDropList(const String& label, const Vector<String>& options, int default_index);
	Ctrl& CreateIntSpinMs(const String& label, int default_value);
	Ctrl& CreateIntSpinTicks(const String& label, int default_value);
	Ctrl& CreateDoubleSpin(const String& label, double default_value);
	Ctrl& CreateKeyAssignRow(const String& label);
};

// Preference panel registry
class PanelRegistry {
public:
	static PanelRegistry& Instance();
	
	void RegisterPanel(const String& category, const String& subcategory, std::function<PreferencesPane*()> factory);
	Vector<String> GetCategories() const;
	Vector<String> GetSubcategories(const String& category) const;
	PreferencesPane* CreatePanel(const String& category, const String& subcategory) const;
	
private:
	PanelRegistry() = default;
	VectorMap<String, VectorMap<String, std::function<PreferencesPane*()>>> registry;
};

// Registration helper macro
#define REGISTER_PREF_PANEL(category, subcategory, panel_class) \
	static struct panel_class##Registrar { \
		panel_class##Registrar() { \
			PanelRegistry::Instance().RegisterPanel(category, subcategory, []() { return new panel_class(); }); \
		} \
	} panel_class##_registrar;

// Preference dialog implementation
class PreferencesDlg : public WithProgressLayout<TopWindow> {
public:
	typedef PreferencesDlg CLASSNAME;
	PreferencesDlg();
	
private:
	void DataIn();
	void DataOut();
	void RefreshTree();
	void SelectTree(const String& category, const String& subcategory);
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
	
	TreeCtrl tree;
	Ctrl& view_holder;
	PreferencesPane* current_panel = nullptr;
	PreferencesModel model;
	Button help, defaults, apply, ok, cancel;
	
	// Preset functionality
	DropList preset_list;
	Button preset_store, preset_rename, preset_delete;
	Option preset_marked_only;
	PreferencePresetManager preset_mgr;
};

// Supporting UI controls
class Row : public Ctrl {
public:
	typedef Row CLASSNAME;
	Row();
	void Add(Ctrl& ctrl, int proportion = 1);
	
private:
	StaticRect bg;
	ArrayCtrl layout;
};

class LabelBox : public ParentCtrl {
public:
	typedef LabelBox CLASSNAME;
	LabelBox(const String& text);
	void Add(Ctrl& ctrl);
	
private:
	Label label;
	ParentCtrl content;
	CtrlFrame& border;
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
	LabeledSlider(const String& label, int min, int max, int default_value);
	Value GetData() const { return slider.GetData(); }
	void SetData(int value) { slider.SetData(value); }
	
private:
	Label label;
	SliderCtrl slider;
};

class LabeledOption : public Row {
public:
	typedef LabeledOption CLASSNAME;
	LabeledOption(const String& label, bool default_value);
	Value GetData() const { return option.GetData(); }
	void SetData(bool value) { option.SetData(value); }
	
private:
	Label label;
	Option option;
};

class LabeledDropList : public Row {
public:
	typedef LabeledDropList CLASSNAME;
	LabeledDropList(const String& label, const Vector<String>& options, int default_index);
	Value GetData() const { return droplist.GetData(); }
	void SetData(int value) { droplist.SetData(value); }
	
private:
	Label label;
	DropList droplist;
};

class IntSpinMs : public Row {
public:
	typedef IntSpinMs CLASSNAME;
	IntSpinMs(const String& label, int default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class IntSpinTicks : public Row {
public:
	typedef IntSpinTicks CLASSNAME;
	IntSpinTicks(const String& label, int default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class DoubleSpin : public Row {
public:
	typedef DoubleSpin CLASSNAME;
	DoubleSpin(const String& label, double default_value);
	Value GetData() const { return spin.GetData(); }
	void SetData(double value) { spin.SetData(value); }
	
private:
	Label label;
	EditDoubleSpin spin;
};

class KeyAssignRow : public Row {
public:
	typedef KeyAssignRow CLASSNAME;
	KeyAssignRow(const String& label);
	Value GetData() const { return edit.GetData(); }
	void SetData(const String& value) { edit.SetData(value); }
	
private:
	Label label;
	EditString edit;
	Button assign;
};

#include "WithPreferencesLayout.h"

// Use the layout defined in the .lay file
typedef WithProgressLayout<TopWindow> WithPreferencesLayout;

// PrefKey template for typed key bindings
template<typename T>
struct PrefKey {
	String key;
	T default_value;
	
	PrefKey(const String& k, const T& def) : key(k), default_value(def) {}
};

}

#endif
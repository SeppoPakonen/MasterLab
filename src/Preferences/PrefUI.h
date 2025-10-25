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
	virtual void Store(PreferencesModel& model, BitSet& changed) = 0;
	
protected:
	// Helper methods for creating common controls
	StaticRect CreateColorRect(const Color& color);
	Row* CreateLabeledSlider(const String& label, int min, int max, int default_value);
	Row* CreateLabeledOption(const String& label, bool default_value);
	Row* CreateLabeledDropList(const String& label, const Vector<String>& options, int default_index);
	Row* CreateIntSpinMs(const String& label, int default_value);
	Row* CreateIntSpinTicks(const String& label, int default_value);
	Row* CreateDoubleSpin(const String& label, double default_value);
	Row* CreateKeyAssignRow(const String& label);
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
	Border border;
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
	int GetData() const { return slider.GetData(); }
	void SetData(int value) { slider.SetData(value); }
	
private:
	Label label;
	SliderCtrl slider;
};

class LabeledOption : public Row {
public:
	typedef LabeledOption CLASSNAME;
	LabeledOption(const String& label, bool default_value);
	bool GetData() const { return option.GetData(); }
	void SetData(bool value) { option.SetData(value); }
	
private:
	Label label;
	Option option;
};

class LabeledDropList : public Row {
public:
	typedef LabeledDropList CLASSNAME;
	LabeledDropList(const String& label, const Vector<String>& options, int default_index);
	int GetData() const { return droplist.GetData(); }
	void SetData(int value) { droplist.SetData(value); }
	
private:
	Label label;
	DropList droplist;
};

class IntSpinMs : public Row {
public:
	typedef IntSpinMs CLASSNAME;
	IntSpinMs(const String& label, int default_value);
	int GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class IntSpinTicks : public Row {
public:
	typedef IntSpinTicks CLASSNAME;
	IntSpinTicks(const String& label, int default_value);
	int GetData() const { return spin.GetData(); }
	void SetData(int value) { spin.SetData(value); }
	
private:
	Label label;
	EditIntSpin spin;
};

class DoubleSpin : public Row {
public:
	typedef DoubleSpin CLASSNAME;
	DoubleSpin(const String& label, double default_value);
	double GetData() const { return spin.GetData(); }
	void SetData(double value) { spin.SetData(value); }
	
private:
	Label label;
	EditDoubleSpin spin;
};

class KeyAssignRow : public Row {
public:
	typedef KeyAssignRow CLASSNAME;
	KeyAssignRow(const String& label);
	String GetData() const { return edit.GetData(); }
	void SetData(const String& value) { edit.SetData(value); }
	
private:
	Label label;
	EditString edit;
	Button assign;
};

// PrefKey template for typed key bindings
template<typename T>
struct PrefKey {
	String key;
	T default_value;
	
	PrefKey(const String& k, const T& def) : key(k), default_value(def) {}
};

}

#endif
#include "Preferences.h"
namespace am {

// PreferencesPane implementation
PreferencesPane::PreferencesPane() {
	// Initialize the base preference pane
}

StaticRect PreferencesPane::CreateColorRect(const Color& color) {
	StaticRect rect;
	rect.SetFrame(1);
	rect.SetRect(0, 0, 20, 20);
	rect.SetInk(color);
	return rect;
}

Row* PreferencesPane::CreateLabeledSlider(const String& label, int min, int max, int default_value) {
	auto* row = new LabeledSlider(label, min, max, default_value);
	return row;
}

Row* PreferencesPane::CreateLabeledOption(const String& label, bool default_value) {
	auto* row = new LabeledOption(label, default_value);
	return row;
}

Row* PreferencesPane::CreateLabeledDropList(const String& label, const Vector<String>& options, int default_index) {
	auto* row = new LabeledDropList(label, options, default_index);
	return row;
}

Row* PreferencesPane::CreateIntSpinMs(const String& label, int default_value) {
	auto* row = new IntSpinMs(label, default_value);
	return row;
}

Row* PreferencesPane::CreateIntSpinTicks(const String& label, int default_value) {
	auto* row = new IntSpinTicks(label, default_value);
	return row;
}

Row* PreferencesPane::CreateDoubleSpin(const String& label, double default_value) {
	auto* row = new DoubleSpin(label, default_value);
	return row;
}

Row* PreferencesPane::CreateKeyAssignRow(const String& label) {
	auto* row = new KeyAssignRow(label);
	return row;
}

// Row implementation
Row::Row() {
	AddFrame(bg);
	layout.SetHorizontal();
	Add(layout.SizePos());
}

void Row::Add(Ctrl& ctrl, int proportion) {
	layout.Add(ctrl, proportion);
}

// LabelBox implementation
LabelBox::LabelBox(const String& text) {
	label.SetLabel(text);
	Add(label.TopPos(0, 20).LeftPos(0, 10));
	Add(content.VSizePos(25).HSizePos());
	AddFrame(border);
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
LabeledSlider::LabeledSlider(const String& label_text, int min, int max, int default_value) {
	label.SetLabel(label_text);
	slider.SetRange(min, max);
	slider.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(slider.VSizePos().RightPos(0, 200));
}

// LabeledOption implementation
LabeledOption::LabeledOption(const String& label_text, bool default_value) {
	label.SetLabel(label_text);
	option.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(option.VSizePos().RightPos(0, 200));
}

// LabeledDropList implementation
LabeledDropList::LabeledDropList(const String& label_text, const Vector<String>& options, int default_index) {
	label.SetLabel(label_text);
	for(const auto& opt : options) {
		droplist.Add(opt);
	}
	droplist.SetData(default_index);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(droplist.VSizePos().RightPos(0, 200));
}

// IntSpinMs implementation
IntSpinMs::IntSpinMs(const String& label_text, int default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// IntSpinTicks implementation
IntSpinTicks::IntSpinTicks(const String& label_text, int default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// DoubleSpin implementation
DoubleSpin::DoubleSpin(const String& label_text, double default_value) {
	label.SetLabel(label_text);
	spin.SetData(default_value);
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(spin.VSizePos().RightPos(0, 200));
}

// KeyAssignRow implementation
KeyAssignRow::KeyAssignRow(const String& label_text) {
	label.SetLabel(label_text);
	assign.SetLabel("Assign");
	
	Add(label.VSizePos().LeftPos(0, 120));
	Add(edit.VSizePos().LeftPos(130, 150));
	Add(assign.VSizePos().RightPos(0, 60));
}

}
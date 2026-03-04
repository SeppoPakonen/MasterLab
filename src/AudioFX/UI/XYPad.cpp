#include "XYPad.h"

namespace UI {

#ifdef GUI

XYPad::XYPad() : parameterSet(nullptr), isDragging(false) {
	position = Point(50, 50); // Center by default
	sensitivity = Point(100, 100);
}

XYPad::~XYPad() {
}

void XYPad::SetParameterIds(const AudioFX::ParameterId& xId, const AudioFX::ParameterId& yId) {
	paramX = xId;
	paramY = yId;
	UpdateFromParameters();
}

void XYPad::SetPosition(double x, double y) {
	position.x = (int)(x * 100.0);
	position.y = (int)(y * 100.0);
	UpdateParameters();
	Refresh();
}

Point XYPad::GetPosition() const {
	return position;
}

void XYPad::SetParameterSet(AudioFX::ParameterSet* params) {
	parameterSet = params;
	UpdateFromParameters();
}

ValueMap XYPad::GetParameterValues() const {
	ValueMap vm;
	if(parameterSet) {
		vm.Add("x", parameterSet->Get(paramX));
		vm.Add("y", parameterSet->Get(paramY));
	}
	return vm;
}

void XYPad::SetSensitivity(double xSens, double ySens) {
	sensitivity.x = (int)(xSens * 100.0);
	sensitivity.y = (int)(ySens * 100.0);
}

void XYPad::Refresh() {
	Ctrl::Refresh();
}

void XYPad::Paint(Draw& draw) {
	Size sz = GetSize();
	draw.DrawRect(sz, SColorFace());
	draw.DrawRect(2, 2, sz.cx - 4, sz.cy - 4, SColorPaper());
	
	// Draw grid lines
	draw.DrawLine(sz.cx / 2, 0, sz.cx / 2, sz.cy, 1, SColorDisabled());
	draw.DrawLine(0, sz.cy / 2, sz.cx, sz.cy / 2, 1, SColorDisabled());
	
	DrawHandle(draw);
}

void XYPad::LeftDown(Point p, dword keyflags) {
	isDragging = true;
	MouseMove(p, keyflags);
}

void XYPad::LeftUp(Point p, dword keyflags) {
	isDragging = false;
}

void XYPad::MouseMove(Point p, dword keyflags) {
	if(isDragging) {
		Size sz = GetSize();
		double x = (double)p.x / sz.cx;
		double y = (double)p.y / sz.cy;
		
		x = clamp(x, 0.0, 1.0);
		y = clamp(y, 0.0, 1.0);
		
		position.x = (int)(x * 100.0);
		position.y = (int)(y * 100.0);
		
		UpdateParameters();
		Refresh();
	}
}

void XYPad::Layout() {
}

void XYPad::UpdateParameters() {
	if(parameterSet) {
		parameterSet->Set(paramX, position.x / 100.0);
		parameterSet->Set(paramY, position.y / 100.0);
	}
}

void XYPad::UpdateFromParameters() {
	if(parameterSet) {
		position.x = (int)(parameterSet->Get(paramX) * 100.0);
		position.y = (int)(parameterSet->Get(paramY) * 100.0);
		Refresh();
	}
}

void XYPad::DrawHandle(Draw& draw) {
	Size sz = GetSize();
	int hx = position.x * sz.cx / 100;
	int hy = position.y * sz.cy / 100;
	
	draw.DrawEllipse(hx - 5, hy - 5, 10, 10, Blue(), 1, Black());
}

#endif // GUI

} // namespace UI

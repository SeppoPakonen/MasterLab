#include "MIDI.h"

CuteMidiControlObserver::CuteMidiControlObserver() {}
CuteMidiControlObserver::~CuteMidiControlObserver() {}
void CuteMidiControlObserver::SetSubject(CuteSubject* subject) { this->subject = subject; }
CuteSubject* CuteMidiControlObserver::GetSubject() const { return subject; }
void CuteMidiControlObserver::SetCurveList(CuteCurveList* curve_list) { this->curve_list = curve_list; }
CuteCurveList* CuteMidiControlObserver::GetCurveList() const { return curve_list; }
void CuteMidiControlObserver::SetWidget(Upp::Ctrl* widget) { this->widget = widget; }
Upp::Ctrl* CuteMidiControlObserver::GetWidget() const { return widget; }

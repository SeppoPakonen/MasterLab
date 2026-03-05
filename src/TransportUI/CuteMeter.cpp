#include "TransportUI.h"

Vector<CuteMeterValue*> CuteMeterValue::values;
unsigned long CuteMeterValue::stamp = 0;

CuteMeterScale::CuteMeterScale(CuteMeter* meter) : meter(meter) {}
CuteMeter* CuteMeterScale::GetMeter() const { return meter; }
void CuteMeterScale::PaintScale(Draw& draw) { DrawLineLabel(draw, GetSize().cy / 2, "0 dB"); }
void CuteMeterScale::Paint(Draw& draw) { last_y = 0; PaintScale(draw); }
void CuteMeterScale::DrawLineLabel(Draw& draw, int y, const String& label) { draw.DrawText(2, max(0, y - 8), label); last_y = y; }

CuteMeterValue::CuteMeterValue(CuteMeter* meter) : meter(meter) { values.Add(this); }
CuteMeterValue::~CuteMeterValue() {
	for(int i = 0; i < values.GetCount(); ++i) {
		if(values[i] == this) {
			values.Remove(i);
			break;
		}
	}
}
CuteMeter* CuteMeterValue::GetMeter() const { return meter; }
void CuteMeterValue::Refresh(unsigned long stamp) { (void)stamp; Ctrl::Refresh(); }
void CuteMeterValue::RefreshAll() { ++stamp; for(CuteMeterValue* v : values) if(v) v->Refresh(stamp); }
void CuteMeterValue::UpdateAll() { for(CuteMeterValue* v : values) if(v) v->Update(); }

CuteMeter::CuteMeter() { Add(box.SizePos()); }
CuteMeter::~CuteMeter() {}
void CuteMeter::SetMonitor(CuteMonitor* monitor) { this->monitor = monitor; }
CuteMonitor* CuteMeter::GetMonitor() const { return monitor; }
void CuteMeter::Reset() {}
int CuteMeter::Scale(float value) const { return int(scale_factor * value); }
void CuteMeter::SetPeakFalloff(int peak_falloff) { this->peak_falloff = peak_falloff; }
int CuteMeter::GetPeakFalloff() const { return peak_falloff; }
void CuteMeter::SetScaleFactor(float scale_factor) { this->scale_factor = scale_factor; }

CuteMixerMeter::CuteMixerMeter() { Add(title_label.TopPos(0, 20).HSizePos()); Add(meter.VSizePos(20, 0).HSizePos()); }
void CuteMixerMeter::SetTitle(const String& title) { this->title = title; title_label.SetText(title); }
const String& CuteMixerMeter::GetTitle() const { return title; }

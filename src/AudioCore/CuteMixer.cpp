#include "AudioCore.h"

CuteMonitorButton::CuteMonitorButton() { SetLabel("Monitor"); }
CuteMixerStrip::CuteMixerStrip() { Add(title_label.TopPos(0,20).HSizePos()); }
void CuteMixerStrip::SetTitle(const String& title) { this->title = title; title_label.SetText(title); }
const String& CuteMixerStrip::GetTitle() const { return title; }
CuteMixerRackWidget::CuteMixerRackWidget() {}
CuteMixerStrip& CuteMixerRackWidget::AddStrip() { return strips.Add(); }
CuteMixerRack::CuteMixerRack() { Add(rack_widget.SizePos()); SetRect(0,0,700,300); }
CuteMixer::CuteMixer() { Add(rack.SizePos()); }
CuteMixerRack& CuteMixer::GetRack() { return rack; }

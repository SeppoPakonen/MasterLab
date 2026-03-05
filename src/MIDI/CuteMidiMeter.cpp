#include "MIDI.h"

CuteMidiMeterScale::CuteMidiMeterScale(CuteMeter* meter) : CuteMeterScale(meter) {}
void CuteMidiMeterScale::PaintScale(Draw& draw) { DrawLineLabel(draw, GetSize().cy / 2, "MIDI"); }
CuteMidiMeterValue::CuteMidiMeterValue(CuteMeter* meter) : CuteMeterValue(meter) {}
void CuteMidiMeterValue::Refresh(unsigned long stamp) { CuteMeterValue::Refresh(stamp); }
CuteMidiMeterLed::CuteMidiMeterLed(CuteMeter* meter) : CuteMeterValue(meter) {}
void CuteMidiMeterLed::Refresh(unsigned long stamp) { (void)stamp; state = LedOn; Ctrl::Refresh(); }
CuteMidiMeter::CuteMidiMeter() {}
CuteMidiComboMeter::CuteMidiComboMeter() { Add(meter.SizePos()); }
CuteMidiMixerMeter::CuteMidiMixerMeter() {}

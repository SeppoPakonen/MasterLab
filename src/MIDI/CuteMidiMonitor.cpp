#include "MIDI.h"

CuteMidiMonitor::CuteMidiMonitor() {}
void CuteMidiMonitor::Update() {}
void CuteMidiMonitor::ProcessEvent(const CuteMidiEvent& event) { (void)event; ++event_count; }
int CuteMidiMonitor::GetEventCount() const { return event_count; }

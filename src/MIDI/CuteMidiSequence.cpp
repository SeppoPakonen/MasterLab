#include "MIDI.h"

CuteMidiSequence::CuteMidiSequence() {}
CuteMidiSequence::~CuteMidiSequence() {}
void CuteMidiSequence::AddEvent(CuteMidiEvent* event) { if(event) events.Add(event); }
int CuteMidiSequence::GetEventCount() const { return events.GetCount(); }
CuteMidiEvent* CuteMidiSequence::GetEvent(int i) const { return i >= 0 && i < events.GetCount() ? const_cast<CuteMidiEvent*>(&events[i]) : nullptr; }
void CuteMidiSequence::Clear() { events.Clear(); }
void CuteMidiSequence::SetChannel(unsigned short channel) { this->channel = channel; }
unsigned short CuteMidiSequence::GetChannel() const { return channel; }

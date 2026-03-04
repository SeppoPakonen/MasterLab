#include "MIDI.h"

CuteMidiRpn::CuteMidiRpn() {}
bool CuteMidiRpn::Process(const Event& event) { pending.Add(event); return true; }
bool CuteMidiRpn::Dequeue(Event& event) { if(pending.IsEmpty()) return false; event = pending[0]; pending.Remove(0); return true; }
bool CuteMidiRpn::IsPending() const { return !pending.IsEmpty(); }
void CuteMidiRpn::Clear() { pending.Clear(); }

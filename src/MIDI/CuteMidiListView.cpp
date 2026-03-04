#include "MIDI.h"

CuteMidiFileItem::CuteMidiFileItem(const String& name) : name(name) {}
CuteMidiChannelItem::CuteMidiChannelItem(int channel) : channel(channel) {}
CuteMidiListView::CuteMidiListView() { Add(list.SizePos()); list.AddColumn("Name"); list.AddColumn("Channel"); list.AddColumn("Events"); list.AddColumn("Duration"); }
void CuteMidiListView::SetMidiFile(CuteMidiFile* midi_file) { this->midi_file = midi_file; }
CuteMidiFile* CuteMidiListView::GetMidiFile() const { return midi_file; }

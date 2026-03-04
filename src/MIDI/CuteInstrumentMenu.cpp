#include "MIDI.h"

CuteInstrumentMenu::CuteInstrumentMenu() {
    Add(list.SizePos());
    list.AddColumn("Instrument");
}
void CuteInstrumentMenu::SetTrack(CuteTrack* track) { this->track = track; }
void CuteInstrumentMenu::SetMidiManager(CuteMidiManager* midi_manager) { this->midi_manager = midi_manager; }
void CuteInstrumentMenu::Rebuild() { (void)track; (void)midi_manager; list.Clear(); }

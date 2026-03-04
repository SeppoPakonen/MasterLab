#include "MIDI.h"

CuteMidiFileTempo::Node::Node(unsigned long tick, float tempo, unsigned short beats_per_bar, unsigned short beat_divisor)
    : tick(tick), tempo(tempo), beats_per_bar(beats_per_bar), beat_divisor(beat_divisor) {}
void CuteMidiFileTempo::Node::Update(CuteMidiFile* midi_file) { ticks_per_beat = midi_file ? midi_file->GetTicksPerBeat() : 960; }
void CuteMidiFileTempo::Node::Reset(Node* node) { if(node && bar > node->bar) tick = node->TickFromBar(bar); else if(node) bar = node->BarFromTick(tick); }
unsigned short CuteMidiFileTempo::Node::BarFromTick(unsigned long tick) const { return bar + ((tick - this->tick) / max<int>(1, ticks_per_beat * beats_per_bar)); }
unsigned long CuteMidiFileTempo::Node::TickFromBar(unsigned short bar) const { return tick + (ticks_per_beat * beats_per_bar * (bar - this->bar)); }
unsigned long CuteMidiFileTempo::Node::TickSnapToBar(unsigned long tick) const { return TickFromBar(BarFromTick(tick)); }
CuteMidiFileTempo::Marker::Marker(unsigned long tick, const String& text) : tick(tick), text(text) {}
CuteMidiFileTempo::CuteMidiFileTempo(CuteMidiFile* midi_file) : midi_file(midi_file) { Clear(); }
CuteMidiFileTempo::~CuteMidiFileTempo() {}
void CuteMidiFileTempo::Clear() { nodes.Clear(); markers.Clear(); AddNode(0); }
CuteMidiFileTempo::Node* CuteMidiFileTempo::SeekNode(unsigned long tick) const { Node* found = nullptr; for(int i = 0; i < nodes.GetCount(); ++i) { if(nodes[i].tick <= tick) found = const_cast<Node*>(&nodes[i]); else break; } return found; }
CuteMidiFileTempo::Node* CuteMidiFileTempo::AddNode(unsigned long tick, float tempo, unsigned short beats_per_bar, unsigned short beat_divisor) { Node& n = nodes.Add(); n = Node(tick, tempo, beats_per_bar, beat_divisor); UpdateNode(&n); return &n; }
void CuteMidiFileTempo::UpdateNode(Node* node) { if(node) node->Update(midi_file); }
void CuteMidiFileTempo::RemoveNode(Node* node) { for(int i = 0; i < nodes.GetCount(); ++i) if(&nodes[i] == node) { nodes.Remove(i); break; } }
CuteMidiFileTempo::Marker* CuteMidiFileTempo::SeekMarker(unsigned long tick) const { Marker* found = nullptr; for(int i = 0; i < markers.GetCount(); ++i) { if(markers[i].tick <= tick) found = const_cast<Marker*>(&markers[i]); else break; } return found; }
CuteMidiFileTempo::Marker* CuteMidiFileTempo::AddMarker(unsigned long tick, const String& text) { Marker& m = markers.Add(); m = Marker(tick, text); return &m; }
void CuteMidiFileTempo::RemoveMarker(Marker* marker) { for(int i = 0; i < markers.GetCount(); ++i) if(&markers[i] == marker) { markers.Remove(i); break; } }
float CuteMidiFileTempo::GetTempo() const { return nodes.IsEmpty() ? 120.0f : nodes[0].tempo; }
unsigned short CuteMidiFileTempo::GetBeatsPerBar() const { return nodes.IsEmpty() ? 4 : nodes[0].beats_per_bar; }
unsigned short CuteMidiFileTempo::GetBeatDivisor() const { return nodes.IsEmpty() ? 2 : nodes[0].beat_divisor; }
unsigned short CuteMidiFileTempo::GetTicksPerBeat() const { return nodes.IsEmpty() ? 960 : nodes[0].ticks_per_beat; }

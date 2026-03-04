#include "TransportUI.h"

CuteTimeScale::Node::Node() {}
CuteTimeScale::Node::Node(int64 frame, double tempo, int beats_per_bar, int beat_divisor) : frame(frame), tempo(tempo), beats_per_bar(beats_per_bar), beat_divisor(beat_divisor) {}
void CuteTimeScale::Node::Update() {}
void CuteTimeScale::Node::Reset() { frame = 0; bar = 0; beat = 0; tick = 0; pixel = 0; tempo = 120.0; beat_type = 4; beats_per_bar = 4; beat_divisor = 4; ticks_per_beat = 960; }
void CuteTimeScale::Node::SetTempoEx(double tempo) { this->tempo = tempo; }
double CuteTimeScale::Node::GetTempoEx() const { return tempo; }
int64 CuteTimeScale::Node::TickSnap(int64 tick) const { int64 snap = max<int64>(1, ticks_per_beat / 4); return (tick / snap) * snap; }

CuteTimeScale::Cursor::Cursor(CuteTimeScale* time_scale) : time_scale(time_scale) {}
CuteTimeScale* CuteTimeScale::Cursor::GetTimeScale() const { return time_scale; }
void CuteTimeScale::Cursor::Reset() { frame = 0; }
void CuteTimeScale::Cursor::SeekFrame(int64 frame) { this->frame = frame; }
void CuteTimeScale::Cursor::SeekBar(int bar) { frame = bar * 4 * 48000; }
void CuteTimeScale::Cursor::SeekBeat(int beat) { frame = beat * 48000; }
void CuteTimeScale::Cursor::SeekTick(int64 tick) { frame = tick * 10; }
void CuteTimeScale::Cursor::SeekPixel(int pixel) { frame = pixel * 100; }
int64 CuteTimeScale::Cursor::GetFrame() const { return frame; }

CuteTimeScale::Marker::Marker() {}
CuteTimeScale::Marker::Marker(int64 frame, int bar, const String& text, Color color) : frame(frame), bar(bar), text(text), color(color) {}
CuteTimeScale::Marker::Marker(int64 frame, int bar, int accidentals, int mode) : frame(frame), bar(bar), accidentals(accidentals), mode(mode) {}

CuteTimeScale::MarkerCursor::MarkerCursor(CuteTimeScale* time_scale) : time_scale(time_scale) {}
void CuteTimeScale::MarkerCursor::Reset() { position = -1; }
void CuteTimeScale::MarkerCursor::SeekFrame(int64 frame) { if (!time_scale) { position = -1; return; } position = 0; for (int i = 0; i < time_scale->GetMarkerCount(); ++i) if (time_scale->GetMarker(i).frame <= frame) position = i; }
int CuteTimeScale::MarkerCursor::GetPosition() const { return position; }
bool CuteTimeScale::MarkerCursor::IsFirst() const { return position <= 0; }
bool CuteTimeScale::MarkerCursor::IsLast() const { return !time_scale || position >= time_scale->GetMarkerCount() - 1; }

CuteTimeScale::CuteTimeScale() {}
void CuteTimeScale::Reset() { sample_rate = 48000; ticks_per_beat = 960; pixels_per_beat = 120; snap_per_beat = 4; display_format = Time; nodes.Clear(); markers.Clear(); }
void CuteTimeScale::Clear() { nodes.Clear(); markers.Clear(); }
void CuteTimeScale::Sync() {}
void CuteTimeScale::Copy(const CuteTimeScale& time_scale) { *this = time_scale; }
void CuteTimeScale::SetSampleRate(int sample_rate) { this->sample_rate = sample_rate; }
int CuteTimeScale::GetSampleRate() const { return sample_rate; }
void CuteTimeScale::SetTicksPerBeat(int ticks_per_beat) { this->ticks_per_beat = ticks_per_beat; }
int CuteTimeScale::GetTicksPerBeat() const { return ticks_per_beat; }
void CuteTimeScale::SetPixelsPerBeat(int pixels_per_beat) { this->pixels_per_beat = pixels_per_beat; }
int CuteTimeScale::GetPixelsPerBeat() const { return pixels_per_beat; }
void CuteTimeScale::SetSnapPerBeat(int snap_per_beat) { this->snap_per_beat = snap_per_beat; }
int CuteTimeScale::GetSnapPerBeat() const { return snap_per_beat; }
void CuteTimeScale::SetDisplayFormat(DisplayFormat display_format) { this->display_format = display_format; }
CuteTimeScale::DisplayFormat CuteTimeScale::GetDisplayFormat() const { return display_format; }
void CuteTimeScale::AddNode(const Node& node) { nodes.Add(node); }
void CuteTimeScale::UpdateNode(int index, const Node& node) { if (index >= 0 && index < nodes.GetCount()) nodes[index] = node; }
void CuteTimeScale::RemoveNode(int index) { if (index >= 0 && index < nodes.GetCount()) nodes.Remove(index); }
int CuteTimeScale::GetNodeCount() const { return nodes.GetCount(); }
const CuteTimeScale::Node& CuteTimeScale::GetNode(int index) const { return nodes[index]; }
void CuteTimeScale::AddMarker(const Marker& marker) { markers.Add(marker); }
void CuteTimeScale::AddKeySignature(const Marker& marker) { markers.Add(marker); }
void CuteTimeScale::UpdateMarker(int index, const Marker& marker) { if (index >= 0 && index < markers.GetCount()) markers[index] = marker; }
void CuteTimeScale::RemoveMarker(int index) { if (index >= 0 && index < markers.GetCount()) markers.Remove(index); }
int CuteTimeScale::GetMarkerCount() const { return markers.GetCount(); }
const CuteTimeScale::Marker& CuteTimeScale::GetMarker(int index) const { return markers[index]; }
String CuteTimeScale::GetTextFromFrame(int64 frame) const { return AsString(frame); }
int64 CuteTimeScale::GetFrameFromText(const String& text) const { return ScanInt64(text); }
int64 CuteTimeScale::GetTickFromFrame(int64 frame) const { return sample_rate ? (frame * ticks_per_beat) / sample_rate : 0; }
int64 CuteTimeScale::GetFrameFromTick(int64 tick) const { return ticks_per_beat ? (tick * sample_rate) / ticks_per_beat : 0; }

CuteTempoCursor::CuteTempoCursor() {}
void CuteTempoCursor::Clear() { tempo = 120.0; }
void CuteTempoCursor::Seek(CuteTimeScale* time_scale, int64 frame) { if (!time_scale || time_scale->GetNodeCount() == 0) { tempo = 120.0; return; } tempo = time_scale->GetNode(0).tempo; for (int i = 0; i < time_scale->GetNodeCount(); ++i) if (time_scale->GetNode(i).frame <= frame) tempo = time_scale->GetNode(i).tempo; }
double CuteTempoCursor::GetTempo() const { return tempo; }

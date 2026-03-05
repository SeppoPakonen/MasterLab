#include "MIDI.h"

CuteMidiFile::CuteMidiFile() { tempo_map.Create(this); }
CuteMidiFile::~CuteMidiFile() { Close(); }
bool CuteMidiFile::Open(const String& filename, int mode) { this->filename = filename; this->mode = mode == None ? Read : mode; offset = 0; if(!tempo_map) tempo_map.Create(this); return true; }
void CuteMidiFile::Close() { mode = None; offset = 0; }
const String& CuteMidiFile::GetFilename() const { return filename; }
int CuteMidiFile::GetMode() const { return mode; }
unsigned short CuteMidiFile::GetFormat() const { return format; }
unsigned short CuteMidiFile::GetTracks() const { return tracks; }
unsigned short CuteMidiFile::GetTicksPerBeat() const { return ticks_per_beat; }
const CuteMidiFileTempo* CuteMidiFile::GetTempoMap() const { return tempo_map.Get(); }
bool CuteMidiFile::ReadTracks(Vector<CuteMidiSequence*>& seqs, unsigned short track_channel) { (void)seqs; (void)track_channel; return true; }
bool CuteMidiFile::ReadTrack(CuteMidiSequence* seq, unsigned short track_channel) { (void)seq; (void)track_channel; return true; }
unsigned long CuteMidiFile::ReadTrackDuration(unsigned short track_channel) { (void)track_channel; return 0; }
bool CuteMidiFile::WriteHeader(unsigned short format, unsigned short tracks, unsigned short ticks_per_beat) { this->format = format; this->tracks = tracks; this->ticks_per_beat = ticks_per_beat; return true; }
bool CuteMidiFile::WriteTracks(const Vector<CuteMidiSequence*>& seqs) { tracks = seqs.GetCount(); return true; }
bool CuteMidiFile::WriteTrack(CuteMidiSequence* seq) { (void)seq; return true; }
bool CuteMidiFile::SaveCopyFile(const String& new_filename, const String& old_filename, unsigned short track_channel, unsigned short format, CuteMidiSequence* seq, CuteTimeScale* time_scale, unsigned long time_offset) { (void)old_filename; (void)track_channel; (void)format; (void)seq; (void)time_scale; (void)time_offset; return !new_filename.IsEmpty(); }
String CuteMidiFile::CreateFilePathRevision(const String& filename, int revision) { return AppendFileName(GetFileFolder(filename), GetFileTitle(filename) + Format("-%d.mid", revision)); }

#include "MIDI.h"

bool CuteMidiClip::Key::operator==(const Key& other) const { return filename == other.filename && clip_offset == other.clip_offset && clip_length == other.clip_length && track_channel == other.track_channel && midi_channel == other.midi_channel; }
unsigned CuteMidiClip::Key::GetHashValue() const {
	unsigned h = CombineHash(filename, (int)clip_offset, (int)clip_length, (int)track_channel);
	return CombineHash(h, (int)midi_channel);
}
bool CuteMidiClip::FileKey::operator==(const FileKey& other) const { return filename == other.filename && track_channel == other.track_channel; }
unsigned CuteMidiClip::FileKey::GetHashValue() const { return CombineHash(filename, (int)track_channel); }

CuteMidiClip::CuteMidiClip(CuteTrack* track) : track(track) {}
CuteMidiClip::CuteMidiClip(const CuteMidiClip& clip) : CuteClip(clip), track(clip.track), track_channel(clip.track_channel), session_flag(clip.session_flag), revision(clip.revision) {}
CuteMidiClip::~CuteMidiClip() {}
void CuteMidiClip::Open() {}
bool CuteMidiClip::CreateMidiFile(const String& filename, int track_channel) { SetFilename(filename); this->track_channel = track_channel; if(!data) data.Create(); return true; }
bool CuteMidiClip::OpenMidiFile(const String& filename, int track_channel, int mode) { (void)mode; SetFilename(filename); this->track_channel = track_channel; if(!data) data.Create(); return true; }
void CuteMidiClip::SetTrackChannel(unsigned short track_channel) { this->track_channel = track_channel; }
unsigned short CuteMidiClip::GetTrackChannel() const { return track_channel; }
unsigned short CuteMidiClip::GetFormat() const { return data ? data->format : 0; }
void CuteMidiClip::SetSessionFlag(bool session_flag) { this->session_flag = session_flag; }
bool CuteMidiClip::IsSessionFlag() const { return session_flag; }
void CuteMidiClip::SetRevision(unsigned short revision) { this->revision = revision; }
unsigned short CuteMidiClip::GetRevision() const { return revision; }
String CuteMidiClip::CreateFilePathRevision(bool force) { return force || revision ? AppendFileName(GetFileFolder(GetFilename()), GetFileTitle(GetFilename()) + Format("-%d.mid", revision)) : GetFilename(); }
CuteMidiSequence* CuteMidiClip::GetSequence() const { return data ? const_cast<CuteMidiSequence*>(data->sequence.Get()) : nullptr; }

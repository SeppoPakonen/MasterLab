#include "AudioCore.h"

CuteAudioClip::Data::Data(CuteAudioBufferThread* sync_thread, unsigned short channels) {
	buffer.Create(sync_thread, channels);
}

CuteAudioClip::Data::~Data() {
	Clear();
}

CuteAudioBuffer* CuteAudioClip::Data::GetBuffer() const { return buffer; }
void CuteAudioClip::Data::Write(float** buffer, unsigned int frames, unsigned short channels, unsigned int offset) { this->buffer->Write(buffer, frames, channels, offset); }
void CuteAudioClip::Data::SyncExport() { buffer->SyncExport(); }
void CuteAudioClip::Data::Seek(unsigned long frame) { buffer->Seek(frame); }
void CuteAudioClip::Data::Reset(bool looping) { buffer->Reset(looping); }
void CuteAudioClip::Data::SetLoop(unsigned long loop_start, unsigned long loop_end) { buffer->SetLoop(loop_start, loop_end); }
void CuteAudioClip::Data::Attach(CuteAudioClip* clip) { clips.Add(clip); }
void CuteAudioClip::Data::Detach(CuteAudioClip* clip) { clips.RemoveKey(FindIndex(clips, clip)); }
unsigned short CuteAudioClip::Data::GetCount() const { return clips.GetCount(); }
const Vector<CuteAudioClip*>& CuteAudioClip::Data::GetClips() const { return clips; }
void CuteAudioClip::Data::Clear() { clips.Clear(); }

CuteAudioClip::CuteAudioClip(CuteTrack* track)
	: track(track) {
}

CuteAudioClip::CuteAudioClip(const CuteAudioClip& clip)
	: track(clip.track), peak(clip.peak), time_stretch(clip.time_stretch), pitch_shift(clip.pitch_shift), stretcher_flags(clip.stretcher_flags), overlap(clip.overlap) {
}

CuteAudioClip::~CuteAudioClip() {
	CloseAudioFile();
}

void CuteAudioClip::SetTimeStretch(float time_stretch) { this->time_stretch = time_stretch; }
float CuteAudioClip::GetTimeStretch() const { return time_stretch; }
void CuteAudioClip::SetPitchShift(float pitch_shift) { this->pitch_shift = pitch_shift; }
float CuteAudioClip::GetPitchShift() const { return pitch_shift; }
void CuteAudioClip::SetStretcherFlags(unsigned int stretcher_flags) { this->stretcher_flags = stretcher_flags; }
unsigned int CuteAudioClip::GetStretcherFlags() const { return stretcher_flags; }
void CuteAudioClip::SetStretcherFlag(unsigned int stretcher_flag, bool is_on) { if(is_on) stretcher_flags |= stretcher_flag; else stretcher_flags &= ~stretcher_flag; }
bool CuteAudioClip::IsStretcherFlag(unsigned int stretcher_flag) const { return (stretcher_flags & stretcher_flag) != 0; }
unsigned int CuteAudioClip::GetOverlap() const { return overlap; }
void CuteAudioClip::Open() {}
bool CuteAudioClip::OpenAudioFile(const String& file_name, int mode) { (void)file_name; (void)mode; return true; }
CuteAudioBuffer* CuteAudioClip::GetBuffer() const { return data ? data->GetBuffer() : nullptr; }
void CuteAudioClip::Write(float** buffer, unsigned int frames, unsigned short channels, unsigned int offset) { if(data) data->Write(buffer, frames, channels, offset); }
void CuteAudioClip::Seek(unsigned long frame) { if(data) data->Seek(frame); }
void CuteAudioClip::Reset(bool looping) { if(data) data->Reset(looping); }
void CuteAudioClip::SetLoop(unsigned long loop_start, unsigned long loop_end) { if(data) data->SetLoop(loop_start, loop_end); }
void CuteAudioClip::Close() { if(data) data->SyncExport(); }
void CuteAudioClip::Process(unsigned long frame_start, unsigned long frame_end) { (void)frame_start; (void)frame_end; }
void CuteAudioClip::ProcessExport(unsigned long frame_start, unsigned long frame_end) { (void)frame_start; (void)frame_end; }
String CuteAudioClip::ToolTip() const { return "Cute audio clip"; }
bool CuteAudioClip::ClipExport(unsigned long offset, unsigned long length) const { (void)offset; (void)length; return true; }
void CuteAudioClip::InsertHashKey() {}
void CuteAudioClip::UpdateHashKey() {}
void CuteAudioClip::RemoveHashKey() {}
void CuteAudioClip::UnlinkHashData() {}
void CuteAudioClip::RelinkHashData() {}
bool CuteAudioClip::IsHashLinked() const { return false; }
void CuteAudioClip::ClearHashTable() {}
bool CuteAudioClip::LoadClipElement(CuteDocument* document, CuteXmlElement* element) { (void)document; (void)element; return true; }
bool CuteAudioClip::SaveClipElement(CuteDocument* document, CuteXmlElement* element) { (void)document; (void)element; return true; }
void CuteAudioClip::CloseAudioFile() { data = nullptr; }
bool CuteAudioClip::IsOverlap(unsigned int overlap_size) const { return overlap_size == overlap; }
void CuteAudioClip::UpdateFractGains(CuteAudioBuffer* buffer) { (void)buffer; }

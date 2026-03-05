#include "AudioCore.h"

CuteAudioClip::CuteAudioClip(CuteTrack* track)
	: track(track), data(new Data(nullptr, 2)) {
	data->Attach(this);
}

CuteAudioClip::CuteAudioClip(const CuteAudioClip& clip)
	: track(clip.track),
	  peak(clip.peak),
	  data(clip.data),
	  time_stretch(clip.time_stretch),
	  pitch_shift(clip.pitch_shift),
	  stretcher_flags(clip.stretcher_flags),
	  overlap(clip.overlap) {
	if(data)
		data->Attach(this);
}

CuteAudioClip::~CuteAudioClip() {
	UnlinkHashData();
}

void CuteAudioClip::SetTimeStretch(float time_stretch) {
	this->time_stretch = time_stretch;
	if(CuteAudioBuffer* buffer = GetBuffer())
		buffer->SetTimeStretch(time_stretch);
}

float CuteAudioClip::GetTimeStretch() const {
	return time_stretch;
}

void CuteAudioClip::SetPitchShift(float pitch_shift) {
	this->pitch_shift = pitch_shift;
	if(CuteAudioBuffer* buffer = GetBuffer())
		buffer->SetPitchShift(pitch_shift);
}

float CuteAudioClip::GetPitchShift() const {
	return pitch_shift;
}

void CuteAudioClip::SetStretcherFlags(unsigned int stretcher_flags) {
	this->stretcher_flags = stretcher_flags;
}

unsigned int CuteAudioClip::GetStretcherFlags() const {
	return stretcher_flags;
}

void CuteAudioClip::SetStretcherFlag(unsigned int stretcher_flag, bool is_on) {
	if(is_on)
		stretcher_flags |= stretcher_flag;
	else
		stretcher_flags &= ~stretcher_flag;
}

bool CuteAudioClip::IsStretcherFlag(unsigned int stretcher_flag) const {
	return (stretcher_flags & stretcher_flag) != 0;
}

unsigned int CuteAudioClip::GetOverlap() const {
	return overlap;
}

void CuteAudioClip::Open() {}

bool CuteAudioClip::OpenAudioFile(const String& file_name, int mode) {
	if(CuteAudioBuffer* buffer = GetBuffer())
		return buffer->Open(file_name, mode);
	return false;
}

CuteAudioBuffer* CuteAudioClip::GetBuffer() const {
	return data ? data->GetBuffer() : nullptr;
}

void CuteAudioClip::Write(float** buffer, unsigned int frames, unsigned short channels, unsigned int offset) {
	if(data)
		data->Write(buffer, frames, channels, offset);
}

void CuteAudioClip::Seek(unsigned long frame) {
	if(data)
		data->Seek(frame);
}

void CuteAudioClip::Reset(bool looping) {
	if(data)
		data->Reset(looping);
}

void CuteAudioClip::SetLoop(unsigned long loop_start, unsigned long loop_end) {
	if(data)
		data->SetLoop(loop_start, loop_end);
}

void CuteAudioClip::Close() {
	CloseAudioFile();
}

void CuteAudioClip::Process(unsigned long frame_start, unsigned long frame_end) {
	(void)frame_start;
	(void)frame_end;
}

void CuteAudioClip::ProcessExport(unsigned long frame_start, unsigned long frame_end) {
	(void)frame_start;
	(void)frame_end;
	if(data)
		data->SyncExport();
}

String CuteAudioClip::ToolTip() const {
	return "CuteAudioClip";
}

bool CuteAudioClip::ClipExport(unsigned long offset, unsigned long length) const {
	(void)offset;
	(void)length;
	return true;
}

void CuteAudioClip::InsertHashKey() {}

void CuteAudioClip::UpdateHashKey() {}

void CuteAudioClip::RemoveHashKey() {}

void CuteAudioClip::UnlinkHashData() {
	if(data) {
		data->Detach(this);
		if(data->GetCount() == 0)
			delete data;
		data = nullptr;
	}
}

void CuteAudioClip::RelinkHashData() {
	if(!data)
		data = new Data(nullptr, 2);
	data->Attach(this);
}

bool CuteAudioClip::IsHashLinked() const {
	return data != nullptr;
}

void CuteAudioClip::ClearHashTable() {}

bool CuteAudioClip::LoadClipElement(CuteDocument* document, CuteXmlElement* element) {
	(void)document;
	(void)element;
	return true;
}

bool CuteAudioClip::SaveClipElement(CuteDocument* document, CuteXmlElement* element) {
	(void)document;
	(void)element;
	return true;
}

void CuteAudioClip::CloseAudioFile() {
	if(CuteAudioBuffer* buffer = GetBuffer())
		buffer->Close();
}

bool CuteAudioClip::IsOverlap(unsigned int overlap_size) const {
	return overlap >= overlap_size;
}

void CuteAudioClip::UpdateFractGains(CuteAudioBuffer* buffer) {
	(void)buffer;
}

CuteAudioClip::Data::Data(CuteAudioBufferThread* sync_thread, unsigned short channels) {
	buffer.Create(sync_thread, channels);
}

CuteAudioClip::Data::~Data() {}

CuteAudioBuffer* CuteAudioClip::Data::GetBuffer() const {
	return const_cast<CuteAudioBuffer*>(buffer.Get());
}

void CuteAudioClip::Data::Write(float** buffer, unsigned int frames, unsigned short channels, unsigned int offset) {
	if(CuteAudioBuffer* b = GetBuffer())
		b->Write(buffer, frames, channels, offset);
}

void CuteAudioClip::Data::SyncExport() {
	if(CuteAudioBuffer* b = GetBuffer())
		b->SyncExport();
}

void CuteAudioClip::Data::Seek(unsigned long frame) {
	if(CuteAudioBuffer* b = GetBuffer())
		b->Seek(frame);
}

void CuteAudioClip::Data::Reset(bool looping) {
	if(CuteAudioBuffer* b = GetBuffer())
		b->Reset(looping);
}

void CuteAudioClip::Data::SetLoop(unsigned long loop_start, unsigned long loop_end) {
	if(CuteAudioBuffer* b = GetBuffer())
		b->SetLoop(loop_start, loop_end);
}

void CuteAudioClip::Data::Attach(CuteAudioClip* clip) {
	if(!clip)
		return;
	for(int i = 0; i < clips.GetCount(); ++i) {
		if(clips[i] == clip)
			return;
	}
	clips.Add(clip);
}

void CuteAudioClip::Data::Detach(CuteAudioClip* clip) {
	for(int i = 0; i < clips.GetCount(); ++i) {
		if(clips[i] == clip) {
			clips.Remove(i);
			return;
		}
	}
}

unsigned short CuteAudioClip::Data::GetCount() const {
	return (unsigned short)clips.GetCount();
}

const Vector<CuteAudioClip*>& CuteAudioClip::Data::GetClips() const {
	return clips;
}

void CuteAudioClip::Data::Clear() {
	clips.Clear();
	buffer.Clear();
}

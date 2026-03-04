#include "AudioCore.h"

namespace am {
namespace Audio {

// CuteAudioClip
CuteAudioClip::CuteAudioClip() : data(new Data()) {}
CuteAudioClip::~CuteAudioClip() {}
void CuteAudioClip::SetBuffer(CuteAudioBuffer* buffer) { data->SetBuffer(buffer); }
CuteAudioBuffer* CuteAudioClip::GetBuffer() const { return data->GetBuffer(); }

// CuteAudioClip::Data
CuteAudioClip::Data::Data() {}
CuteAudioClip::Data::~Data() {}
void CuteAudioClip::Data::SetBuffer(CuteAudioBuffer* b) { buffer.Clear(); if (b) buffer.Create(b); }
CuteAudioBuffer* CuteAudioClip::Data::GetBuffer() const { return buffer.IsEmpty() ? nullptr : buffer[0]; }
void CuteAudioClip::Data::Attach(CuteAudioClip* clip) { clips.FindAdd(clip); }
void CuteAudioClip::Data::Detach(CuteAudioClip* clip) { clips.Remove(clips.Find(clip)); }

Vector<CuteAudioClip*>& CuteAudioClip::Data::GetClips() { return clips; }

} // namespace Audio
} // namespace am

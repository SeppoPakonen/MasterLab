#include "AudioEditing.h"
#include <AudioCore/AudioCore.h>

CuteClipForm::CuteClipForm() {}
void CuteClipForm::SetClip(CuteClip* clip) { this->clip = clip; }
CuteClip* CuteClipForm::GetClip() const { return clip; }
bool CuteClipForm::IsClipNew() const { return clip_new; }
bool CuteClipForm::IsDirty() const { return dirty_count != 0; }
void CuteClipForm::Accept() {}
void CuteClipForm::Reject() {}
void CuteClipForm::BrowseFile() {}
void CuteClipForm::StabilizeForm() {}

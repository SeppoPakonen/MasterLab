#include "AudioCore.h"

class CuteTrack {};
CuteClip::CuteClip() {}
CuteClip::~CuteClip() {}
void CuteClip::SetTrack(CuteTrack* track) { this->track = track; }
CuteTrack* CuteClip::GetTrack() const { return track; }
void CuteClip::SetName(const String& name) { this->name = name; }
const String& CuteClip::GetName() const { return name; }
void CuteClip::SetClipStart(unsigned long clip_start) { this->clip_start = clip_start; }
unsigned long CuteClip::GetClipStart() const { return clip_start; }
void CuteClip::SetClipLength(unsigned long clip_length) { this->clip_length = clip_length; }
unsigned long CuteClip::GetClipLength() const { return clip_length; }
void CuteClip::SetClipSelected(bool clip_selected) { this->clip_selected = clip_selected; }
bool CuteClip::IsClipSelected() const { return clip_selected; }

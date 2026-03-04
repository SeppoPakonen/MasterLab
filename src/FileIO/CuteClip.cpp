#include "AudioCore.h"

namespace am {
namespace FileIO {

CuteTrackClip::CuteTrackClip() {}
CuteTrackClip::~CuteTrackClip() {}
void CuteTrackClip::SetTrack(CuteTrack* track) { this->track = track; }
CuteTrack* CuteTrackClip::GetTrack() const { return track; }
void CuteTrackClip::SetName(const String& name) { this->name = name; }
const String& CuteTrackClip::GetName() const { return name; }
void CuteTrackClip::SetClipStart(unsigned long clip_start) { this->clip_start = clip_start; }
unsigned long CuteTrackClip::GetClipStart() const { return clip_start; }
void CuteTrackClip::SetClipLength(unsigned long clip_length) { this->clip_length = clip_length; }
unsigned long CuteTrackClip::GetClipLength() const { return clip_length; }
void CuteTrackClip::SetClipSelected(bool clip_selected) { this->clip_selected = clip_selected; }
bool CuteTrackClip::IsClipSelected() const { return clip_selected; }

} // namespace FileIO
} // namespace am

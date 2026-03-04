#include "AudioEditing.h"
#include <AudioCore/AudioCore.h>

class CuteTrack {};
CuteClipSelect::CuteClipSelect() {}
CuteClipSelect::~CuteClipSelect() { Clear(); }
void CuteClipSelect::SelectItem(CuteClip* clip, const Rect& rect, bool select) { (void)clip; (void)rect; (void)select; }
void CuteClipSelect::Clear() { items.Clear(); rect = Rect(0, 0, 0, 0); }
bool CuteClipSelect::IsTrackSingle() const { return track_single; }
CuteTrack* CuteClipSelect::GetTrackSingle() const { return track_single_ptr; }
const Rect& CuteClipSelect::GetRect() const { return rect; }

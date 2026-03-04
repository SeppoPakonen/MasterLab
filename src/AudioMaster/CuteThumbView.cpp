#include "AudioMaster.h"

CuteThumbView::CuteThumbView() {}
void CuteThumbView::UpdatePlayHead() { ++play_head_x; Refresh(); }
void CuteThumbView::UpdateContents() { Refresh(); }
void CuteThumbView::UpdateThumb(int dx) { thumb_rect.Offset(dx, 0); Refresh(); }

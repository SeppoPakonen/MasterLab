#include "ProjectWindow.h"

CuteScrollView::CuteScrollView() {}
CuteScrollView::~CuteScrollView() {}
int CuteScrollView::GetContentsX() const { return contents_x; }
int CuteScrollView::GetContentsY() const { return contents_y; }
int CuteScrollView::GetContentsWidth() const { return contents_width; }
int CuteScrollView::GetContentsHeight() const { return contents_height; }
void CuteScrollView::SetContentsPos(int contents_x, int contents_y) { this->contents_x = contents_x; this->contents_y = contents_y; }
void CuteScrollView::ResizeContents(int contents_width, int contents_height) { this->contents_width = contents_width; this->contents_height = contents_height; }
void CuteScrollView::EnsureVisible(int contents_x, int contents_y, int margin_x, int margin_y) { this->contents_x = max(0, contents_x - margin_x); this->contents_y = max(0, contents_y - margin_y); }
Point CuteScrollView::ViewportToContents(const Point& point) const { return Point(point.x + contents_x, point.y + contents_y); }
Point CuteScrollView::ContentsToViewport(const Point& point) const { return Point(point.x - contents_x, point.y - contents_y); }

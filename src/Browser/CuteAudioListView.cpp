#include "Browser.h"

CuteAudioFileItem::CuteAudioFileItem(const String& path, CuteAudioFile* file)
    : path(path) {
    (void)file;
}

String CuteAudioFileItem::ToolTip() const {
    return path;
}

CuteAudioListView::CuteAudioListView() {
}

int CuteAudioListView::GetPathColumn() const { return Path; }
CuteAudioFileItem CuteAudioListView::CreateFileItem(const String& path) { return CuteAudioFileItem(path, nullptr); }
Vector<String> CuteAudioListView::GetOpenFileNames() { return Vector<String>(); }

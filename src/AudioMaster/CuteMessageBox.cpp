#include "AudioMaster.h"

CuteMessageBox::CuteMessageBox() {
    Add(text_label.SizePos());
    SetRect(0, 0, 320, 120);
}
void CuteMessageBox::SetText(const String& text) { text_label.SetText(text); }
String CuteMessageBox::GetText() const { return text_label.GetText().ToString(); }
void CuteMessageBox::SetIcon(Icon icon) { this->icon = icon; }
CuteMessageBox::Icon CuteMessageBox::GetIcon() const { return icon; }

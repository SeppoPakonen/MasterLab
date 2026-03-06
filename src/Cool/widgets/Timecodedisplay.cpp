/*
    SPDX-FileCopyrightText: 2010 Jean-Baptiste Mardelle <jb@kdenlive.org>
    U++ Conversion: 2026 MasterLab Team
*/

#include "Timecodedisplay.h"
#include "../Core.h"

NAMESPACE_UPP

TimecodeDisplay::TimecodeDisplay(bool auto_adjust) {
    Initialize();
    if (auto_adjust) {
        UpdateTimeCode(pCore.GetTimecode());
    }
}

TimecodeDisplay::TimecodeDisplay(const Timecode& t)
    : timecode(t)
{
    Initialize();
}

TimecodeDisplay::~TimecodeDisplay() {
}

void TimecodeDisplay::Initialize() {
    AlignRight();
    SetFilter([](int c) { return IsDigit(c) || c == ':' || c == ',' || c == '.' || c == '-' ? c : 0; });
    
    WhenAction = THISBACK(OnEditingFinished);
}

void TimecodeDisplay::SetRange(int min, int max) {
    min_value = min;
    max_value = max;
    SetValue(value); // Re-clamp
}

void TimecodeDisplay::SetValue(int v) {
    if (max_value >= 0) {
        value = clamp(v, min_value, max_value);
    } else {
        value = max(min_value, v);
    }
    
    RefreshDisplay();
    if (WhenUpdated) WhenUpdated();
}

void TimecodeDisplay::SetValue(const String& s) {
    SetValue(timecode.GetFrameCount(s));
}

void TimecodeDisplay::SetValue(const GenTime& v) {
    SetValue(v.Frames(timecode.GetFps()));
}

GenTime TimecodeDisplay::GetGentime() const {
    return GenTime(value, timecode.GetFps());
}

void TimecodeDisplay::SetTimeCodeFormat(bool frames, bool force) {
    if (!force && is_frames_format == frames) return;
    is_frames_format = frames;
    RefreshDisplay();
}

void TimecodeDisplay::UpdateTimeCode(const Timecode& t) {
    timecode = t;
    RefreshDisplay();
}

void TimecodeDisplay::RefreshDisplay() {
    if (is_frames_format) {
        SetText(Format("%d", value - min_value));
    } else {
        SetText(timecode.GetTimecodeFromFrames(offset + value - min_value));
    }
}

void TimecodeDisplay::OnEditingFinished() {
    String text = GetText().ToString();
    if (is_frames_format) {
        SetValue(StrInt(text) + min_value);
    } else {
        SetValue(timecode.GetFrameCount(text) + min_value - offset);
    }
    if (WhenEditingFinished) WhenEditingFinished(value);
}

void TimecodeDisplay::SetBold(bool bold) {
    SetFont(StdFont().Bold(bold));
}

void TimecodeDisplay::LeftDown(Point p, dword flags) {
    EditField::LeftDown(p, flags);
    start_drag_pos = Pointf(p);
    is_dragging = true;
}

void TimecodeDisplay::MouseMove(Point p, dword flags) {
    if (is_dragging && (flags & K_MOUSELEFT)) {
        double delta = p.x - start_drag_pos.x;
        if (abs(delta) > 5) {
            SetValue(value + (int)delta);
            start_drag_pos = Pointf(p);
        }
    }
    EditField::MouseMove(p, flags);
}

void TimecodeDisplay::LeftUp(Point p, dword flags) {
    is_dragging = false;
    EditField::LeftUp(p, flags);
}

void TimecodeDisplay::MouseWheel(Point p, int zdelta, dword flags) {
    SetValue(value + (zdelta > 0 ? 1 : -1));
}

bool TimecodeDisplay::Key(dword key, int count) {
    if (key == K_ENTER || key == K_RETURN) {
        OnEditingFinished();
        return true;
    }
    return EditField::Key(key, count);
}

END_UPP_NAMESPACE

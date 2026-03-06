/*
   SPDX-FileCopyrightText: 2003 Jason Wood <jasonwood@blueyonder.co.uk>
   U++ Conversion: 2026 MasterLab Team
*/

#include "Timecode.h"
#include <cmath>

NAMESPACE_UPP

Timecode::Timecode(Formats format, double frames_per_second) {
    SetFormat(frames_per_second, format);
}

Timecode::~Timecode() {}

void Timecode::SetFormat(double frames_per_second, Formats format_) {
    displayed_frames_per_second = (int)round(frames_per_second);
    drop_frame_timecode = (abs(frames_per_second - 30000.0 / 1001.0) < 0.001);
    format = format_;
    real_fps = frames_per_second;
    
    if (drop_frame_timecode) {
        drop_frames = round(real_fps * 0.066666);
        frames_per_10_minutes = (int)round(real_fps * 600);
    }
}

String Timecode::GetDisplayTimecode(const GenTime& time, bool frame_display) const {
    if (frame_display) {
        return Format("%d", time.Frames(real_fps));
    }
    return GetTimecode(time);
}

String Timecode::GetTimecode(const GenTime& time) const {
    switch (format) {
        case HH_MM_SS_FF:
            return GetTimecodeFromFrames(time.Frames(real_fps));
        case HH_MM_SS_HH:
            return GetTimecodeHH_MM_SS_HH(time);
        case Frames:
            return GetTimecodeFrames(time);
        case Seconds:
            return GetTimecodeSeconds(time);
    }
    return GetTimecodeFromFrames(time.Frames(real_fps));
}

int Timecode::GetFrameCount(const String& duration) const {
    if (duration.IsEmpty()) return 0;
    
    // U++ Split with multiple delimiters
    Vector<String> parts = Split(duration, ":,.");
    if (parts.GetCount() < 3) return 0;
    
    int hours = StrInt(parts[0]);
    int minutes = StrInt(parts[1]);
    int seconds = StrInt(parts[2]);
    int frames = (parts.GetCount() > 3) ? StrInt(parts[3]) : 0;
    
    int frame_number = 0;
    if (drop_frame_timecode) {
        int total_minutes = (60 * hours) + minutes;
        frame_number = (displayed_frames_per_second * 3600 * hours) + 
                       (displayed_frames_per_second * 60 * minutes) + 
                       (displayed_frames_per_second * seconds) + frames;
        frame_number -= (int)(drop_frames * (total_minutes - floor(total_minutes / 10)));
    } else {
        frame_number = (int)round((hours * 3600.0 + minutes * 60.0 + seconds) * real_fps + frames);
    }
    
    return (duration[0] == '-') ? -frame_number : frame_number;
}

const String Timecode::GetDisplayTimecodeFromFrames(int frames, bool frame_display) const {
    if (frame_display) return Format("%d", frames);
    return GetTimecodeFromFrames(frames);
}

const String Timecode::GetTimecodeFromFrames(int frames) const {
    if (drop_frame_timecode) return GetTimecodeDropFrame(frames);
    
    bool negative = (frames < 0);
    if (negative) frames = abs(frames);
    
    int hours = (int)(frames / (real_fps * 3600));
    frames -= (int)floor(hours * 3600 * real_fps);
    
    int minutes = (int)(frames / (real_fps * 60));
    frames -= (int)floor(minutes * 60 * real_fps);
    
    int seconds = (int)(frames / real_fps);
    frames -= (int)ceil(seconds * real_fps);
    
    int ff_width = (real_fps > 100) ? 3 : 2;
    String res = Format("%02d:%02d:%02d:%0*d", hours, minutes, seconds, ff_width, frames);
    return negative ? "-" + res : res;
}

const String Timecode::GetMask(const GenTime& t) const {
    String m = (real_fps > 100) ? "99:99:99:999" : "99:99:99:99";
    if (drop_frame_timecode) {
        // String::Replace is void, so we must use a temporary or multiple steps
        String res = m;
        res.Replace(":", ",");
        m = res;
    }
    if (t.Seconds() < 0) return "#" + m;
    return m;
}

String Timecode::ReformatSeparators(String duration) const {
    if (duration.GetLength() > 8) {
        duration.Set(8, drop_frame_timecode ? ',' : ':');
    }
    return duration;
}

// static
String Timecode::GetStringTimecode(int frames, double fps, bool show_frames) {
    bool negative = (frames < 0);
    if (negative) frames = abs(frames);
    
    int seconds = (int)(frames / fps);
    int frms = frames % (int)round(fps);
    int minutes = seconds / 60;
    seconds %= 60;
    int hours = minutes / 60;
    minutes %= 60;
    
    String res;
    if (show_frames) {
        int ff_width = (fps > 100) ? 3 : 2;
        res = Format("%02d:%02d:%02d.%0*d", hours, minutes, seconds, ff_width, frms);
    } else {
        res = Format("%02d:%02d:%02d", hours, minutes, seconds);
    }
    return negative ? "-" + res : res;
}

String Timecode::FormatMarkerDuration(int frames, double fps) {
    int seconds = (int)(frames / fps);
    int frms = frames % (int)round(fps);
    int minutes = seconds / 60;
    seconds %= 60;
    
    if (minutes > 0) return Format("%dm:%02ds:%02df", minutes, seconds, frms);
    return Format("%ds:%02df", seconds, frms);
}

String Timecode::ScaleTimecode(String timecode, double source_fps, double target_fps) {
    Timecode src(HH_MM_SS_FF, source_fps);
    Timecode dst(HH_MM_SS_FF, target_fps);
    return dst.GetTimecodeFromFrames(src.GetFrameCount(timecode));
}

const String Timecode::GetTimecodeHH_MM_SS_HH(const GenTime& time) const {
    int hundredths = (int)round(time.Seconds() * 100);
    bool negative = (hundredths < 0);
    if (negative) hundredths = abs(hundredths);
    
    int seconds = hundredths / 100;
    hundredths %= 100;
    int minutes = seconds / 60;
    seconds %= 60;
    int hours = minutes / 60;
    minutes %= 60;
    
    String res = Format("%02d:%02d:%02d.%02d", hours, minutes, seconds, hundredths);
    return negative ? "-" + res : res;
}

const String Timecode::GetTimecodeFrames(const GenTime& time) const {
    return Format("%d", time.Frames(real_fps));
}

const String Timecode::GetTimecodeSeconds(const GenTime& time) const {
    return Format("%.2f", time.Seconds());
}

const String Timecode::GetTimecodeDropFrame(int frames) const {
    String res = GetTimecodeFromFrames(frames);
    res.Replace(":", ",");
    return res;
}

END_UPP_NAMESPACE

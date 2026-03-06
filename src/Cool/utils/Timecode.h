/*
   SPDX-FileCopyrightText: 2003 Jason Wood <jasonwood@blueyonder.co.uk>
   U++ Conversion: 2026 MasterLab Team
*/

#ifndef _Cool_utils_Timecode_h_
#define _Cool_utils_Timecode_h_

#include "Gentime.h"

NAMESPACE_UPP

/**
 * Handles the conversion of a GenTime into a nicely formatted string.
*/
class Timecode {
public:
    enum Formats { HH_MM_SS_FF, HH_MM_SS_HH, Frames, Seconds };

    explicit Timecode(Formats format = HH_MM_SS_FF, double frames_per_second = 25);
    virtual ~Timecode();

    void SetFormat(double frames_per_second, Formats format = HH_MM_SS_FF);
    Formats GetFormat() const { return format; }

    String GetDisplayTimecode(const GenTime& time, bool frame_display) const;
    String GetTimecode(const GenTime& time) const;
    int    GetFrameCount(const String& duration) const;
    
    const String GetDisplayTimecodeFromFrames(int frames, bool frame_display) const;
    const String GetTimecodeFromFrames(int frames) const;
    
    double GetFps() const { return real_fps; }
    const String GetMask(const GenTime& t = GenTime()) const;
    String ReformatSeparators(String duration) const;

    static String GetStringTimecode(int frames, double fps, bool show_frames = false);
    static String FormatMarkerDuration(int frames, double fps);
    static String ScaleTimecode(String timecode, double source_fps, double target_fps);

private:
    Formats format;
    bool    drop_frame_timecode;
    int     displayed_frames_per_second;
    double  real_fps;
    double  drop_frames;
    int     frames_per_10_minutes;

    const String GetTimecodeHH_MM_SS_FF(int frames) const;
    const String GetTimecodeHH_MM_SS_HH(const GenTime& time) const;
    const String GetTimecodeFrames(const GenTime& time) const;
    const String GetTimecodeSeconds(const GenTime& time) const;
    const String GetTimecodeDropFrame(int framenumber) const;
};

END_UPP_NAMESPACE

#endif

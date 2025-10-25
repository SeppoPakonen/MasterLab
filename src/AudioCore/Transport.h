#ifndef _AudioCore_Transport_h_
#define _AudioCore_Transport_h_

// Note: Requires AudioCore/AudioCore.h (for FrameIndex) - included via main header in .cpp files

namespace am {

struct WindOptions {
	enum Mode { AdjustToZoom, Fixed };
	Mode mode = AdjustToZoom;
	int speedFactor = 1;
	int fastFactor = 10;
};

struct ScrubPrefs {
	int response = 50;    // 0-100
	int volume = 50;      // 0-100
	bool cpuSaving = false;
};

struct TimecodePrefs {
	bool showSubframes = false;
	int userFramerate = 30;
	int cursorWidth = 3;
};

struct Transport {
    bool playing = false;
    FrameIndex playhead = 0;
    
    // Basic transport methods
    void Play();
    void Stop();
    void Seek(FrameIndex f);
    
    // New methods required by design
    void SetReturnToStartOnStop(bool on) { return_to_start_on_stop = on; }
    void SetPunchDeactivateOnStop(bool on) { punch_deactivate_on_stop = on; }
    void SetStopAfterAutoPunchOut(bool on) { stop_after_auto_punch_out = on; }
    void SetStopWhileWinding(bool on) { stop_while_winding = on; }
    void SetStationaryCursor(bool on) { stationary_cursor = on; }
    void SetLocateOnEmptyClick(bool on) { locate_on_empty_click = on; }
    void SetZoomWhileLocating(bool on) { zoom_while_locating = on; }
    void SetUserFramerate(int framerate) { user_framerate = framerate; }
    void SetCursorWidth(int px) { cursor_width = px; }
    void ConfigureWind(const WindOptions& options) { wind_options = options; }
    void ConfigureScrub(const ScrubPrefs& prefs) { scrub_prefs = prefs; }
    void ConfigureTimecode(const TimecodePrefs& prefs) { timecode_prefs = prefs; }
    
    // Getters for new properties
    bool GetReturnToStartOnStop() const { return return_to_start_on_stop; }
    bool GetPunchDeactivateOnStop() const { return punch_deactivate_on_stop; }
    bool GetStopAfterAutoPunchOut() const { return stop_after_auto_punch_out; }
    bool GetStopWhileWinding() const { return stop_while_winding; }
    bool GetStationaryCursor() const { return stationary_cursor; }
    bool GetLocateOnEmptyClick() const { return locate_on_empty_click; }
    bool GetZoomWhileLocating() const { return zoom_while_locating; }
    int GetUserFramerate() const { return user_framerate; }
    int GetCursorWidth() const { return cursor_width; }
    const WindOptions& GetWindOptions() const { return wind_options; }
    const ScrubPrefs& GetScrubPrefs() const { return scrub_prefs; }
    const TimecodePrefs& GetTimecodePrefs() const { return timecode_prefs; }
    
private:
    // New fields required by design
    bool return_to_start_on_stop = false;
    bool punch_deactivate_on_stop = false;
    bool stop_after_auto_punch_out = false;
    bool stop_while_winding = false;
    bool stationary_cursor = false;
    bool locate_on_empty_click = false;
    bool zoom_while_locating = false;
    int user_framerate = 30;
    int cursor_width = 3;
    WindOptions wind_options;
    ScrubPrefs scrub_prefs;
    TimecodePrefs timecode_prefs;
};

}

#endif

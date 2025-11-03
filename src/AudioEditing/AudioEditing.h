#ifndef _AudioEditing_AudioEditing_h_
#define _AudioEditing_AudioEditing_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <RichText/RichText.h>
#include <AudioCore/AudioCore.h>
using namespace Upp;

#include "AudioImportPrefs.h"
#include "TimeStretchPrefs.h"
#include "SnapSettings.h"
#include "FadeBehavior.h"

// Ensure VectorMap is available

// Class to represent individual audio clips
class ClipMarker {
public:
    double time;
    String label;
    Color color;
    
    ClipMarker() : time(0.0) {}
    ClipMarker(double t, String l, Color c) : time(t), label(l), color(c) {}
    
    void Jsonize(JsonIO& jio) {
        jio("time", time)("label", label)("color", color);
    }
    
    bool operator==(const ClipMarker& other) const {
        return time == other.time && label == other.label && color == other.color;
    }
};

class AudioClip {
private:
    String name;
    double start_time;
    double end_time;
    String file_path;
    bool is_muted;
    bool is_soloed;
    double volume;
    double pitch_semitones;  // For pitch shifting
    Vector<ClipMarker> markers;

public:
    AudioClip();
    AudioClip(String clip_name, String file_path, double start_time = 0.0, double end_time = 0.0);
    
    // Getters
    String GetName() const { return name; }
    double GetStartTime() const { return start_time; }
    double GetEndTime() const { return end_time; }
    String GetFilePath() const { return file_path; }
    bool GetMuteStatus() const { return is_muted; }
    bool GetSoloStatus() const { return is_soloed; }
    double GetVolume() const { return volume; }
    double GetPitchSemitones() const { return pitch_semitones; }
    const Vector<ClipMarker>& GetMarkers() const { return markers; }  // Return const reference
    
    // Setters
    void SetName(String n) { name = n; }
    void SetStartTime(double start) { start_time = start; }
    void SetEndTime(double end) { end_time = end; }
    void SetFilePath(String path) { file_path = path; }
    void SetMuteStatus(bool muted) { is_muted = muted; }
    void SetSoloStatus(bool soloed) { is_soloed = soloed; }
    void SetVolume(double vol) { volume = vol; }
    void SetPitchSemitones(double semitones) { pitch_semitones = semitones; }  // For pitch shifting
    
    // Utility functions
    double GetDuration() const { return end_time - start_time; }
    void SetDuration(double duration) { end_time = start_time + duration; }
    bool ContainsTime(double time) const { return time >= start_time && time <= end_time; }
    bool OverlapsWith(const AudioClip& other) const;
    void AddMarker(const ClipMarker& marker) { markers.Add(marker); }
    void RemoveMarker(int index) { if(index >= 0 && index < markers.GetCount()) markers.Remove(index); }
    
    void Jsonize(JsonIO& jio) {
        jio("name", name)("start_time", start_time)("end_time", end_time)
           ("file_path", file_path)("is_muted", is_muted)("is_soloed", is_soloed)
           ("volume", volume)("pitch_semitones", pitch_semitones)("markers", markers);
    }
    
    bool operator==(const AudioClip& other) const {
        return name == other.name && start_time == other.start_time && 
               end_time == other.end_time && file_path == other.file_path &&
               is_muted == other.is_muted && is_soloed == other.is_soloed &&
               volume == other.volume && pitch_semitones == other.pitch_semitones &&
               markers == other.markers;
    }
};

// Class to represent a single audio track containing multiple clips
class AudioTrack {
private:
    String name;
    Vector<AudioClip> clips;
    bool is_muted;
    bool is_soloed;
    double volume;
    int height;

public:
    AudioTrack();
    AudioTrack(String track_name);
    
    // Getters
    String GetName() const { return name; }
    const Vector<AudioClip>& GetClips() const { return clips; }  // Return const reference
    bool GetMuteStatus() const { return is_muted; }
    bool GetSoloStatus() const { return is_soloed; }
    double GetVolume() const { return volume; }
    int GetHeight() const { return height; }
    
    // Setters
    void SetName(String n) { name = n; }
    void SetMuteStatus(bool muted) { is_muted = muted; }
    void SetSoloStatus(bool soloed) { is_soloed = soloed; }
    void SetVolume(double vol) { volume = vol; }
    void SetHeight(int h) { height = h; }
    
    // Track operations
    void AddClip(const AudioClip& clip);
    void RemoveClip(int index);
    void MoveClip(int from_index, int to_index);
    int FindClipAtTime(double time) const; // Returns index of clip at specified time, or -1 if none
    void TrimClip(int index, double new_start_time, double new_end_time);
    void SplitClip(int index, double split_time);
    
    // Automation data for this track
    VectorMap<String, Automation> automation;  // Map of parameter name to automation data
    
    void Jsonize(JsonIO& jio) {
        jio("name", name)("clips", clips)("is_muted", is_muted)("is_soloed", is_soloed)
           ("volume", volume)("height", height)("automation", automation);
    }
    
    bool operator==(const AudioTrack& other) const {
        return name == other.name && clips == other.clips && 
               is_muted == other.is_muted && is_soloed == other.is_soloed &&
               volume == other.volume && height == other.height && automation == other.automation;
    }
    
    // Automation-related methods
    void AddAutomationPoint(String parameter, const AutomationPoint& point);
    void RemoveAutomationPoint(String parameter, int index);
    double GetAutomationValueAtTime(String parameter, double time) const;
    void SetAutomationValueAtTime(String parameter, double time, double value);
    Vector<AutomationPoint> GetAutomationPoints(String parameter_name) const;
};

// Class to represent markers on the timeline
class Marker {
public:
    double time;
    String label;
    Color color;
    
    Marker() : time(0.0) {}
    Marker(double t, String l, Color c) : time(t), label(l), color(c) {}
    
    void Jsonize(JsonIO& jio) {
        jio("time", time)("label", label)("color", color);
    }
    
    bool operator==(const Marker& other) const {
        return time == other.time && label == other.label && color == other.color;
    }
};

// Class to represent regions on the timeline
class Region {
public:
    double start_time;
    double end_time;
    String label;
    Color color;
    
    Region() : start_time(0.0), end_time(0.0) {}
    Region(double start, double end, String l, Color c) : start_time(start), end_time(end), label(l), color(c) {}
    
    void Jsonize(JsonIO& jio) {
        jio("start_time", start_time)("end_time", end_time)("label", label)("color", color);
    }
    
    bool operator==(const Region& other) const {
        return start_time == other.start_time && end_time == other.end_time && 
               label == other.label && color == other.color;
    }
};

// Class to represent the timeline containing multiple audio tracks
class Timeline {
private:
    Vector<AudioTrack> tracks;
    Vector<AudioBus> buses;
    double duration;
    int time_signature_numerator;
    int time_signature_denominator;
    double tempo;
    bool metronome_enabled;
    Vector<Marker> markers;
    Vector<Region> regions;

public:
    Timeline();
    
    // Getters
    const Vector<AudioTrack>& GetTracks() const { return tracks; }  // Return const reference
    const Vector<AudioBus>& GetBuses() const { return buses; }  // Return const reference
    double GetDuration() const { return duration; }
    int GetTimeSignatureNumerator() const { return time_signature_numerator; }
    int GetTimeSignatureDenominator() const { return time_signature_denominator; }
    double GetTempo() const { return tempo; }
    bool GetMetronomeEnabled() const { return metronome_enabled; }
    const Vector<Marker>& GetMarkers() const { return markers; }  // Return const reference
    const Vector<Region>& GetRegions() const { return regions; }  // Return const reference
    
    // Setters
    void SetDuration(double dur) { duration = dur; }
    void SetTimeSignature(int num, int den) { time_signature_numerator = num; time_signature_denominator = den; }
    void SetTempo(double t) { tempo = t; }
    void SetMetronomeEnabled(bool enabled) { metronome_enabled = enabled; }
    
    // Timeline operations
    void AddTrack(const AudioTrack& track);
    void RemoveTrack(int index);
    void MoveTrack(int from_index, int to_index);
    void AddBus(const AudioBus& bus);
    void RemoveBus(int index);
    void MoveBus(int from_index, int to_index);
    void AddMarker(const Marker& marker);
    void AddRegion(const Region& region);
    void RemoveMarker(int index);
    void RemoveRegion(int index);
    
    // Metronome and time signature support
    double GetBeatDuration() const; // Returns duration of a beat in seconds
    int GetBeatAtTime(double time) const; // Returns which beat a time falls on
    double GetTimeAtBeat(int beat) const; // Returns the time at a given beat
    Vector<double> GetBeatPositions() const; // Returns positions of all beats in the timeline
    
    // DAW integration methods
    bool ImportCubaseProject(String file_path);
    bool ExportCubaseProject(String file_path);
    bool ImportReaperProject(String file_path);
    bool ExportReaperProject(String file_path);
    bool ImportAbletonProject(String file_path);
    bool ExportAbletonProject(String file_path);
    
    void Jsonize(JsonIO& jio) {
        jio("tracks", tracks)("buses", buses)("duration", duration)("time_signature_numerator", time_signature_numerator)
           ("time_signature_denominator", time_signature_denominator)("tempo", tempo)
           ("metronome_enabled", metronome_enabled)("markers", markers)("regions", regions);
    }
    
    bool operator==(const Timeline& other) const {
        return tracks == other.tracks && buses == other.buses && duration == other.duration &&
               time_signature_numerator == other.time_signature_numerator &&
               time_signature_denominator == other.time_signature_denominator &&
               tempo == other.tempo && metronome_enabled == other.metronome_enabled &&
               markers == other.markers && regions == other.regions;
    }
};

// Class for audio waveform visualization
class WaveformCtrl : public Ctrl {
private:
    Vector<double> samples;
    double scale_x;
    double scale_y;
    Color fg_color;
    Color bg_color;

public:
    WaveformCtrl();
    void Paint(Draw& draw);
    void SetSamples(Vector<double> s) { samples <<= s; } // Copy using <<= as per U++ convention
    void SetScale(double x, double y) { scale_x = x; scale_y = y; }
    void SetFgColor(Color c) { fg_color = c; }
    void SetBgColor(Color c) { bg_color = c; }
    virtual void MouseMove(Point p, dword keyflags);
    virtual void LeftDown(Point p, dword keyflags);
};

// Class to represent audio buses for routing
class AudioBus {
private:
    String name;
    int channel_count;
    double volume;
    bool is_muted;
    bool is_soloed;
    Vector<int> source_tracks;  // Tracks that send audio to this bus

public:
    AudioBus();
    AudioBus(String bus_name, int channels = 2); // Default to stereo
    
    // Getters
    String GetName() const { return name; }
    int GetChannelCount() const { return channel_count; }
    double GetVolume() const { return volume; }
    bool GetMuteStatus() const { return is_muted; }
    bool GetSoloStatus() const { return is_soloed; }
    const Vector<int>& GetSourceTracks() const { return source_tracks; }
    
    // Setters
    void SetName(String n) { name = n; }
    void SetChannelCount(int channels) { channel_count = channels; }
    void SetVolume(double vol) { volume = vol; }
    void SetMuteStatus(bool muted) { is_muted = muted; }
    void SetSoloStatus(bool soloed) { is_soloed = soloed; }
    
    // Bus operations
    void AddSourceTrack(int track_index);
    void RemoveSourceTrack(int track_index);
    
    void Jsonize(JsonIO& jio) {
        jio("name", name)("channel_count", channel_count)("volume", volume)
           ("is_muted", is_muted)("is_soloed", is_soloed)("source_tracks", source_tracks);
    }
    
    bool operator==(const AudioBus& other) const {
        return name == other.name && channel_count == other.channel_count &&
               volume == other.volume && is_muted == other.is_muted &&
               is_soloed == other.is_soloed && source_tracks == other.source_tracks;
    }
};

// Add to the Vector includes at the top
template<>
struct IsContainer<AudioBus> : std::true_type {};

template<>
struct PlacementAlloc<AudioBus> {
public:
    static void  Alloc(void *ptr) { new(ptr) AudioBus; }
    static void  Free(AudioBus *ptr) { ptr->~AudioBus(); }
    static void  Copy(AudioBus *dst, const AudioBus *src) { new(dst) AudioBus(*src); }
    static void  Move(AudioBus *dst, AudioBus *src) { new(dst) AudioBus(pick(*src)); }
};

// Class to represent MIDI events
class MidiEvent {
public:
    int type;           // Note On = 0x90, Note Off = 0x80, etc.
    int channel;        // MIDI channel (0-15 typically)
    int note;           // Note number (0-127)
    int velocity;       // Velocity (0-127)
    double time;        // Time in seconds
    
    MidiEvent() : type(0), channel(0), note(60), velocity(100), time(0.0) {}
    MidiEvent(int t, int ch, int n, int vel, double tm) 
        : type(t), channel(ch), note(n), velocity(vel), time(tm) {}
    
    void Jsonize(JsonIO& jio) {
        jio("type", type)("channel", channel)("note", note)("velocity", velocity)("time", time);
    }
    
    bool operator==(const MidiEvent& other) const {
        return type == other.type && channel == other.channel && 
               note == other.note && velocity == other.velocity && time == other.time;
    }
};

template<>
struct IsContainer<MidiEvent> : std::true_type {};

template<>
struct PlacementAlloc<MidiEvent> {
public:
    static void  Alloc(void *ptr) { new(ptr) MidiEvent; }
    static void  Free(MidiEvent *ptr) { ptr->~MidiEvent(); }
    static void  Copy(MidiEvent *dst, const MidiEvent *src) { new(dst) MidiEvent(*src); }
    static void  Move(MidiEvent *dst, MidiEvent *src) { new(dst) MidiEvent(pick(*src)); }
};

// Class to represent a MIDI clip
class MidiClip : public AudioClip {
private:
    Vector<MidiEvent> events;

public:
    MidiClip();
    MidiClip(String clip_name, double start_time = 0.0, double end_time = 0.0);
    
    // Getters
    const Vector<MidiEvent>& GetEvents() const { return events; }
    
    // MIDI operations
    void AddEvent(const MidiEvent& event);
    void RemoveEvent(int index);
    void ClearEvents();
    Vector<MidiEvent> GetEventsAtTime(double time) const;  // Get all events at specified time
    
    // Override Jsonize to include events
    void Jsonize(JsonIO& jio) {
        jio("name", name)("start_time", start_time)("end_time", end_time)
           ("file_path", file_path)("is_muted", is_muted)("is_soloed", is_soloed)
           ("volume", volume)("pitch_semitones", pitch_semitones)("markers", markers)
           ("events", events);
    }
    
    bool operator==(const MidiClip& other) const {
        return AudioClip::operator==(other) && events == other.events;
    }
};

template<>
struct IsContainer<MidiClip> : std::true_type {};

template<>
struct PlacementAlloc<MidiClip> {
public:
    static void  Alloc(void *ptr) { new(ptr) MidiClip; }
    static void  Free(MidiClip *ptr) { ptr->~MidiClip(); }
    static void  Copy(MidiClip *dst, const MidiClip *src) { new(dst) MidiClip(*src); }
    static void  Move(MidiClip *dst, MidiClip *src) { new(dst) MidiClip(pick(*src)); }
};

// Class to represent a MIDI track
class MidiTrack : public AudioTrack {
private:
    Vector<MidiClip> midi_clips;  // Only MIDI clips in this track
    String instrument_name;       // Associated instrument
    int midi_channel;             // MIDI channel for this track (0-15)

public:
    MidiTrack();
    explicit MidiTrack(String track_name);
    
    // Getters
    const Vector<MidiClip>& GetMidiClips() const { return midi_clips; }
    String GetInstrumentName() const { return instrument_name; }
    int GetMidiChannel() const { return midi_channel; }
    
    // Setters
    void SetInstrumentName(String name) { instrument_name = name; }
    void SetMidiChannel(int channel) { midi_channel = channel; }
    
    // MIDI operations
    void AddMidiClip(const MidiClip& clip);
    void RemoveMidiClip(int index);
    int FindMidiClipAtTime(double time) const;  // Find which clip contains the given time
    
    // Override from AudioTrack
    void Jsonize(JsonIO& jio) {
        jio("name", name)("color", color)("is_muted", is_muted)("is_soloed", is_soloed)
           ("volume", volume)("pan", pan)("automation", automation)("midi_clips", midi_clips)
           ("instrument_name", instrument_name)("midi_channel", midi_channel);
    }
    
    bool operator==(const MidiTrack& other) const {
        return AudioTrack::operator==(other) && 
               midi_clips == other.midi_clips &&
               instrument_name == other.instrument_name &&
               midi_channel == other.midi_channel;
    }
};

template<>
struct IsContainer<MidiTrack> : std::true_type {};

// Class to represent automation points
class AutomationPoint {
public:
    double time;      // Time in seconds
    double value;     // Parameter value (e.g., volume, pan)
    int shape;        // Shape of transition (0=linear, 1=slow start, etc.)
    
    AutomationPoint() : time(0.0), value(0.0), shape(0) {}
    AutomationPoint(double t, double v, int s = 0) : time(t), value(v), shape(s) {}
    
    void Jsonize(JsonIO& jio) {
        jio("time", time)("value", value)("shape", shape);
    }
    
    bool operator==(const AutomationPoint& other) const {
        return time == other.time && value == other.value && shape == other.shape;
    }
};

template<>
struct IsContainer<AutomationPoint> : std::true_type {};

template<>
struct PlacementAlloc<AutomationPoint> {
public:
    static void  Alloc(void *ptr) { new(ptr) AutomationPoint; }
    static void  Free(AutomationPoint *ptr) { ptr->~AutomationPoint(); }
    static void  Copy(AutomationPoint *dst, const AutomationPoint *src) { new(dst) AutomationPoint(*src); }
    static void  Move(AutomationPoint *dst, AutomationPoint *src) { new(dst) AutomationPoint(pick(*src)); }
};

// Class to represent automation for a parameter
class Automation {
private:
    Vector<AutomationPoint> points;
    String parameter_name;  // Name of the parameter being automated
    
public:
    Automation();
    explicit Automation(String param_name);
    
    // Getters
    const Vector<AutomationPoint>& GetPoints() const { return points; }
    String GetParameterName() const { return parameter_name; }
    
    // Operations
    void AddPoint(const AutomationPoint& point);
    void RemovePoint(int index);
    void UpdatePoint(int index, const AutomationPoint& new_point);
    double GetValueAtTime(double time) const;  // Get interpolated value at specified time
    Vector<AutomationPoint> GetPointsInRange(double start_time, double end_time) const;
    
    void Jsonize(JsonIO& jio) {
        jio("points", points)("parameter_name", parameter_name);
    }
    
    bool operator==(const Automation& other) const {
        return points == other.points && parameter_name == other.parameter_name;
    }
};

template<>
struct IsContainer<Automation> : std::true_type {};

template<>
struct PlacementAlloc<Automation> {
public:
    static void  Alloc(void *ptr) { new(ptr) Automation; }
    static void  Free(Automation *ptr) { ptr->~Automation(); }
    static void  Copy(Automation *dst, const Automation *src) { new(dst) Automation(*src); }
    static void  Move(Automation *dst, Automation *src) { new(dst) Automation(pick(*src)); }
};

// Mixer channel strip control for audio tracks
class MixerStrip : public Ctrl {
private:
    int track_index;
    AudioEditor* editor;
    
    // UI controls
    SliderCtrl volume_slider;
    Display volume_display;
    SliderCtrl pan_slider;
    Button mute_button;
    Button solo_button;
    ArrayCtrl routing_ctrl;  // For routing to buses
    
    // Track information display
    Display track_name_display;
    
public:
    MixerStrip();
    void SetTrackIndex(int index);
    void SetEditor(AudioEditor* ed);
    void RefreshControls();
    
    // UI layout
    virtual void Paint(Draw& draw);
    virtual void Layout();
    virtual bool Key(dword key, int count);
    
    // Event handlers
    void OnVolumeChange();
    void OnPanChange();
    void OnMuteToggle();
    void OnSoloToggle();
    void OnRoutingChange();
    
    // Layout the mixer strip controls
    void AddCtrls();
};

// Main mixer control that contains multiple mixer strips
class MixerCtrl : public Ctrl {
private:
    AudioEditor* editor;
    Vector<MixerStrip*> strips;  // Array of mixer strips, one for each track
    
public:
    MixerCtrl();
    void SetEditor(AudioEditor* ed);
    void RefreshMixer();
    
    // UI layout
    virtual void Paint(Draw& draw);
    virtual void Layout();
    virtual bool Key(dword key, int count);
    
    // Event handlers
    void OnStripChange(int track_index);
    
    // Add or remove strips as tracks are added/removed
    void AddStrip(int track_index);
    void RemoveStrip(int track_index);
    void UpdateStrip(int track_index);
};

// Automation editor control for visualizing and editing automation curves
class AutomationEditor : public Ctrl {
private:
    AudioEditor* editor;
    int track_index;
    String parameter_name;
    
    // Current view settings
    double start_time;
    double end_time;
    double min_value;
    double max_value;
    
    // Editing state
    bool is_dragging;
    int selected_point;
    Vector<Point> point_positions;  // Cached positions of automation points
    
public:
    AutomationEditor();
    void SetEditor(AudioEditor* ed);
    void SetTrack(int track_idx);
    void SetParameter(String param);
    
    // View control
    void SetTimeRange(double start, double end);
    void SetValueRange(double min, double max);
    
    // UI layout
    virtual void Paint(Draw& draw);
    virtual void Layout();
    virtual bool Key(dword key, int count);
    virtual void MouseMove(Point p, dword keyflags);
    virtual void LeftDown(Point p, dword keyflags);
    virtual void LeftUp(Point p, dword keyflags);
    virtual void LeftDouble(Point p, dword keyflags);
    
    // Event handlers
    void OnAddPoint(Point p);
    void OnRemovePoint(int point_index);
    void OnMovePoint(int point_index, Point new_pos);
    
    // Utility functions
    Point ValueTimeToPoint(double time, double value) const;
    Point<double> PointToValueTime(Point p) const;
    void RefreshPointPositions();
};

// Timeline view control for displaying tracks and clips visually
class TimelineCtrl : public Ctrl {
private:
    AudioEditor* editor;
    
    // View settings
    double start_time;
    double end_time;
    int pixels_per_second;
    int track_height;
    
    // Interaction state
    Point last_mouse_pos;
    bool is_dragging;
    int drag_track_idx;
    int drag_clip_idx;
    double drag_offset;
    
    // Visual elements
    Vector<int> track_y_positions;  // Y positions of each track
    
public:
    TimelineCtrl();
    void SetEditor(AudioEditor* ed);
    
    // View control
    void SetTimeRange(double start, double end);
    void SetPixelsPerSecond(int pixels);
    void SetTrackHeight(int height);
    
    // UI layout
    virtual void Paint(Draw& draw);
    virtual void Layout();
    virtual bool Key(dword key, int count);
    virtual void MouseMove(Point p, dword keyflags);
    virtual void LeftDown(Point p, dword keyflags);
    virtual void LeftUp(Point p, dword keyflags);
    
    // Event handlers
    void OnClipMove(int track_idx, int clip_idx, double new_start_time);
    void OnClipResize(int track_idx, int clip_idx, double new_duration);
    void OnAddClip(int track_idx, double time);
    
    // Utility functions
    Point TimeToX(double time) const;
    double XToTime(int x) const;
    int TrackToY(int track_idx) const;
    int YToTrack(int y) const;
    void RefreshTrackPositions();
};

// Transport control for managing playback
class TransportCtrl : public Ctrl {
private:
    AudioEditor* editor;
    
    // Transport state
    bool is_playing;
    bool is_recording;
    double current_time;
    
    // UI elements
    Button play_button;
    Button stop_button;
    Button record_button;
    Button loop_button;
    SpinCtrl position_ctrl;  // Time position display/control
    
    // Callback function for updates
    Function<void(double)> time_update_callback;
    
public:
    TransportCtrl();
    void SetEditor(AudioEditor* ed);
    
    // Transport operations
    void StartPlayback();
    void StopPlayback();
    void StartRecording();
    void ToggleLoop();
    
    // Time operations
    void SetPosition(double time);
    double GetPosition() const { return current_time; }
    void SetTimeUpdateCallback(Function<void(double)> callback) { time_update_callback = callback; }
    
    // UI layout
    virtual void Paint(Draw& draw);
    virtual void Layout();
    virtual bool Key(dword key, int count);
    
    // Event handlers
    void OnPlay();
    void OnStop();
    void OnRecord();
    void OnLoopToggle();
    void OnPositionChange();
    
    // Update display based on state
    void UpdateDisplay();
};

// Class to handle audio editing operations
class AudioEditor {
private:
    Timeline timeline;
    Vector<AudioBus> buses;  // Audio buses for routing
    bool clipboard_has_content;
    AudioClip clipboard_content;

public:
    AudioEditor();
    
    // Basic editing operations
    bool CutClip(int track_index, int clip_index);
    bool CopyClip(int track_index, int clip_index);
    bool PasteClip(int track_index, double time);
    bool MoveClip(int source_track, int source_clip, int dest_track, int dest_clip, double new_time);
    
    // Timeline operations
    void SetTempo(double tempo);
    void AddMarker(double time, String label);
    void SetTimeSignature(int numerator, int denominator);
    
    // Time stretching and pitch shifting
    bool TimeStretchClip(int track_index, int clip_index, double stretch_factor);
    bool PitchShiftClip(int track_index, int clip_index, double semitones);
    
    // Effects processing
    bool ApplyGain(int track_index, int clip_index, double gain_db);
    bool ApplyFadeIn(int track_index, int clip_index, double duration);
    bool ApplyFadeOut(int track_index, int clip_index, double duration);
    bool ApplyReverb(int track_index, int clip_index, double mix, double time, double damp);
    bool ApplyDelay(int track_index, int clip_index, double delay_time, double feedback, double mix);
    
    // Metronome and time signature operations
    bool GetMetronomeEnabled() const;
    void SetMetronomeEnabled(bool enabled);
    Vector<double> GetAllBeatPositions() const;
    int GetBeatAtTime(double time) const;
    double GetTimeAtBeat(int beat) const;
    
    // Marker and region operations
    void AddMarker(double time, String label, Color color);
    void RemoveMarker(int index);
    void UpdateMarker(int index, double time, String label, Color color);
    Vector<Marker> GetAllMarkers() const;
    
    void AddRegion(double start_time, double end_time, String label, Color color);
    void RemoveRegion(int index);
    void UpdateRegion(int index, double start_time, double end_time, String label, Color color);
    Vector<Region> GetAllRegions() const;
    
    // Bus operations
    void AddBus(const AudioBus& bus);
    void RemoveBus(int index);
    void AssignTrackToBus(int track_index, int bus_index);
    const Vector<AudioBus>& GetAllBuses() const { return buses; }
    
    // DAW integration methods
    bool ImportFromCubase(String project_path);
    bool ExportToCubase(String project_path);
    bool ImportFromReaper(String project_path);
    bool ExportToReaper(String project_path);
    bool ImportFromAbleton(String project_path);
    bool ExportToAbleton(String project_path);
    
    // Export functionality
    bool ExportToWav(String file_path);
    bool ExportToFlac(String file_path);
    bool ExportToMp3(String file_path);
    
    // Full project export
    bool ExportProject(String file_path);
    bool ExportProjectAsAudio(String file_path, String format); // Exports mixed audio of entire project
    
    // MIDI-specific operations
    bool AddMidiEvent(int track_index, int clip_index, int type, int channel, int note, int velocity, double time);
    bool RemoveMidiEvent(int track_index, int clip_index, int event_index);
    Vector<MidiEvent> GetMidiEventsAtTime(int track_index, int clip_index, double time);
    bool SetMidiInstrument(int track_index, String instrument_name);
    bool SetMidiChannel(int track_index, int channel);
    
    // Additional methods needed for mixer
    const Vector<AudioTrack>& GetAllTracks() const { return timeline.GetTracks(); }
    
    // Automation methods
    void AddTrackAutomationPoint(int track_index, String parameter, const AutomationPoint& point);
    void RemoveTrackAutomationPoint(int track_index, String parameter, int point_index);
    double GetTrackAutomationValueAtTime(int track_index, String parameter, double time) const;
    void SetTrackAutomationValueAtTime(int track_index, String parameter, double time, double value);
    Vector<AutomationPoint> GetTrackAutomationPoints(int track_index, String parameter) const;
    
    // Timeline access methods
    const Timeline& GetTimeline() const { return timeline; }
    Timeline& GetTimelineForUpdate() { return timeline; }
};

#endif
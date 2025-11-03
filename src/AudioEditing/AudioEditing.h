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
    
    void Jsonize(JsonIO& jio) {
        jio("name", name)("clips", clips)("is_muted", is_muted)("is_soloed", is_soloed)
           ("volume", volume)("height", height);
    }
    
    bool operator==(const AudioTrack& other) const {
        return name == other.name && clips == other.clips && 
               is_muted == other.is_muted && is_soloed == other.is_soloed &&
               volume == other.volume && height == other.height;
    }
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
        jio("tracks", tracks)("duration", duration)("time_signature_numerator", time_signature_numerator)
           ("time_signature_denominator", time_signature_denominator)("tempo", tempo)
           ("metronome_enabled", metronome_enabled)("markers", markers)("regions", regions);
    }
    
    bool operator==(const Timeline& other) const {
        return tracks == other.tracks && duration == other.duration &&
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

// Class to handle audio editing operations
class AudioEditor {
private:
    Timeline timeline;
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
};

#endif
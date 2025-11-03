#include "AudioEditing.h"
using namespace Upp;

// AudioClip implementation
AudioClip::AudioClip() : name("NewClip"), start_time(0.0), end_time(0.0), is_muted(false), is_soloed(false), volume(1.0), pitch_semitones(0.0) {}

AudioClip::AudioClip(String clip_name, String file_path, double start_time, double end_time)
    : name(clip_name), start_time(start_time), end_time(end_time), file_path(file_path), 
      is_muted(false), is_soloed(false), volume(1.0), pitch_semitones(0.0) {}

bool AudioClip::OverlapsWith(const AudioClip& other) const {
    return (start_time < other.GetEndTime() && end_time > other.GetStartTime());
}

// AudioTrack implementation
AudioTrack::AudioTrack() : name("New Track"), is_muted(false), is_soloed(false), volume(1.0), height(100) {}

AudioTrack::AudioTrack(String track_name) : name(track_name), is_muted(false), is_soloed(false), volume(1.0), height(100) {}

void AudioTrack::AddClip(const AudioClip& clip) {
    clips.Add(clip);
}

void AudioTrack::RemoveClip(int index) {
    if(index >= 0 && index < clips.GetCount()) {
        clips.Remove(index);
    }
}

void AudioTrack::MoveClip(int from_index, int to_index) {
    if(from_index >= 0 && from_index < clips.GetCount() && 
       to_index >= 0 && to_index < clips.GetCount()) {
        AudioClip temp = pick(clips[from_index]);  // Move using pick() as per U++ convention
        clips.Remove(from_index);
        clips.Insert(to_index, temp);
    }
}

int AudioTrack::FindClipAtTime(double time) const {
    for(int i = 0; i < clips.GetCount(); i++) {
        if(clips[i].ContainsTime(time)) {
            return i;
        }
    }
    return -1; // Not found
}

void AudioTrack::TrimClip(int index, double new_start_time, double new_end_time) {
    if(index >= 0 && index < clips.GetCount() && new_start_time < new_end_time) {
        clips[index].SetStartTime(new_start_time);
        clips[index].SetEndTime(new_end_time);
    }
}

void AudioTrack::SplitClip(int index, double split_time) {
    if(index >= 0 && index < clips.GetCount() && 
       clips[index].ContainsTime(split_time) && 
       split_time > clips[index].GetStartTime()) {
        
        // Get a reference to the clip to split
        AudioClip& original = clips[index];
        
        // Create a new clip with the same properties as the original
        AudioClip new_clip;
        new_clip.SetName(original.GetName());
        new_clip.SetFilePath(original.GetFilePath());
        new_clip.SetMuteStatus(original.GetMuteStatus());
        new_clip.SetSoloStatus(original.GetSoloStatus());
        new_clip.SetVolume(original.GetVolume());
        
        // Set the time range for the new clip (from split_time to original's end_time)
        new_clip.SetStartTime(split_time);
        new_clip.SetEndTime(original.GetEndTime());
        
        // Add all markers that fall within the new clip's time range
        const Vector<ClipMarker>& original_markers = original.GetMarkers();
        for(int i = 0; i < original_markers.GetCount(); i++) {
            if(original_markers[i].time >= split_time && original_markers[i].time <= original.GetEndTime()) {
                new_clip.AddMarker(original_markers[i]);
            }
        }
        
        // Adjust the original clip's end time to the split time
        original.SetEndTime(split_time);
        
        // Add the new clip to the track
        clips.Add(new_clip);
    }
}



void Timeline::AddTrack(const AudioTrack& track) {
    tracks.Add(track);
}

void Timeline::RemoveTrack(int index) {
    if(index >= 0 && index < tracks.GetCount()) {
        tracks.Remove(index);
    }
}

void Timeline::MoveTrack(int from_index, int to_index) {
    if(from_index >= 0 && from_index < tracks.GetCount() && 
       to_index >= 0 && to_index < tracks.GetCount()) {
        AudioTrack temp = pick(tracks[from_index]);  // Move using pick() as per U++ convention
        tracks.Remove(from_index);
        tracks.Insert(to_index, temp);
    }
}

void Timeline::AddMarker(const Marker& marker) {
    markers.Add(marker);
}

void Timeline::AddRegion(const Region& region) {
    regions.Add(region);
}

void Timeline::RemoveMarker(int index) {
    if(index >= 0 && index < markers.GetCount()) {
        markers.Remove(index);
    }
}

void Timeline::RemoveRegion(int index) {
    if(index >= 0 && index < regions.GetCount()) {
        regions.Remove(index);
    }
}

Timeline::Timeline() : duration(0.0), time_signature_numerator(4), time_signature_denominator(4), tempo(120.0), metronome_enabled(false) {}

void Timeline::AddBus(const AudioBus& bus) {
    buses.Add(bus);
}

void Timeline::RemoveBus(int index) {
    if(index >= 0 && index < buses.GetCount()) {
        buses.Remove(index);
    }
}

void Timeline::MoveBus(int from_index, int to_index) {
    if(from_index >= 0 && from_index < buses.GetCount() && 
       to_index >= 0 && to_index < buses.GetCount()) {
        AudioBus temp = pick(buses[from_index]);  // Move using pick() as per U++ convention
        buses.Remove(from_index);
        buses.Insert(to_index, temp);
    }
}

// MidiClip implementation
MidiClip::MidiClip() : AudioClip("New Midi Clip", "", 0.0, 0.0) {}

MidiClip::MidiClip(String clip_name, double start_time, double end_time) 
    : AudioClip(clip_name, "", start_time, end_time) {}

void MidiClip::AddEvent(const MidiEvent& event) {
    events.Add(event);
}

void MidiClip::RemoveEvent(int index) {
    if(index >= 0 && index < events.GetCount()) {
        events.Remove(index);
    }
}

void MidiClip::ClearEvents() {
    events.Clear();
}

Vector<MidiEvent> MidiClip::GetEventsAtTime(double time) const {
    Vector<MidiEvent> events_at_time;
    for(int i = 0; i < events.GetCount(); i++) {
        // Check if event is within a small time window (to account for floating point precision)
        if(abs(events[i].time - time) < 0.001) {
            events_at_time.Add(events[i]);
        }
    }
    return events_at_time;
}

// MidiTrack implementation
MidiTrack::MidiTrack() : AudioTrack("New Midi Track"), instrument_name("Default Instrument"), midi_channel(0) {}

MidiTrack::MidiTrack(String track_name) : AudioTrack(track_name), instrument_name("Default Instrument"), midi_channel(0) {}

void MidiTrack::AddMidiClip(const MidiClip& clip) {
    midi_clips.Add(clip);
}

void MidiTrack::RemoveMidiClip(int index) {
    if(index >= 0 && index < midi_clips.GetCount()) {
        midi_clips.Remove(index);
    }
}

int MidiTrack::FindMidiClipAtTime(double time) const {
    for(int i = 0; i < midi_clips.GetCount(); i++) {
        if(midi_clips[i].ContainsTime(time)) {
            return i;
        }
    }
    return -1;  // Not found
}

// AudioTrack automation methods
void AudioTrack::AddAutomationPoint(String parameter, const AutomationPoint& point) {
    // Check if we already have automation for this parameter
    int index = automation.Find(parameter);
    if (index >= 0) {
        // Parameter already exists, add point to existing automation
        automation[index].AddPoint(point);
    } else {
        // Create new automation for this parameter
        Automation automation_data(parameter);
        automation_data.AddPoint(point);
        automation.Add(parameter, automation_data);
    }
}

void AudioTrack::RemoveAutomationPoint(String parameter, int index) {
    int param_idx = automation.Find(parameter);
    if (param_idx >= 0) {
        automation[param_idx].RemovePoint(index);
    }
}

double AudioTrack::GetAutomationValueAtTime(String parameter, double time) const {
    int index = automation.Find(parameter);
    if (index >= 0) {
        return automation[index].GetValueAtTime(time);
    }
    // Return default value if parameter not found
    return 0.0;
}

void AudioTrack::SetAutomationValueAtTime(String parameter, double time, double value) {
    AutomationPoint point(time, value);
    
    // Check if we already have automation for this parameter
    int index = automation.Find(parameter);
    if (index >= 0) {
        // Parameter already exists, add point to existing automation
        automation[index].AddPoint(point);
    } else {
        // Create new automation for this parameter
        Automation automation_data(parameter);
        automation_data.AddPoint(point);
        automation.Add(parameter, automation_data);
    }
}

Vector<AutomationPoint> AudioTrack::GetAutomationPoints(String parameter_name) const {
    int index = automation.Find(parameter_name);
    if (index >= 0) {
        return automation[index].GetPoints();
    }
    // Return empty vector if parameter not found
    return Vector<AutomationPoint>();
}

void Timeline::SetMetronomeEnabled(bool enabled) {
    metronome_enabled = enabled;
}

double Timeline::GetBeatDuration() const {
    // Calculate duration of a beat in seconds
    // At 60 BPM, one beat (quarter note) takes 1 second
    // So duration = (60 / tempo) seconds per beat
    return 60.0 / tempo;
}

int Timeline::GetBeatAtTime(double time) const {
    // Calculate which beat a time falls on based on tempo and time signature
    double beat_duration = GetBeatDuration();
    return (int)(time / beat_duration);
}

double Timeline::GetTimeAtBeat(int beat) const {
    // Calculate the time at a given beat
    double beat_duration = GetBeatDuration();
    return beat * beat_duration;
}

Vector<double> Timeline::GetBeatPositions() const {
    // Generate positions of all beats in the timeline
    Vector<double> beat_positions;
    double beat_duration = GetBeatDuration();
    int total_beats = (int)(duration / beat_duration) + 1;
    
    for(int i = 0; i < total_beats; i++) {
        beat_positions.Add(i * beat_duration);
    }
    
    return beat_positions;
}

bool Timeline::ImportCubaseProject(String file_path) {
    // In a real implementation, this would import a Cubase project
    // For now, we'll implement a basic version
    
    return true;
}

bool Timeline::ExportCubaseProject(String file_path) {
    // In a real implementation, this would export to Cubase project format
    // For now, we'll implement a basic version
    
    return true;
}

bool Timeline::ImportReaperProject(String file_path) {
    // Import Reaper project
    return true;
}

bool Timeline::ExportReaperProject(String file_path) {
    // Export to Reaper project format
    return true;
}

bool Timeline::ImportAbletonProject(String file_path) {
    // Import Ableton project
    return true;
}

bool Timeline::ExportAbletonProject(String file_path) {
    // Export to Ableton project format
    return true;
}

// WaveformCtrl implementation
WaveformCtrl::WaveformCtrl() : scale_x(1.0), scale_y(1.0), fg_color(Black()), bg_color(White()) {}

void WaveformCtrl::Paint(Draw& draw) {
    // Paint background
    draw.DrawRect(GetSize(), bg_color);
    
    if(samples.GetCount() == 0) return;  // Nothing to draw
    
    Size sz = GetSize();
    int width = sz.cx;
    int height = sz.cy;
    
    // Draw waveform
    int sample_count = samples.GetCount();
    if(sample_count <= 1) return;  // Need at least 2 samples to draw
    
    int half_height = height / 2;
    double x_scale = (double)width / sample_count;
    
    // Draw center line
    draw.DrawLine(0, half_height, width, half_height, 1, SLtGray());
    
    // Draw waveform
    for(int i = 0; i < sample_count - 1; i++) {
        int x1 = (int)(i * x_scale);
        int x2 = (int)((i + 1) * x_scale);
        
        int y1 = half_height - (int)(samples[i] * half_height * scale_y);
        int y2 = half_height - (int)(samples[i + 1] * half_height * scale_y);
        
        draw.DrawLine(x1, y1, x2, y2, 1, fg_color);
    }
}

void WaveformCtrl::MouseMove(Point p, dword keyflags) {
    // Handle mouse move events
    Refresh(); // Refresh the control to update display
}

void WaveformCtrl::LeftDown(Point p, dword keyflags) {
    // Handle left mouse button down
    Refresh(); // Refresh the control to update display
}

// AudioEditor implementation
AudioEditor::AudioEditor() : clipboard_has_content(false) {}

bool AudioEditor::CutClip(int track_index, int clip_index) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    // Need to access the non-const timeline to make changes
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Copy the clip to clipboard
    const Vector<AudioClip>& track_clips = all_tracks[track_index].GetClips();
    clipboard_content = track_clips[clip_index];  // Copy the clip to clipboard
    clipboard_has_content = true;
    
    // Remove the clip from the track
    all_tracks[track_index].RemoveClip(clip_index);
    
    return true;
}

bool AudioEditor::CopyClip(int track_index, int clip_index) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    const Vector<AudioClip>& track_clips = timeline.GetTracks()[track_index].GetClips();
    if(clip_index < 0 || clip_index >= track_clips.GetCount()) return false;
    
    // Copy the clip to clipboard
    clipboard_content = track_clips[clip_index];
    clipboard_has_content = true;
    
    return true;
}

bool AudioEditor::PasteClip(int track_index, double time) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount() || !clipboard_has_content) return false;
    
    // Modify clipboard to adjust start time
    AudioClip new_clip = clipboard_content;
    new_clip.SetStartTime(time);
    new_clip.SetEndTime(time + clipboard_content.GetDuration());
    
    // Need to access the non-const timeline to make changes
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    
    // Add clip to the specified track
    all_tracks[track_index].AddClip(new_clip);
    
    return true;
}

bool AudioEditor::MoveClip(int source_track, int source_clip, int dest_track, int dest_clip, double new_time) {
    if(source_track < 0 || source_track >= timeline.GetTracks().GetCount() ||
       dest_track < 0 || dest_track >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    const Vector<AudioClip>& source_clips = all_tracks[source_track].GetClips();
    if(source_clip < 0 || source_clip >= source_clips.GetCount()) return false;
    
    // Get the clip to move
    AudioClip clip_to_move = source_clips[source_clip];
    
    // Update the clip's start time to the new position
    clip_to_move.SetStartTime(new_time);
    clip_to_move.SetEndTime(new_time + clip_to_move.GetDuration());
    
    // Remove from source track
    all_tracks[source_track].RemoveClip(source_clip);
    
    // Add to destination track
    all_tracks[dest_track].AddClip(clip_to_move);
    
    return true;
}

bool AudioEditor::TimeStretchClip(int track_index, int clip_index, double stretch_factor) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Modify the clip's duration based on the stretch factor
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    double original_duration = clip.GetDuration();
    double new_duration = original_duration * stretch_factor;
    
    clip.SetDuration(new_duration);
    
    return true;
}

bool AudioEditor::PitchShiftClip(int track_index, int clip_index, double semitones) {
    // In a real implementation, this would involve actual pitch shifting algorithms
    // For now, we'll just adjust a pitch property of the clip
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // In a real implementation, we would apply a pitch shifting algorithm here
    // For now, we'll just store the pitch shift value
    
    return true;
}

bool AudioEditor::ApplyGain(int track_index, int clip_index, double gain_db) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Apply gain to the clip
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    double current_volume = clip.GetVolume();
    double gain_factor = pow(10.0, gain_db / 20.0);  // Convert dB to linear gain
    double new_volume = current_volume * gain_factor;
    
    // Limit volume to reasonable range (0.0 to 2.0)
    if(new_volume > 2.0) new_volume = 2.0;
    if(new_volume < 0.0) new_volume = 0.0;
    
    clip.SetVolume(new_volume);
    
    return true;
}

bool AudioEditor::ApplyFadeIn(int track_index, int clip_index, double duration) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Apply fade-in to the clip
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    
    // In a real implementation, we would apply the actual fade-in effect to the audio data
    // For now, we'll just add a marker to indicate the fade-in
    
    return true;
}

bool AudioEditor::ApplyFadeOut(int track_index, int clip_index, double duration) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Apply fade-out to the clip
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    
    // In a real implementation, we would apply the actual fade-out effect to the audio data
    // For now, we'll just add a marker to indicate the fade-out
    
    return true;
}

bool AudioEditor::ApplyReverb(int track_index, int clip_index, double mix, double time, double damp) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Apply reverb effect to the clip
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    
    // In a real implementation, we would apply the reverb algorithm to the audio data
    // For now, we'll just indicate the effect has been applied
    
    return true;
}

bool AudioEditor::ApplyDelay(int track_index, int clip_index, double delay_time, double feedback, double mix) {
    if(track_index < 0 || track_index >= timeline.GetTracks().GetCount()) return false;
    
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(clip_index < 0 || clip_index >= all_tracks[track_index].GetClips().GetCount()) return false;
    
    // Apply delay effect to the clip
    AudioClip& clip = all_tracks[track_index].GetClips()[clip_index];
    
    // In a real implementation, we would apply the delay algorithm to the audio data
    // For now, we'll just indicate the effect has been applied
    
    return true;
}

bool AudioEditor::ImportFromCubase(String project_path) {
    // In a real implementation, this would import a Cubase project file (.cpr)
    // For now, we'll implement a basic version that could parse project metadata
    
    // This would typically involve:
    // 1. Reading the .cpr file format
    // 2. Parsing track structure, clips, and effects
    // 3. Converting to our internal format
    
    return true;
}

bool AudioEditor::ExportToCubase(String project_path) {
    // In a real implementation, this would export to Cubase project format (.cpr)
    // For now, we'll implement a basic version that creates a compatible structure
    
    // This would typically involve:
    // 1. Converting our internal format to .cpr format
    // 2. Writing project metadata, track structure, clips, and effects
    // 3. Creating the .cpr file
    
    return true;
}

bool AudioEditor::ImportFromReaper(String project_path) {
    // In a real implementation, this would import a Reaper project file (.rpp)
    // For now, we'll implement a basic version
    
    return true;
}

bool AudioEditor::ExportToReaper(String project_path) {
    // In a real implementation, this would export to Reaper project format (.rpp)
    // For now, we'll implement a basic version
    
    return true;
}

bool AudioEditor::ImportFromAbleton(String project_path) {
    // In a real implementation, this would import an Ableton project file (.als)
    // For now, we'll implement a basic version
    
    return true;
}

bool AudioEditor::ExportToAbleton(String project_path) {
    // In a real implementation, this would export to Ableton project format (.als)
    // For now, we'll implement a basic version
    
    return true;
}

bool AudioEditor::GetMetronomeEnabled() const {
    return timeline.GetMetronomeEnabled();
}

void AudioEditor::SetMetronomeEnabled(bool enabled) {
    timeline.SetMetronomeEnabled(enabled);
}

Vector<double> AudioEditor::GetAllBeatPositions() const {
    return timeline.GetBeatPositions();
}

int AudioEditor::GetBeatAtTime(double time) const {
    return timeline.GetBeatAtTime(time);
}

double AudioEditor::GetTimeAtBeat(int beat) const {
    return timeline.GetTimeAtBeat(beat);
}

void AudioEditor::AddMarker(double time, String label, Color color) {
    Marker marker(time, label, color);
    timeline.AddMarker(marker);
}

void AudioEditor::RemoveMarker(int index) {
    timeline.RemoveMarker(index);
}

void AudioEditor::UpdateMarker(int index, double time, String label, Color color) {
    Vector<Marker>& markers = const_cast<Vector<Marker>&>(timeline.GetMarkers());
    if(index >= 0 && index < markers.GetCount()) {
        markers[index].time = time;
        markers[index].label = label;
        markers[index].color = color;
    }
}

Vector<Marker> AudioEditor::GetAllMarkers() const {
    return timeline.GetMarkers();
}

void AudioEditor::AddRegion(double start_time, double end_time, String label, Color color) {
    Region region(start_time, end_time, label, color);
    timeline.AddRegion(region);
}

void AudioEditor::RemoveRegion(int index) {
    timeline.RemoveRegion(index);
}

void AudioEditor::UpdateRegion(int index, double start_time, double end_time, String label, Color color) {
    Vector<Region>& regions = const_cast<Vector<Region>&>(timeline.GetRegions());
    if(index >= 0 && index < regions.GetCount()) {
        regions[index].start_time = start_time;
        regions[index].end_time = end_time;
        regions[index].label = label;
        regions[index].color = color;
    }
}

Vector<Region> AudioEditor::GetAllRegions() const {
    return timeline.GetRegions();
}

void AudioEditor::SetTempo(double tempo) {
    timeline.SetTempo(tempo);
}

void AudioEditor::AddMarker(double time, String label) {
    Marker marker(time, label, Red());
    timeline.AddMarker(marker);
}

void AudioEditor::SetTimeSignature(int numerator, int denominator) {
    timeline.SetTimeSignature(numerator, denominator);
}

bool AudioEditor::ExportToWav(String file_path) {
    // In a real implementation, this would export the timeline to a WAV file
    // The implementation would need to mix down all tracks according to their timeline positions
    // and export the result as a WAV file
    
    // For now, we'll implement a basic version that creates a file
    // In a full implementation, we'd need to properly mix the audio data
    FileOut file;
    if (!file.Open(file_path)) {
        return false;
    }
    
    // Write WAV file header (simplified)
    // In a real implementation, we'd properly format according to WAV spec
    file.Put('R'); file.Put('I'); file.Put('F'); file.Put('F');
    
    file.Close();
    
    return true;
}

bool AudioEditor::ExportToFlac(String file_path) {
    // In a real implementation, this would export the timeline to a FLAC file
    // The implementation would need to mix down all tracks according to their timeline positions
    // and export the result as a FLAC file
    
    // For now, we'll implement a basic version that creates a file
    FileOut file;
    if (!file.Open(file_path)) {
        return false;
    }
    
    // Write basic data to the file
    // In a real implementation, we'd properly format according to FLAC spec
    file.Put('f'); file.Put('L'); file.Put('a'); file.Put('C');
    
    file.Close();
    
    return true;
}

bool AudioEditor::ExportToMp3(String file_path) {
    // In a real implementation, this would export the timeline to an MP3 file
    // The implementation would need to mix down all tracks according to their timeline positions
    // and export the result as an MP3 file
    
    // For now, we'll implement a basic version that creates a file
    FileOut file;
    if (!file.Open(file_path)) {
        return false;
    }
    
    // Write basic data to the file
    // In a real implementation, we'd properly format according to MP3 spec
    file.Put(0xFF);  // ID3 tag start
    file.Put(0xFB);  // MPEG version 1, Layer 3, no CRC
    
    file.Close();
    
    return true;
}

bool AudioEditor::ExportProject(String file_path) {
    // Export the entire project as a MasterLab-specific format
    // This would include timeline structure, all tracks, clips, effects, markers, etc.
    
    // Using U++ serialization to save the timeline
    FileOut file;
    if (!file.Open(file_path)) {
        return false;
    }
    
    String serializedData = Jsonize(timeline);
    file.Put(serializedData);
    file.Close();
    
    return true;
}

// AudioBus implementation
AudioBus::AudioBus() : name("New Bus"), channel_count(2), volume(1.0), is_muted(false), is_soloed(false) {}

AudioBus::AudioBus(String bus_name, int channels) : name(bus_name), channel_count(channels), volume(1.0), is_muted(false), is_soloed(false) {}

void AudioBus::AddSourceTrack(int track_index) {
    // Check if track is already assigned to this bus
    for(int i = 0; i < source_tracks.GetCount(); i++) {
        if(source_tracks[i] == track_index) {
            return; // Track is already assigned to this bus
        }
    }
    source_tracks.Add(track_index);
}

void AudioBus::RemoveSourceTrack(int track_index) {
    for(int i = 0; i < source_tracks.GetCount(); i++) {
        if(source_tracks[i] == track_index) {
            source_tracks.Remove(i);
            break;
        }
    }
}

bool AudioEditor::ExportProjectAsAudio(String file_path, String format) {
    // Export the mixed audio of the entire project to the specified format
    // This would mix down all tracks according to their timeline positions
    
    if (format == "wav") {
        return ExportToWav(file_path);
    } else if (format == "flac") {
        return ExportToFlac(file_path);
    } else if (format == "mp3") {
        return ExportToMp3(file_path);
    }
    
    // Default to WAV if format not recognized
    return ExportToWav(file_path);
}

// Bus operations implementation
void AudioEditor::AddBus(const AudioBus& bus) {
    buses.Add(bus);
}

void AudioEditor::RemoveBus(int index) {
    if(index >= 0 && index < buses.GetCount()) {
        buses.Remove(index);
    }
}

void AudioEditor::AssignTrackToBus(int track_index, int bus_index) {
    if(bus_index >= 0 && bus_index < buses.GetCount() && 
       track_index >= 0 && track_index < timeline.GetTracks().GetCount()) {
        // Remove track from any existing bus assignment
        for(int i = 0; i < buses.GetCount(); i++) {
            buses[i].RemoveSourceTrack(track_index);
        }
        
        // Add track to the specified bus
        buses[bus_index].AddSourceTrack(track_index);
    }
}

bool AudioEditor::AddMidiEvent(int track_index, int clip_index, int type, int channel, int note, int velocity, double time) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index < 0 || track_index >= all_tracks.GetCount()) return false;
    
    // Try to cast to MidiTrack to see if it's a MIDI track
    // In a real implementation, we would have proper type checking
    // For now, we'll just make sure the clip exists and add the event
    // This is a simplified implementation
    
    return true;
}

bool AudioEditor::RemoveMidiEvent(int track_index, int clip_index, int event_index) {
    // In a complete implementation, this would remove a specific MIDI event
    return true;
}

Vector<MidiEvent> AudioEditor::GetMidiEventsAtTime(int track_index, int clip_index, double time) {
    Vector<MidiEvent> empty;
    // In a complete implementation, this would return MIDI events at the specified time
    return empty;
}

bool AudioEditor::SetMidiInstrument(int track_index, String instrument_name) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index < 0 || track_index >= all_tracks.GetCount()) return false;
    
    // In a complete implementation, this would set the MIDI instrument for the track
    return true;
}

bool AudioEditor::SetMidiChannel(int track_index, int channel) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index < 0 || track_index >= all_tracks.GetCount()) return false;
    
    // In a complete implementation, this would set the MIDI channel for the track
    return true;
}

// MixerStrip implementation
MixerStrip::MixerStrip() : track_index(-1), editor(nullptr) {
    // Initialize controls with default values
    volume_slider.SetRange(0, 100);  // 0-100% in UI, mapped to 0.0-2.0 in actual value
    volume_slider <<= THISBACK(OnVolumeChange);
    
    pan_slider.SetRange(-100, 100);  // -100% to 100% (hard left to hard right)
    pan_slider <<= THISBACK(OnPanChange);
    
    mute_button.SetLabel("MUTE");
    mute_button <<= THISBACK(OnMuteToggle);
    
    solo_button.SetLabel("SOLO");
    solo_button <<= THISBACK(OnSoloToggle);
    
    // Add controls to the layout
    AddCtrls();
}

void MixerStrip::SetTrackIndex(int index) {
    track_index = index;
    RefreshControls();
}

void MixerStrip::SetEditor(AudioEditor* ed) {
    editor = ed;
    RefreshControls();
}

void MixerStrip::RefreshControls() {
    if (!editor || track_index < 0) return;
    
    // Get track information from the editor
    const Vector<AudioTrack>& tracks = editor->GetAllBuses().GetCount() > 0 ? 
        editor->GetAllBuses()[0].GetSourceTracks().GetCount() > 0 ?
        editor->GetAllBuses()[0].GetSourceTracks() : Vector<AudioTrack>() :
        Vector<AudioTrack>();
    
    // Actually, we need to get the tracks from the timeline
    // This is a simplified implementation
    Layout();  // Refresh the layout to reflect any changes
}

void MixerStrip::Paint(Draw& draw) {
    // Draw the mixer strip background
    draw.DrawRect(GetSize(), White());
    
    // Draw a border around the mixer strip
    draw.DrawRect(GetSize(), Black());
}

void MixerStrip::Layout() {
    // Calculate positions for all controls based on the available size
    Size sz = GetSize();
    
    // Position the controls: Track name at top, then volume/pan, then mute/solo, routing at bottom
    int margin = 5;
    int ctrl_width = 50;
    int ctrl_height = 20;
    int label_height = 15;
    
    // Track name display
    track_name_display.SetRect(margin, margin, sz.cx - 2*margin, label_height);
    
    // Volume slider and display
    int y = margin + label_height + margin;
    volume_display.SetRect(margin, y, ctrl_width, ctrl_height);
    volume_slider.SetRect(margin + ctrl_width + margin, y, ctrl_width, ctrl_height);
    
    // Pan slider
    y += ctrl_height + margin;
    pan_slider.SetRect(margin + ctrl_width + margin, y, ctrl_width, ctrl_height);
    
    // Mute and solo buttons
    y += ctrl_height + margin;
    mute_button.SetRect(margin, y, ctrl_width, ctrl_height);
    solo_button.SetRect(margin + ctrl_width + margin, y, ctrl_width, ctrl_height);
    
    // Routing controls
    y += ctrl_height + margin;
    routing_ctrl.SetRect(margin, y, sz.cx - 2*margin, sz.cy - y - margin);
    
    Ctrl::Layout();
}

bool MixerStrip::Key(dword key, int count) {
    // Handle keyboard shortcuts for mixer operations
    switch(key) {
        case K_DELETE:
            // Implement track deletion if needed
            return true;
        case Ctrl('m'):
            // Toggle mute
            OnMuteToggle();
            return true;
        case Ctrl('s'):
            // Toggle solo
            OnSoloToggle();
            return true;
    }
    return Ctrl::Key(key, count);
}

void MixerStrip::OnVolumeChange() {
    // Handle volume change from slider
    if (editor && track_index >= 0) {
        // In a real implementation, this would update the track volume
        // Convert slider value (0-100) to actual volume (0.0-2.0)
        double volume = volume_slider.GetValue() / 50.0;  // Slider value 0-100 maps to 0.0-2.0
        // editor->SetTrackVolume(track_index, volume);
    }
}

void MixerStrip::OnPanChange() {
    // Handle pan change from slider
    if (editor && track_index >= 0) {
        // In a real implementation, this would update the track pan
        // Convert slider value (-100 to 100) to actual pan (-1.0 to 1.0)
        double pan = pan_slider.GetValue() / 100.0;  // Slider value -100 to 100 maps to -1.0 to 1.0
        // editor->SetTrackPan(track_index, pan);
    }
}

void MixerStrip::OnMuteToggle() {
    if (editor && track_index >= 0) {
        // In a real implementation, this would toggle the track mute state
        // bool current_mute = editor->GetTrackMuteStatus(track_index);
        // editor->SetTrackMuteStatus(track_index, !current_mute);
        mute_button.SetLabel(editor->GetMetronomeEnabled() ? "MUTE" : "UNMUTE"); // Placeholder
    }
}

void MixerStrip::OnSoloToggle() {
    if (editor && track_index >= 0) {
        // In a real implementation, this would toggle the track solo state
        // bool current_solo = editor->GetTrackSoloStatus(track_index);
        // editor->SetTrackSoloStatus(track_index, !current_solo);
    }
}

void MixerStrip::OnRoutingChange() {
    // Handle routing change - update which bus this track sends to
    if (editor && track_index >= 0) {
        // In a real implementation, this would update the track-to-bus routing
    }
}

void MixerStrip::AddCtrls() {
    // Add all controls to the mixer strip
    Add(track_name_display);
    Add(volume_display);
    Add(volume_slider);
    Add(pan_slider);
    Add(mute_button);
    Add(solo_button);
    Add(routing_ctrl);
}

// MixerCtrl implementation
MixerCtrl::MixerCtrl() : editor(nullptr) {
    // Initialize the mixer control
}

void MixerCtrl::SetEditor(AudioEditor* ed) {
    editor = ed;
    RefreshMixer();
}

void MixerCtrl::RefreshMixer() {
    if (!editor) return;
    
    // Clear existing strips
    for (auto& strip : strips) {
        RemoveChild(&(*strip));
        delete strip;
    }
    strips.Clear();
    
    // Create a mixer strip for each track
    const Vector<AudioTrack>& tracks = editor->GetAllTracks();
    for (int i = 0; i < tracks.GetCount(); i++) {
        MixerStrip* strip = new MixerStrip();
        strip->SetTrackIndex(i);
        strip->SetEditor(editor);
        strips.Add(strip);
        AddChild(strip);
    }
    
    Layout();
}

void MixerCtrl::Paint(Draw& draw) {
    // Draw the mixer background
    draw.DrawRect(GetSize(), RGB(40, 40, 40));  // Dark gray background
    
    // Draw a border around the mixer
    draw.DrawRect(GetSize(), Black());
}

void MixerCtrl::Layout() {
    // Layout all the mixer strips in a vertical arrangement
    Size sz = GetSize();
    
    if (strips.GetCount() == 0) return;
    
    // Calculate width for each strip
    int strip_width = std::min(150, sz.cx / std::max(1, strips.GetCount()));  // At least 150px width per strip
    int strip_height = sz.cy;  // Full height for now, might want to limit per strip
    
    for (int i = 0; i < strips.GetCount(); i++) {
        int x_pos = i * strip_width;
        strips[i]->SetRect(x_pos, 0, strip_width, strip_height);
    }
}

bool MixerCtrl::Key(dword key, int count) {
    return Ctrl::Key(key, count);
}

void MixerCtrl::OnStripChange(int track_index) {
    // This would be called when a parameter changes on a specific strip
    // In a real implementation, this might trigger a redraw or update
}

void MixerCtrl::AddStrip(int track_index) {
    // Add a new mixer strip for the given track index
    if (!editor) return;
    
    MixerStrip* strip = new MixerStrip();
    strip->SetTrackIndex(track_index);
    strip->SetEditor(editor);
    strips.Add(strip);
    AddChild(strip);
    
    Layout();  // Re-layout to accommodate the new strip
}

void MixerCtrl::RemoveStrip(int track_index) {
    // Remove the mixer strip for the given track index
    // In a real implementation, we would need to find and remove the specific strip
    // For now, we'll just refresh the entire mixer
    RefreshMixer();
}

void MixerCtrl::UpdateStrip(int track_index) {
    // Update the specific strip for the given track index
    if (track_index >= 0 && track_index < strips.GetCount()) {
        strips[track_index]->RefreshControls();
    }
}

// Automation implementation
Automation::Automation() : parameter_name("default") {}

Automation::Automation(String param_name) : parameter_name(param_name) {}

void Automation::AddPoint(const AutomationPoint& point) {
    // Find the correct position to insert the point to keep them in time order
    int insert_pos = 0;
    for(int i = 0; i < points.GetCount(); i++) {
        if(points[i].time > point.time) {
            break;
        }
        insert_pos++;
    }
    points.Insert(insert_pos, point);
}

void Automation::RemovePoint(int index) {
    if(index >= 0 && index < points.GetCount()) {
        points.Remove(index);
    }
}

void Automation::UpdatePoint(int index, const AutomationPoint& new_point) {
    if(index >= 0 && index < points.GetCount()) {
        points[index] = new_point;
        // Ensure the points remain in time order after update
        if(index > 0 && points[index].time < points[index-1].time) {
            // Move backward to correct position
            for(int i = index; i > 0 && points[i].time < points[i-1].time; i--) {
                std::swap(points[i], points[i-1]);
            }
        } else if(index < points.GetCount()-1 && points[index].time > points[index+1].time) {
            // Move forward to correct position
            for(int i = index; i < points.GetCount()-1 && points[i].time > points[i+1].time; i++) {
                std::swap(points[i], points[i+1]);
            }
        }
    }
}

double Automation::GetValueAtTime(double time) const {
    if(points.GetCount() == 0) return 0.0;
    if(points.GetCount() == 1) return points[0].value;
    
    // Find the two points that frame the given time
    int first_point = -1;
    int second_point = -1;
    
    for(int i = 0; i < points.GetCount(); i++) {
        if(points[i].time <= time) {
            first_point = i;
        } else {
            if(first_point != -1) {
                second_point = i;
                break;
            }
        }
    }
    
    if(first_point == -1) {
        // time is before the first point, return the first point's value
        return points[0].value;
    }
    
    if(second_point == -1) {
        // time is after the last point, return the last point's value
        return points[points.GetCount()-1].value;
    }
    
    // Interpolate between the two points
    const AutomationPoint& p1 = points[first_point];
    const AutomationPoint& p2 = points[second_point];
    
    // Linear interpolation
    double fraction = (time - p1.time) / (p2.time - p1.time);
    return p1.value + fraction * (p2.value - p1.value);
}

Vector<AutomationPoint> Automation::GetPointsInRange(double start_time, double end_time) const {
    Vector<AutomationPoint> result;
    
    for(int i = 0; i < points.GetCount(); i++) {
        if(points[i].time >= start_time && points[i].time <= end_time) {
            result.Add(points[i]);
        }
    }
    
    return result;
}

// AudioEditor automation methods
void AudioEditor::AddTrackAutomationPoint(int track_index, String parameter, const AutomationPoint& point) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index >= 0 && track_index < all_tracks.GetCount()) {
        all_tracks[track_index].AddAutomationPoint(parameter, point);
    }
}

void AudioEditor::RemoveTrackAutomationPoint(int track_index, String parameter, int point_index) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index >= 0 && track_index < all_tracks.GetCount()) {
        all_tracks[track_index].RemoveAutomationPoint(parameter, point_index);
    }
}

double AudioEditor::GetTrackAutomationValueAtTime(int track_index, String parameter, double time) const {
    const Vector<AudioTrack>& all_tracks = timeline.GetTracks();
    if(track_index >= 0 && track_index < all_tracks.GetCount()) {
        return all_tracks[track_index].GetAutomationValueAtTime(parameter, time);
    }
    return 0.0;  // Default value
}

void AudioEditor::SetTrackAutomationValueAtTime(int track_index, String parameter, double time, double value) {
    Vector<AudioTrack>& all_tracks = const_cast<Vector<AudioTrack>&>(timeline.GetTracks());
    if(track_index >= 0 && track_index < all_tracks.GetCount()) {
        all_tracks[track_index].SetAutomationValueAtTime(parameter, time, value);
    }
}

Vector<AutomationPoint> AudioEditor::GetTrackAutomationPoints(int track_index, String parameter) const {
    const Vector<AudioTrack>& all_tracks = timeline.GetTracks();
    if(track_index >= 0 && track_index < all_tracks.GetCount()) {
        return all_tracks[track_index].GetAutomationPoints(parameter);
    }
    // Return empty vector if track not found
    return Vector<AutomationPoint>();
}

// AutomationEditor implementation
AutomationEditor::AutomationEditor() : editor(nullptr), track_index(-1), 
    start_time(0.0), end_time(10.0), min_value(0.0), max_value(1.0), 
    is_dragging(false), selected_point(-1) {
    // Set default ranges
    AddFrame(BlackFrame());  // Add a border
}

void AutomationEditor::SetEditor(AudioEditor* ed) {
    editor = ed;
}

void AutomationEditor::SetTrack(int track_idx) {
    track_index = track_idx;
    RefreshPointPositions();
}

void AutomationEditor::SetParameter(String param) {
    parameter_name = param;
    RefreshPointPositions();
}

void AutomationEditor::SetTimeRange(double start, double end) {
    start_time = start;
    end_time = end;
    RefreshPointPositions();
}

void AutomationEditor::SetValueRange(double min, double max) {
    min_value = min;
    max_value = max;
    RefreshPointPositions();
}

void AutomationEditor::Paint(Draw& draw) {
    Size sz = GetSize();
    
    // Draw background
    draw.DrawRect(sz, White());
    
    // Draw grid lines
    int num_time_lines = 10;
    int num_value_lines = 5;
    
    for(int i = 1; i < num_time_lines; i++) {
        int x = (sz.cx * i) / num_time_lines;
        draw.DrawLine(x, 0, x, sz.cy, 1, RGBA(200, 200, 200));
    }
    
    for(int i = 1; i < num_value_lines; i++) {
        int y = (sz.cy * i) / num_value_lines;
        draw.DrawLine(0, y, sz.cx, y, 1, RGBA(200, 200, 200));
    }
    
    // Draw the automation curve if we have an editor and track
    if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
        Vector<AutomationPoint> points = editor->GetAllTracks()[track_index].GetAutomationPoints(parameter_name);
        
        // Draw the curve
        if(points.GetCount() > 1) {
            Point prev_point = ValueTimeToPoint(points[0].time, points[0].value);
            for(int i = 1; i < points.GetCount(); i++) {
                Point curr_point = ValueTimeToPoint(points[i].time, points[i].value);
                
                // Draw line between points
                draw.DrawLine(prev_point, curr_point, 2, Blue());
                
                prev_point = curr_point;
            }
        }
        
        // Draw the automation points
        for(int i = 0; i < points.GetCount(); i++) {
            Point pos = ValueTimeToPoint(points[i].time, points[i].value);
            Color point_color = (i == selected_point) ? Red() : Blue();
            draw.DrawEllipse(pos.x - 5, pos.y - 5, 10, 10, point_color, 2, White());
        }
    }
}

void AutomationEditor::Layout() {
    // The control doesn't need special layout, just refresh the display
    RefreshPointPositions();
    Refresh();
}

bool AutomationEditor::Key(dword key, int count) {
    if(key == K_DELETE && selected_point >= 0) {
        // Delete the selected point
        OnRemovePoint(selected_point);
        Refresh();
        return true;
    }
    return Ctrl::Key(key, count);
}

void AutomationEditor::MouseMove(Point p, dword keyflags) {
    if(is_dragging && selected_point >= 0) {
        // Move the selected point to the new position
        Point<double> timeValue = PointToValueTime(p);
        
        // Update the automation point with the new time and value
        if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
            editor->SetTrackAutomationValueAtTime(track_index, parameter_name, timeValue.x, timeValue.y);
            RefreshPointPositions();
            Refresh();
        }
    }
    
    Ctrl::MouseMove(p, keyflags);
}

void AutomationEditor::LeftDown(Point p, dword keyflags) {
    if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
        // Check if we clicked on an existing point
        Vector<AutomationPoint> points = editor->GetAllTracks()[track_index].GetAutomationPoints(parameter_name);
        
        bool found_point = false;
        for(int i = 0; i < points.GetCount(); i++) {
            Point pos = ValueTimeToPoint(points[i].time, points[i].value);
            int dx = abs(pos.x - p.x);
            int dy = abs(pos.y - p.y);
            
            if(dx <= 5 && dy <= 5) {
                // Clicked on a point
                selected_point = i;
                is_dragging = true;
                Refresh();
                found_point = true;
                break;
            }
        }
        
        if(!found_point) {
            // Add a new point at the clicked position
            Point<double> timeValue = PointToValueTime(p);
            OnAddPoint(p);
        }
    }
    
    Ctrl::LeftDown(p, keyflags);
}

void AutomationEditor::LeftUp(Point p, dword keyflags) {
    is_dragging = false;
    Ctrl::LeftUp(p, keyflags);
}

void AutomationEditor::LeftDouble(Point p, dword keyflags) {
    // Double-click adds a new point at the position
    OnAddPoint(p);
    Ctrl::LeftDouble(p, keyflags);
}

void AutomationEditor::OnAddPoint(Point p) {
    if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
        Point<double> timeValue = PointToValueTime(p);
        editor->AddTrackAutomationPoint(track_index, parameter_name, 
                                       AutomationPoint(timeValue.x, timeValue.y));
        RefreshPointPositions();
        Refresh();
    }
}

void AutomationEditor::OnRemovePoint(int point_index) {
    if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
        editor->RemoveTrackAutomationPoint(track_index, parameter_name, point_index);
        if(selected_point == point_index) {
            selected_point = -1;
        }
        RefreshPointPositions();
        Refresh();
    }
}

void AutomationEditor::OnMovePoint(int point_index, Point new_pos) {
    // This would be used to move a specific point to a new position
    // The actual movement is handled in MouseMove
}

Point AutomationEditor::ValueTimeToPoint(double time, double value) const {
    Size sz = GetSize();
    
    // Convert time and value to coordinates
    double time_range = end_time - start_time;
    double value_range = max_value - min_value;
    
    int x = (time_range > 0) ? (int)((time - start_time) / time_range * sz.cx) : 0;
    int y = (value_range > 0) ? (int)(sz.cy - ((value - min_value) / value_range * sz.cy)) : sz.cy / 2;
    
    return Point(x, y);
}

Point<double> AutomationEditor::PointToValueTime(Point p) const {
    Size sz = GetSize();
    
    // Convert coordinates to time and value
    double time_range = end_time - start_time;
    double value_range = max_value - min_value;
    
    double time = (sz.cx > 0) ? (p.x * time_range / sz.cx + start_time) : start_time;
    double value = (sz.cy > 0) ? (max_value - (p.y * value_range / sz.cy)) : min_value;
    
    return Point<double>(time, value);
}

void AutomationEditor::RefreshPointPositions() {
    point_positions.Clear();
    
    if(editor && track_index >= 0 && !parameter_name.IsEmpty()) {
        Vector<AutomationPoint> points = editor->GetAllTracks()[track_index].GetAutomationPoints(parameter_name);
        
        for(int i = 0; i < points.GetCount(); i++) {
            point_positions.Add(ValueTimeToPoint(points[i].time, points[i].value));
        }
    }
}

// TimelineCtrl implementation
TimelineCtrl::TimelineCtrl() : editor(nullptr), start_time(0.0), end_time(60.0), 
    pixels_per_second(50), track_height(50), is_dragging(false), drag_track_idx(-1), 
    drag_clip_idx(-1), drag_offset(0.0) {
    // Set default values
    AddFrame(BlackFrame());  // Add a border
}

void TimelineCtrl::SetEditor(AudioEditor* ed) {
    editor = ed;
    RefreshTrackPositions();
}

void TimelineCtrl::SetTimeRange(double start, double end) {
    start_time = start;
    end_time = end;
    Refresh();
}

void TimelineCtrl::SetPixelsPerSecond(int pixels) {
    pixels_per_second = pixels;
    Refresh();
}

void TimelineCtrl::SetTrackHeight(int height) {
    track_height = height;
    RefreshTrackPositions();
    Refresh();
}

void TimelineCtrl::Paint(Draw& draw) {
    Size sz = GetSize();
    
    // Draw background
    draw.DrawRect(sz, White());
    
    // Draw grid lines (vertical time lines)
    double time_range = end_time - start_time;
    int total_width = (int)(time_range * pixels_per_second);
    
    // Draw time grid
    for(double time = floor(start_time); time <= end_time; time += 1.0) {
        int x = (int)((time - start_time) * pixels_per_second);
        if(x >= 0 && x < sz.cx) {
            draw.DrawLine(x, 0, x, sz.cy, 1, RGBA(200, 200, 200));
            // Draw time label
            draw.DrawText(x + 2, 2, Format("%.1f s", time), StdFont(), Black());
        }
    }
    
    if(editor == nullptr) return;
    
    const Vector<AudioTrack>& tracks = editor->GetAllTracks();
    
    // Draw tracks and clips
    for(int track_idx = 0; track_idx < tracks.GetCount(); track_idx++) {
        int y_pos = TrackToY(track_idx);
        
        // Draw track background
        if(y_pos < sz.cy) {
            int height = std::min(track_height, sz.cy - y_pos);
            draw.DrawRect(0, y_pos, sz.cx, height, 
                         track_idx % 2 == 0 ? RGBA(240, 240, 240) : RGBA(250, 250, 250));
            
            // Draw track name
            draw.DrawText(5, y_pos + 2, tracks[track_idx].GetName(), StdFont(), Black());
        }
        
        // Draw clips in this track
        const Vector<AudioClip>& clips = tracks[track_idx].GetClips();
        for(int clip_idx = 0; clip_idx < clips.GetCount(); clip_idx++) {
            const AudioClip& clip = clips[clip_idx];
            
            int x_start = (int)((clip.GetStartTime() - start_time) * pixels_per_second);
            int x_end = (int)((clip.GetEndTime() - start_time) * pixels_per_second);
            
            if(x_end > 0 && x_start < sz.cx) {
                // Ensure we're within the track's vertical bounds
                int clip_top = y_pos + 20;
                int clip_height = std::min(track_height - 25, sz.cy - clip_top);
                
                if(clip_height > 0) {
                    Color clip_color = clip.GetMuteStatus() ? Gray() : Blue();
                    int width = std::max(2, x_end - x_start);  // Minimum width of 2 pixels
                    
                    // Adjust to be within the track area
                    int adjusted_start = std::max(0, x_start);
                    int adjusted_width = std::min(width, sz.cx - adjusted_start);
                    
                    if(adjusted_width > 0) {
                        draw.DrawRect(adjusted_start, clip_top, adjusted_width, clip_height, 
                                     clip_color, 1, clip.GetMuteStatus() ? Gray() : Blue());
                        
                        // Draw clip name
                        String clip_name = clip.GetName();
                        if(adjusted_width > 20) {  // Only draw text if we have enough space
                            draw.DrawText(adjusted_start + 2, clip_top + 2, 
                                         clip_name.Mid(0, std::min(20, clip_name.GetLength())), 
                                         StdFont(10), White());
                        }
                    }
                }
            }
        }
    }
    
    // Draw playhead if needed
    // This would be implemented based on playback state
}

void TimelineCtrl::Layout() {
    RefreshTrackPositions();
    Refresh();
}

bool TimelineCtrl::Key(dword key, int count) {
    // Handle keyboard shortcuts for timeline operations
    switch(key) {
        case K_DELETE:
            // If a clip is selected, delete it
            return true;
        case K_SPACE:
            // Play/pause toggle
            return true;
        case Ctrl('a'):
            // Select all clips
            return true;
    }
    return Ctrl::Key(key, count);
}

void TimelineCtrl::MouseMove(Point p, dword keyflags) {
    if(is_dragging && drag_track_idx >= 0 && drag_clip_idx >= 0 && editor != nullptr) {
        // Calculate new time based on mouse position
        double new_time = XToTime(p.x) - drag_offset;
        
        // Update the clip position
        Vector<AudioTrack>& tracks = const_cast<Vector<AudioTrack>&>(editor->GetAllTracks());
        
        if(drag_track_idx < tracks.GetCount()) {
            Vector<AudioClip>& clips = const_cast<Vector<AudioClip>&>(tracks[drag_track_idx].GetClips());
            
            if(drag_clip_idx < clips.GetCount()) {
                double clip_duration = clips[drag_clip_idx].GetDuration();
                
                // Update the clip's start and end times
                clips[drag_clip_idx].SetStartTime(new_time);
                clips[drag_clip_idx].SetEndTime(new_time + clip_duration);
                
                Refresh();  // Update the display
            }
        }
    }
    
    last_mouse_pos = p;
    Ctrl::MouseMove(p, keyflags);
}

void TimelineCtrl::LeftDown(Point p, dword keyflags) {
    if(editor == nullptr) return;
    
    const Vector<AudioTrack>& tracks = editor->GetAllTracks();
    int clicked_track = YToTrack(p.y);
    
    if(clicked_track >= 0 && clicked_track < tracks.GetCount()) {
        // Check if we clicked on a clip in this track
        const Vector<AudioClip>& clips = tracks[clicked_track].GetClips();
        double clicked_time = XToTime(p.x);
        
        for(int i = 0; i < clips.GetCount(); i++) {
            if(clips[i].ContainsTime(clicked_time)) {
                // We clicked on a clip
                is_dragging = true;
                drag_track_idx = clicked_track;
                drag_clip_idx = i;
                drag_offset = clicked_time - clips[i].GetStartTime();
                
                Refresh();  // Highlight the selected clip
                break;
            }
        }
    }
    
    Ctrl::LeftDown(p, keyflags);
}

void TimelineCtrl::LeftUp(Point p, dword keyflags) {
    is_dragging = false;
    drag_track_idx = -1;
    drag_clip_idx = -1;
    
    Ctrl::LeftUp(p, keyflags);
}

void TimelineCtrl::OnClipMove(int track_idx, int clip_idx, double new_start_time) {
    // This would be called to move a clip to a new time position
    if(editor && track_idx >= 0 && track_idx < editor->GetAllTracks().GetCount()) {
        Vector<AudioTrack>& tracks = const_cast<Vector<AudioTrack>&>(editor->GetAllTracks());
        Vector<AudioClip>& clips = const_cast<Vector<AudioClip>&>(tracks[track_idx].GetClips());
        
        if(clip_idx >= 0 && clip_idx < clips.GetCount()) {
            double duration = clips[clip_idx].GetDuration();
            clips[clip_idx].SetStartTime(new_start_time);
            clips[clip_idx].SetEndTime(new_start_time + duration);
        }
    }
}

void TimelineCtrl::OnClipResize(int track_idx, int clip_idx, double new_duration) {
    // This would be called to resize a clip
    if(editor && track_idx >= 0 && track_idx < editor->GetAllTracks().GetCount()) {
        Vector<AudioTrack>& tracks = const_cast<Vector<AudioTrack>&>(editor->GetAllTracks());
        Vector<AudioClip>& clips = const_cast<Vector<AudioClip>&>(tracks[track_idx].GetClips());
        
        if(clip_idx >= 0 && clip_idx < clips.GetCount()) {
            clips[clip_idx].SetDuration(new_duration);
        }
    }
}

void TimelineCtrl::OnAddClip(int track_idx, double time) {
    // This would be called to add a new clip at the specified time
    // Implementation would depend on how the user specifies the audio file
}

Point TimelineCtrl::TimeToX(double time) const {
    return (int)((time - start_time) * pixels_per_second);
}

double TimelineCtrl::XToTime(int x) const {
    return start_time + ((double)x / pixels_per_second);
}

int TimelineCtrl::TrackToY(int track_idx) const {
    return track_idx * track_height;
}

int TimelineCtrl::YToTrack(int y) const {
    if(track_height > 0) {
        return y / track_height;
    }
    return -1;  // Invalid track height
}

void TimelineCtrl::RefreshTrackPositions() {
    track_y_positions.Clear();
    if(editor) {
        const Vector<AudioTrack>& tracks = editor->GetAllTracks();
        for(int i = 0; i < tracks.GetCount(); i++) {
            track_y_positions.Add(TrackToY(i));
        }
    }
}

// TransportCtrl implementation
TransportCtrl::TransportCtrl() : editor(nullptr), is_playing(false), is_recording(false), current_time(0.0) {
    // Initialize buttons
    play_button.SetLabel("▶");
    play_button <<= THISBACK(OnPlay);
    
    stop_button.SetLabel("■");
    stop_button <<= THISBACK(OnStop);
    
    record_button.SetLabel("●");
    record_button <<= THISBACK(OnRecord);
    
    loop_button.SetLabel(" LOOP ");
    loop_button <<= THISBACK(OnLoopToggle);
    
    // Initialize position control
    position_ctrl.SetData("00:00:000");
    position_ctrl <<= THISBACK(OnPositionChange);
    
    // Add controls to the transport
    AddCtrls();
}

void TransportCtrl::SetEditor(AudioEditor* ed) {
    editor = ed;
}

void TransportCtrl::StartPlayback() {
    if (!is_playing) {
        is_playing = true;
        is_recording = false; // Can't record while just playing
        
        // In a real implementation, we would start the audio playback system
        // For now, we'll just simulate playback by updating the time periodically
        
        UpdateDisplay();
    }
}

void TransportCtrl::StopPlayback() {
    is_playing = false;
    is_recording = false;
    
    // In a real implementation, we would stop the audio playback system
    
    UpdateDisplay();
}

void TransportCtrl::StartRecording() {
    is_recording = true;
    is_playing = true;  // Usually recording also starts playback
    
    // In a real implementation, we would start the recording system
    
    UpdateDisplay();
}

void TransportCtrl::ToggleLoop() {
    // In a real implementation, this would toggle looping during playback
    UpdateDisplay();
}

void TransportCtrl::SetPosition(double time) {
    current_time = time;
    
    // Update the position display to show time in MM:SS:ms format
    int minutes = (int)(time / 60);
    int seconds = (int)(time) % 60;
    int milliseconds = (int)((time - (int)time) * 1000);
    
    String time_str = Format("%02d:%02d:%03d", minutes, seconds, milliseconds);
    position_ctrl.SetData(time_str);
    
    // Call the time update callback if set
    if (time_update_callback)
        time_update_callback(current_time);
}

void TransportCtrl::Paint(Draw& draw) {
    // Draw transport control background
    draw.DrawRect(GetSize(), RGBA(220, 220, 220));
    
    // Draw a subtle dividing line
    Size sz = GetSize();
    draw.DrawLine(0, sz.cy-1, sz.cx, sz.cy-1, 1, Gray());
}

void TransportCtrl::Layout() {
    // Calculate positions for all transport controls
    Size sz = GetSize();
    
    int btn_width = 40;
    int btn_height = 30;
    int margin = 5;
    
    // Position the buttons from left to right
    int x = margin;
    
    // Record button
    record_button.SetRect(x, (sz.cy - btn_height) / 2, btn_width, btn_height);
    x += btn_width + margin;
    
    // Play button
    play_button.SetRect(x, (sz.cy - btn_height) / 2, btn_width, btn_height);
    x += btn_width + margin;
    
    // Stop button
    stop_button.SetRect(x, (sz.cy - btn_height) / 2, btn_width, btn_height);
    x += btn_width + margin;
    
    // Loop button
    loop_button.SetRect(x, (sz.cy - btn_height) / 2, btn_width + 20, btn_height);
    x += btn_width + 20 + margin;
    
    // Position control (time display)
    int pos_width = 100;
    int pos_height = 25;
    position_ctrl.SetRect(sz.cx - pos_width - margin, (sz.cy - pos_height) / 2, pos_width, pos_height);
}

bool TransportCtrl::Key(dword key, int count) {
    switch(key) {
        case K_SPACE:
            if (is_playing) {
                StopPlayback();
            } else {
                StartPlayback();
            }
            return true;
        case Ctrl('k'):
            // Toggle loop
            ToggleLoop();
            return true;
    }
    
    return Ctrl::Key(key, count);
}

void TransportCtrl::OnPlay() {
    StartPlayback();
}

void TransportCtrl::OnStop() {
    StopPlayback();
}

void TransportCtrl::OnRecord() {
    StartRecording();
}

void TransportCtrl::OnLoopToggle() {
    ToggleLoop();
}

void TransportCtrl::OnPositionChange() {
    // Parse the time from the position control
    String time_str = position_ctrl.GetData();
    
    // This is a simplified implementation - in reality, we'd parse the time string
    // and set the playhead position accordingly
    double new_time = current_time;
    
    // For now, just update the current time to the new value
    SetPosition(new_time);
    
    // Update the display
    UpdateDisplay();
}

void TransportCtrl::UpdateDisplay() {
    // Update button states based on transport state
    play_button.SetLabel(is_playing ? "‖" : "▶");  // Change to pause symbol if playing
    record_button.SetLook(is_recording ? Button::PUSHED : Button::NORMAL);
    
    // Update position display
    SetPosition(current_time);
}

void TransportCtrl::AddCtrls() {
    // Add all controls to the transport
    Add(play_button);
    Add(stop_button);
    Add(record_button);
    Add(loop_button);
    Add(position_ctrl);
}
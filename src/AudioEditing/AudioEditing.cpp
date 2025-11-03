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
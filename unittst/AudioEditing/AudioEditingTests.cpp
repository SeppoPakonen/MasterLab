#include <Core/Core.h>
#include <AudioEditing/AudioEditing.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test AudioClip functionality
    {
        AudioClip clip("TestClip", "test.wav", 0.0, 5.0);
        
        // Test getters
        assert(clip.GetName() == "TestClip");
        assert(clip.GetStartTime() == 0.0);
        assert(clip.GetEndTime() == 5.0);
        assert(clip.GetDuration() == 5.0);
        assert(clip.GetFilePath() == "test.wav");
        
        // Test setters
        clip.SetName("NewName");
        assert(clip.GetName() == "NewName");
        
        clip.SetStartTime(1.0);
        clip.SetEndTime(6.0);
        assert(clip.GetDuration() == 5.0); // Duration should still be 5.0
        
        // Test ContainsTime
        assert(clip.ContainsTime(3.0) == true);
        assert(clip.ContainsTime(7.0) == false);
        
        // Test AddMarker/RemoveMarker
        ClipMarker marker(2.5, "MidPoint", Red());
        clip.AddMarker(marker);
        auto markers = clip.GetMarkers();
        assert(markers.GetCount() == 1);
        assert(markers[0].time == 2.5);
        
        cout << "AudioClip tests passed!" << endl;
    }
    
    // Test AudioTrack functionality
    {
        AudioTrack track("Test Track");
        
        // Add clips to track
        AudioClip clip1("Clip1", "file1.wav", 0.0, 3.0);
        AudioClip clip2("Clip2", "file2.wav", 5.0, 8.0);
        
        track.AddClip(clip1);
        track.AddClip(clip2);
        
        auto clips = track.GetClips();
        assert(clips.GetCount() == 2);
        assert(clips[0].GetName() == "Clip1");
        assert(clips[1].GetName() == "Clip2");
        
        // Test FindClipAtTime
        int clipAt2 = track.FindClipAtTime(2.0);  // Should be 0 (clip1)
        assert(clipAt2 == 0);
        
        int clipAt6 = track.FindClipAtTime(6.0);  // Should be 1 (clip2)
        assert(clipAt6 == 1);
        
        // Test FindClipAtTime in gap
        int clipAt4 = track.FindClipAtTime(4.0);  // Should be -1 (no clip)
        assert(clipAt4 == -1);
        
        cout << "AudioTrack tests passed!" << endl;
    }
    
    // Test Timeline functionality
    {
        Timeline timeline;
        
        // Add tracks to timeline
        AudioTrack track1("Track1");
        AudioTrack track2("Track2");
        
        AudioClip clip1("TimelineClip1", "file1.wav", 0.0, 3.0);
        track1.AddClip(clip1);
        
        timeline.AddTrack(track1);
        timeline.AddTrack(track2);
        
        auto tracks = timeline.GetTracks();
        assert(tracks.GetCount() == 2);
        assert(tracks[0].GetName() == "Track1");
        assert(tracks[1].GetName() == "Track2");
        
        // Test time signature and tempo
        timeline.SetTimeSignature(3, 4);  // 3/4 time
        assert(timeline.GetTimeSignatureNumerator() == 3);
        assert(timeline.GetTimeSignatureDenominator() == 4);
        
        timeline.SetTempo(140.0);  // 140 BPM
        assert(timeline.GetTempo() == 140.0);
        
        // Test beat calculations
        assert(abs(timeline.GetBeatDuration() - (60.0/140.0)) < 0.0001);
        
        cout << "Timeline tests passed!" << endl;
    }
    
    // Test AudioEditor functionality
    {
        AudioEditor editor;
        
        // Set timeline properties
        editor.SetTempo(120.0);
        editor.SetTimeSignature(4, 4);
        editor.SetMetronomeEnabled(true);
        
        assert(editor.GetMetronomeEnabled() == true);
        assert(editor.GetAllBeatPositions().GetCount() > 0);
        
        // Add marker
        editor.AddMarker(2.0, "Test Marker", Red());
        auto markers = editor.GetAllMarkers();
        assert(markers.GetCount() == 1);
        assert(markers[0].time == 2.0);
        assert(markers[0].label == "Test Marker");
        
        cout << "AudioEditor tests passed!" << endl;
    }
    
    // Test AudioBus functionality
    {
        AudioBus bus("MainOut", 2);  // Stereo bus
        
        // Test basic properties
        assert(bus.GetName() == "MainOut");
        assert(bus.GetChannelCount() == 2);
        assert(bus.GetVolume() == 1.0);
        
        // Test source track assignment
        bus.AddSourceTrack(0);
        bus.AddSourceTrack(1);
        
        auto sources = bus.GetSourceTracks();
        assert(sources.GetCount() == 2);
        assert(sources[0] == 0);
        assert(sources[1] == 1);
        
        // Test removing a source track
        bus.RemoveSourceTrack(0);
        sources = bus.GetSourceTracks();
        assert(sources.GetCount() == 1);
        assert(sources[0] == 1);
        
        cout << "AudioBus tests passed!" << endl;
    }
    
    // Test MIDI functionality
    {
        // Test MidiEvent
        MidiEvent noteOn(0x90, 0, 60, 100, 1.0);  // Note On, channel 0, note 60, vel 100, at 1.0s
        assert(noteOn.type == 0x90);
        assert(noteOn.channel == 0);
        assert(noteOn.note == 60);
        assert(noteOn.velocity == 100);
        assert(noteOn.time == 1.0);
        
        // Test MidiClip
        MidiClip midiClip("Test Midi Clip", 0.0, 4.0);
        assert(midiClip.GetName() == "Test Midi Clip");
        
        // Add a few MIDI events
        midiClip.AddEvent(noteOn);
        midiClip.AddEvent(MidiEvent(0x80, 0, 60, 0, 1.5));  // Note Off
        assert(midiClip.GetEvents().GetCount() == 2);
        
        // Test MidiTrack
        MidiTrack midiTrack("MIDI Track 1");
        assert(midiTrack.GetName() == "MIDI Track 1");
        assert(midiTrack.GetMidiChannel() == 0);
        
        midiTrack.SetInstrumentName("Grand Piano");
        midiTrack.SetMidiChannel(1);
        assert(midiTrack.GetInstrumentName() == "Grand Piano");
        assert(midiTrack.GetMidiChannel() == 1);
        
        // Add the MIDI clip to the track
        midiTrack.AddMidiClip(midiClip);
        assert(midiTrack.GetMidiClips().GetCount() == 1);
        
        cout << "MIDI tests passed!" << endl;
    }
    
    // Test Mixer functionality
    {
        AudioEditor editor;
        
        // Add a track
        AudioTrack track("Test Track");
        // In a real implementation, we would use the editor to add a track
        // For testing purposes, we'll just create a MixerStrip and MixerCtrl
        
        // Test mixer controls (creation logic)
        MixerStrip strip;
        strip.SetTrackIndex(0);
        assert(strip.IsOpen());
        
        // Test mixer control
        MixerCtrl mixer;
        mixer.SetEditor(&editor);
        assert(mixer.IsOpen());
        
        cout << "Mixer tests passed!" << endl;
    }
    
    // Test Automation functionality
    {
        // Test AutomationPoint
        AutomationPoint point(1.0, 0.5, 0);  // At 1.0s, value 0.5, linear shape
        assert(point.time == 1.0);
        assert(point.value == 0.5);
        assert(point.shape == 0);
        
        // Test Automation
        Automation volAutomation("volume");
        volAutomation.AddPoint(AutomationPoint(0.0, 0.0));  // Start silent
        volAutomation.AddPoint(AutomationPoint(2.0, 1.0));  // Fade in to full by 2s
        
        assert(volAutomation.GetPoints().GetCount() == 2);
        assert(volAutomation.GetParameterName() == "volume");
        
        // Test value interpolation
        assert(abs(volAutomation.GetValueAtTime(1.0) - 0.5) < 0.001);  // Should be halfway between 0 and 1
        assert(abs(volAutomation.GetValueAtTime(0.5) - 0.25) < 0.001); // Should be 1/4 of the way
        
        // Test AudioTrack automation
        AudioTrack track("Test Track with Automation");
        track.AddAutomationPoint("volume", AutomationPoint(0.0, 0.0));
        track.AddAutomationPoint("volume", AutomationPoint(4.0, 1.0));
        
        double valueAt2Sec = track.GetAutomationValueAtTime("volume", 2.0);
        assert(abs(valueAt2Sec - 0.5) < 0.001);  // Should be halfway between 0 and 1
        
        cout << "Automation tests passed!" << endl;
    }
    
    // Test TimelineCtrl functionality
    {
        AudioEditor editor;
        
        // Add a track with a clip to the editor's timeline
        AudioTrack track("Test Track");
        AudioClip clip("Test Clip", "test.wav", 1.0, 3.0);
        track.AddClip(clip);
        
        Timeline& timeline = editor.GetTimelineForUpdate();
        timeline.AddTrack(track);
        
        // Test timeline control creation
        TimelineCtrl timelineCtrl;
        timelineCtrl.SetEditor(&editor);
        assert(timelineCtrl.IsOpen());
        
        // Test time/position conversion
        timelineCtrl.SetTimeRange(0.0, 10.0);
        timelineCtrl.SetPixelsPerSecond(100);
        
        Point pos = timelineCtrl.TimeToX(5.0);
        double time = timelineCtrl.XToTime(pos.x);
        
        // Allow for small floating point precision differences
        assert(abs(time - 5.0) < 0.01);
        
        cout << "TimelineCtrl tests passed!" << endl;
    }
        
        // Test timeline control creation
        TimelineCtrl timelineCtrl;
        timelineCtrl.SetEditor(&editor);
        assert(timelineCtrl.IsOpen());
        
        // Test time/position conversion
        timelineCtrl.SetTimeRange(0.0, 10.0);
        timelineCtrl.SetPixelsPerSecond(100);
        
        Point pos = timelineCtrl.TimeToX(5.0);
        double time = timelineCtrl.XToTime(pos.x);
        
        // Allow for small floating point precision differences
        assert(abs(time - 5.0) < 0.01);
        
        cout << "TimelineCtrl tests passed!" << endl;
    }
    
    // Test TransportCtrl functionality
    {
        AudioEditor editor;
        
        // Test transport control creation
        TransportCtrl transport;
        transport.SetEditor(&editor);
        assert(transport.IsOpen());
        
        // Test basic transport operations
        transport.StartPlayback();
        assert(transport.GetPosition() == 0.0);
        
        transport.SetPosition(5.5);
        assert(transport.GetPosition() == 5.5);
        
        // Test stop functionality
        transport.StopPlayback();
        assert(!transport.GetPosition() == 0.0); // Position remains same, but state changes
        
        cout << "TransportCtrl tests passed!" << endl;
    }
    
    // Test MixerRack functionality
    {
        AudioEditor editor;
        
        // Add tracks to the editor
        AudioTrack track1("Track 1");
        AudioTrack track2("Track 2");
        Timeline& timeline = editor.GetTimelineForUpdate();
        timeline.AddTrack(track1);
        timeline.AddTrack(track2);
        
        // Test mixer rack creation
        MixerRack mixerRack;
        mixerRack.SetEditor(&editor);
        assert(mixerRack.IsOpen());
        
        // Check that the rack has the right number of strips
        // This would require access to the internal strips, which we don't expose
        // So we'll just verify the control can be created and laid out
        
        mixerRack.RefreshRack();
        mixerRack.Layout();
        
        cout << "MixerRack tests passed!" << endl;
    }
    
    // Test AudioProject functionality
    {
        // Test project creation
        AudioProject project("Test Project", "/path/to/test.mlp");
        assert(project.GetName() == "Test Project");
        assert(project.GetPath() == "/path/to/test.mlp");
        
        // Test timeline access
        Timeline& timeline = project.GetTimelineForUpdate();
        assert(timeline.GetTracks().GetCount() == 0);
        
        // Add a track to the project
        AudioTrack track("Track 1");
        timeline.AddTrack(track);
        assert(project.GetTimeline().GetTracks().GetCount() == 1);
        
        cout << "AudioProject tests passed!" << endl;
    }
    
    cout << "All tests passed!" << endl;
}
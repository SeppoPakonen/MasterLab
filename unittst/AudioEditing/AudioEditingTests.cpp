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
    
    cout << "All tests passed!" << endl;
}
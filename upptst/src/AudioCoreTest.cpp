#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test AudioCore functionality
    {
        LOG("Testing AudioCore functionality...");
        
        // Test basic audio buffer operations
        AudioBuffer buffer(2, 48000); // 2 channels, 1 second at 48kHz
        assert(buffer.GetChannelCount() == 2);
        assert(buffer.GetSampleCount() == 48000);
        
        // Fill buffer with test signal
        for (int ch = 0; ch < 2; ch++) {
            for (int i = 0; i < 100; i++) {
                buffer[ch][i] = sin(i * 2 * M_PI * 440.0 / 48000.0); // 440Hz sine wave
            }
        }
        
        // Check that we can read back the values
        assert(abs(buffer[0][10] - sin(10 * 2 * M_PI * 440.0 / 48000.0)) < 0.001);
        
        LOG("Audio buffer test passed");
    }

    // Test Track functionality
    {
        LOG("Testing Track functionality...");
        
        Track track;
        track.SetName("Test Track");
        track.SetChannelCount(2); // Stereo
        
        assert(track.GetName() == "Test Track");
        assert(track.GetChannelCount() == 2);
        assert(track.IsEnabled() == true);
        
        // Test volume and pan
        track.SetVolume(0.8);
        track.SetPan(-0.3); // Slightly to the left
        
        assert(abs(track.GetVolume() - 0.8) < 0.001);
        assert(abs(track.GetPan() - (-0.3)) < 0.001);
        
        LOG("Track test passed");
    }

    // Test Mixer functionality
    {
        LOG("Testing Mixer functionality...");
        
        Mixer mixer;
        assert(mixer.GetTrackCount() == 0);
        
        // Add a track to mixer
        Track track;
        track.SetName("Mixer Track");
        int trackId = mixer.AddTrack(pick(track));
        
        assert(mixer.GetTrackCount() == 1);
        assert(mixer.GetTrack(trackId).GetName() == "Mixer Track");
        
        LOG("Mixer test passed");
    }

    LOG("All AudioCore tests passed!");
}
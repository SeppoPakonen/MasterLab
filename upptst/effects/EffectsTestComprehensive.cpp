#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <AudioFX/AudioFX.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Reverb functionality
    {
        LOG("Testing Reverb functionality...");
        
        ReverbEffect reverb;
        reverb.SetName("Test Reverb");
        
        // Test reverb parameters
        reverb.SetDecayTime(2.5);
        assert(abs(reverb.GetDecayTime() - 2.5) < 0.001);
        
        reverb.SetEarlyReflections(0.3);
        assert(abs(reverb.GetEarlyReflections() - 0.3) < 0.001);
        
        reverb.SetDiffusion(0.8);
        assert(abs(reverb.GetDiffusion() - 0.8) < 0.001);
        
        reverb.SetPreDelay(0.04);
        assert(abs(reverb.GetPreDelay() - 0.04) < 0.001);
        
        reverb.SetWetDryMix(0.7);
        assert(abs(reverb.GetWetDryMix() - 0.7) < 0.001);
        
        LOG("Reverb test passed");
    }

    // Test Delay functionality
    {
        LOG("Testing Delay functionality...");
        
        DelayEffect delay;
        delay.SetName("Test Delay");
        
        // Test delay parameters
        delay.SetTime(0.5); // 500ms
        assert(abs(delay.GetTime() - 0.5) < 0.001);
        
        delay.SetFeedback(0.4);
        assert(abs(delay.GetFeedback() - 0.4) < 0.001);
        
        delay.SetMix(0.6);
        assert(abs(delay.GetMix() - 0.6) < 0.001);
        
        delay.SetTempoSync(true);
        assert(delay.GetTempoSync() == true);
        
        // Simulate processing an audio buffer
        AudioBuffer input(2, 1024); // stereo, 1024 samples
        AudioBuffer output(2, 1024);
        
        // Fill with test signal
        for (int ch = 0; ch < 2; ch++) {
            for (int i = 0; i < 1024; i++) {
                input[ch][i] = sin(i * 2 * M_PI * 440.0 / 48000.0);
            }
        }
        
        // Process through delay
        delay.Process(input, output, 48000); // at 48kHz
        
        // Output should be different from input due to delay processing
        assert(output[0][500] != input[0][500]);
        
        LOG("Delay test passed");
    }

    // Test Dynamics (Compressor) functionality
    {
        LOG("Testing Dynamics functionality...");
        
        CompressorEffect comp;
        comp.SetName("Test Compressor");
        
        // Test compressor parameters
        comp.SetThreshold(-12.0); // -12 dB
        assert(abs(comp.GetThreshold() - (-12.0)) < 0.001);
        
        comp.SetRatio(4.0); // 4:1 ratio
        assert(abs(comp.GetRatio() - 4.0) < 0.001);
        
        comp.SetAttack(0.005); // 5ms
        assert(abs(comp.GetAttack() - 0.005) < 0.001);
        
        comp.SetRelease(0.150); // 150ms
        assert(abs(comp.GetRelease() - 0.150) < 0.001);
        
        comp.SetMakeupGain(2.0); // 2dB
        assert(abs(comp.GetMakeupGain() - 2.0) < 0.001);
        
        LOG("Dynamics test passed");
    }

    // Test EQ functionality
    {
        LOG("Testing EQ functionality...");
        
        EQEffect eq;
        eq.SetName("Test EQ");
        
        // Create bands
        EQBand lowShelf(EQBandType::LOW_SHELF, 80.0, 1.0, 3.0);  // Low shelf at 80Hz, Q=1.0, +3dB
        EQBand peak1(EQBandType::PEAK, 500.0, 0.7, -2.0);        // Peak at 500Hz, Q=0.7, -2dB
        EQBand highShelf(EQBandType::HIGH_SHELF, 8000.0, 1.0, 2.0); // High shelf at 8kHz, +2dB
        
        eq.AddBand(lowShelf);
        eq.AddBand(peak1);
        eq.AddBand(highShelf);
        
        assert(eq.GetBandCount() == 3);
        assert(eq.GetBand(0).GetFrequency() == 80.0);
        assert(abs(eq.GetBand(1).GetGain() - (-2.0)) < 0.001);
        
        LOG("EQ test passed");
    }

    LOG("All Effects tests passed!");
}
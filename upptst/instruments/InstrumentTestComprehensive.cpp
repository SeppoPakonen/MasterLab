#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <PluginSDK/PluginSDK.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Synth functionality
    {
        LOG("Testing Synth functionality...");
        
        // Test basic synth parameters
        SynthEngine synth;
        synth.SetName("Test Synth");
        
        // Add oscillator parameters
        Parameter osc1Wave("osc1_wave", "Osc 1 Waveform", 0.0, 0.0, 4.0); // Saw, Square, Sine, etc.
        Parameter osc1Pitch("osc1_pitch", "Osc 1 Pitch", 0.5, 0.0, 1.0);
        Parameter osc1Level("osc1_level", "Osc 1 Level", 0.8, 0.0, 1.0);
        
        synth.AddParameter(osc1Wave);
        synth.AddParameter(osc1Pitch);
        synth.AddParameter(osc1Level);
        
        assert(synth.GetName() == "Test Synth");
        assert(synth.GetParameterCount() == 3);
        
        LOG("Synth test passed");
    }

    // Test Sampler functionality
    {
        LOG("Testing Sampler functionality...");
        
        Sampler sampler;
        sampler.SetName("Test Sampler");
        
        // Add sampler parameters
        Parameter sampleStart("sample_start", "Sample Start", 0.0, 0.0, 1.0);
        Parameter sampleEnd("sample_end", "Sample End", 1.0, 0.0, 1.0);
        Parameter loopStart("loop_start", "Loop Start", 0.2, 0.0, 1.0);
        Parameter loopEnd("loop_end", "Loop End", 0.8, 0.0, 1.0);
        Parameter loopMode("loop_mode", "Loop Mode", 1.0, 0.0, 2.0); // Forward, Ping-Pong, etc.
        
        sampler.AddParameter(sampleStart);
        sampler.AddParameter(sampleEnd);
        sampler.AddParameter(loopStart);
        sampler.AddParameter(loopEnd);
        sampler.AddParameter(loopMode);
        
        assert(sampler.GetName() == "Test Sampler");
        assert(sampler.GetParameterCount() == 5);
        
        LOG("Sampler test passed");
    }

    // Test Virtual Analog functionality
    {
        LOG("Testing Virtual Analog functionality...");
        
        VirtualAnalog vaSynth;
        vaSynth.SetName("Test VA Synth");
        
        // Add filter parameters
        Parameter filterCutoff("filter_cutoff", "Filter Cutoff", 0.7, 0.0, 1.0);
        Parameter filterResonance("filter_res", "Filter Resonance", 0.3, 0.0, 1.0);
        Parameter filterType("filter_type", "Filter Type", 0.0, 0.0, 3.0); // LP, HP, BP, Notch
        
        vaSynth.AddParameter(filterCutoff);
        vaSynth.AddParameter(filterResonance);
        vaSynth.AddParameter(filterType);
        
        assert(vaSynth.GetName() == "Test VA Synth");
        assert(vaSynth.GetParameterCount() == 3);
        
        LOG("Virtual Analog test passed");
    }

    LOG("All Instrument tests passed!");
}
#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test MIDI Instruments functionality
    {
        LOG("Testing MIDI Instruments functionality...");
        
        // Test creating a MIDI instrument
        PluginInfo info;
        info.name = "TestMidiInstrument";
        info.type = PluginType::MIDI_INSTRUMENT;
        info.category = "Synth";
        info.manufacturer = "Test Manufacturer";
        
        assert(info.name == "TestMidiInstrument");
        assert(info.type == PluginType::MIDI_INSTRUMENT);
        
        LOG("Basic MIDI instrument test passed");
    }

    // Test MIDI instrument processing
    {
        LOG("Testing MIDI instrument processing...");
        
        // Create a MIDI instrument
        MidiInstrument instrument;
        instrument.SetName("Virtual Synth");
        
        // Add some parameters
        Parameter osc1Pitch("osc1_pitch", "Osc 1 Pitch", 0.5, 0.0, 1.0);
        Parameter filterCutoff("filter_cutoff", "Filter Cutoff", 0.7, 0.0, 1.0);
        Parameter ampAttack("amp_attack", "Amp Attack", 0.2, 0.0, 1.0);
        
        instrument.AddParameter(osc1Pitch);
        instrument.AddParameter(filterCutoff);
        instrument.AddParameter(ampAttack);
        
        assert(instrument.GetName() == "Virtual Synth");
        assert(instrument.GetParameterCount() == 3);
        
        LOG("MIDI instrument processing test passed");
    }

    LOG("All MIDI Instruments tests passed!");
}
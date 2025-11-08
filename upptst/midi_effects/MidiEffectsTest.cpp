#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test MIDI Effects functionality
    {
        LOG("Testing MIDI Effects functionality...");
        
        // Test creating a MIDI effect
        PluginInfo info;
        info.name = "TestMidiEffect";
        info.type = PluginType::MIDI_EFFECT;
        info.category = "Chord";
        info.manufacturer = "Test Manufacturer";
        
        assert(info.name == "TestMidiEffect");
        assert(info.type == PluginType::MIDI_EFFECT);
        
        LOG("Basic MIDI effect test passed");
    }

    // Test MIDI event processing
    {
        LOG("Testing MIDI event processing...");
        
        // Create a simple MIDI event
        MidiEvent event(0x90, 0, 60, 100, 0.0); // Note On, channel 0, note 60, velocity 100, at time 0.0
        
        assert(event.GetType() == 0x90);
        assert(event.GetChannel() == 0);
        assert(event.GetNote() == 60);
        assert(event.GetVelocity() == 100);
        
        LOG("MIDI event processing test passed");
    }

    LOG("All MIDI Effects tests passed!");
}
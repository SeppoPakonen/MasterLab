#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test MIDI Inserts functionality
    {
        LOG("Testing MIDI Inserts functionality...");
        
        // Test creating a MIDI insert
        PluginInfo info;
        info.name = "TestMidiInsert";
        info.type = PluginType::MIDI_INSERT;
        info.category = "Filter";
        info.manufacturer = "Test Manufacturer";
        
        assert(info.name == "TestMidiInsert");
        assert(info.type == PluginType::MIDI_INSERT);
        
        LOG("Basic MIDI insert test passed");
    }

    // Test MIDI insert processing
    {
        LOG("Testing MIDI insert processing...");
        
        // Create a MIDI insert effect
        MidiInsertEffect insertEffect;
        insertEffect.SetName("Delay Insert");
        
        // Add some parameters
        Parameter delayTime("delay_time", "Delay Time", 0.5, 0.0, 2.0);
        Parameter feedback("feedback", "Feedback", 0.3, 0.0, 1.0);
        
        insertEffect.AddParameter(delayTime);
        insertEffect.AddParameter(feedback);
        
        assert(insertEffect.GetName() == "Delay Insert");
        assert(insertEffect.GetParameterCount() == 2);
        
        LOG("MIDI insert processing test passed");
    }

    LOG("All MIDI Inserts tests passed!");
}
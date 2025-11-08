#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Arpeggiator functionality
    {
        LOG("Testing Arpeggiator functionality...");
        
        Arpeggiator arp;
        arp.SetName("Test Arpeggiator");
        
        // Test pattern types
        arp.SetPattern(ArpeggiatorPattern::UP);
        assert(arp.GetPattern() == ArpeggiatorPattern::UP);
        
        arp.SetOctaveCount(2);
        assert(arp.GetOctaveCount() == 2);
        
        arp.SetGateLength(0.8);
        assert(abs(arp.GetGateLength() - 0.8) < 0.001);
        
        arp.SetTempoSync(true);
        assert(arp.GetTempoSync() == true);
        
        // Test adding notes to arpeggiate
        arp.AddNote(60); // C note
        arp.AddNote(64); // E note
        arp.AddNote(67); // G note
        
        assert(arp.GetNoteCount() == 3);
        
        LOG("Arpeggiator test passed");
    }

    // Test Quantizer functionality
    {
        LOG("Testing Quantizer functionality...");
        
        Quantizer quantizer;
        quantizer.SetName("Test Quantizer");
        
        // Test quantization settings
        quantizer.SetDivision(QuantizeDivision::EIGHTH); // 8th notes
        assert(quantizer.GetDivision() == QuantizeDivision::EIGHTH);
        
        quantizer.SetStrength(0.9); // 90% quantization strength
        assert(abs(quantizer.GetStrength() - 0.9) < 0.001);
        
        quantizer.SetRetrigger(true);
        assert(quantizer.GetRetrigger() == true);
        
        // Test quantizing a MIDI event
        MidiEvent event(0x90, 0, 60, 100, 1.234); // Note On at 1.234 seconds
        double quantizedTime = quantizer.QuantizeTime(event.GetTime(), 120.0); // At 120 BPM
        
        // The quantized time should be different from the original
        assert(quantizedTime != 1.234);
        
        LOG("Quantizer test passed");
    }

    // Test MidiController functionality
    {
        LOG("Testing MidiController functionality...");
        
        MidiController controller;
        controller.SetName("Test Controller");
        
        // Test controller mapping
        ControllerMapping map1(1, "Mod Wheel", 0, 127); // CC 1, 0-127 range
        ControllerMapping map2(7, "Volume", 0, 127);    // CC 7, 0-127 range
        ControllerMapping map3(11, "Expression", 0, 127); // CC 11, 0-127 range
        
        controller.AddMapping(map1);
        controller.AddMapping(map2);
        controller.AddMapping(map3);
        
        assert(controller.GetMappingCount() == 3);
        assert(controller.GetMapping(0).GetCC() == 1);
        assert(controller.GetMapping(1).GetName() == "Volume");
        
        LOG("MidiController test passed");
    }

    LOG("All MIDI Inserts tests passed!");
}
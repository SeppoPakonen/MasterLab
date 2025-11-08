#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Chord Progression Mapper functionality
    {
        LOG("Testing Chord Progression Mapper functionality...");
        
        // Test basic chord progression operations
        ChordProgression chordProg;
        chordProg.SetName("Test Chord Progression");
        
        // Add some chords to the progression
        Chord c1(Note::C, ChordQuality::MAJOR, 4); // C Major in 4th octave
        Chord c2(Note::A, ChordQuality::MINOR, 4); // A Minor in 4th octave
        Chord c3(Note::F, ChordQuality::MAJOR, 4); // F Major in 4th octave
        Chord c4(Note::G, ChordQuality::MAJOR, 4); // G Major in 4th octave
        
        chordProg.AddChord(c1);
        chordProg.AddChord(c2);
        chordProg.AddChord(c3);
        chordProg.AddChord(c4);
        
        assert(chordProg.GetName() == "Test Chord Progression");
        assert(chordProg.GetChordCount() == 4);
        assert(chordProg.GetChord(0).GetRootNote() == Note::C);
        assert(chordProg.GetChord(1).GetQuality() == ChordQuality::MINOR);
        
        LOG("Chord Progression Mapper test passed");
    }

    // Test Groove Humanizer functionality
    {
        LOG("Testing Groove Humanizer functionality...");
        
        GrooveHumanizer humanizer;
        humanizer.SetName("Test Humanizer");
        
        // Test timing parameters
        humanizer.SetTimingRandomization(0.15);  // 15% timing randomization
        humanizer.SetVelocityRandomization(0.1); // 10% velocity randomization
        humanizer.SetHumanizationAmount(0.8);    // 80% humanization
        
        assert(humanizer.GetName() == "Test Humanizer");
        assert(abs(humanizer.GetTimingRandomization() - 0.15) < 0.001);
        assert(abs(humanizer.GetVelocityRandomization() - 0.1) < 0.001);
        assert(abs(humanizer.GetHumanizationAmount() - 0.8) < 0.001);
        
        // Test applying humanization to a MIDI event
        MidiEvent event(0x90, 0, 60, 100, 1.0); // Note On at 1.0 seconds
        MidiEvent humanizedEvent = humanizer.ApplyHumanization(event, 120.0); // At 120 BPM
        
        // The humanized event should have similar properties but slightly different timing/velocity
        assert(humanizedEvent.GetType() == 0x90); // Should still be Note On
        assert(humanizedEvent.GetNote() == 60);   // Same note
        assert(humanizedEvent.GetChannel() == 0); // Same channel
        
        LOG("Groove Humanizer test passed");
    }

    LOG("All MIDI Effects tests passed!");
}
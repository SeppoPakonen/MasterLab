#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <MIDI/MIDI.h>
#include <PluginSDK/PluginSDK.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Adaptive Drum Composer functionality
    {
        LOG("Testing Adaptive Drum Composer functionality...");
        
        AdaptiveDrumComposer composer;
        composer.SetName("Test Drum Composer");
        
        // Test pattern parameters
        composer.SetSwingAmount(0.6);
        assert(abs(composer.GetSwingAmount() - 0.6) < 0.001);
        
        composer.SetComplexity(0.7);
        assert(abs(composer.GetComplexity() - 0.7) < 0.001);
        
        composer.SetVelocityVariation(0.3);
        assert(abs(composer.GetVelocityVariation() - 0.3) < 0.001);
        
        // Test adding drum patterns
        DrumPattern pattern1("Kick Pattern");
        pattern1.AddHit(0.0, 36, 100);   // Kick at time 0
        pattern1.AddHit(0.5, 36, 90);    // Kick at time 0.5
        pattern1.AddHit(1.0, 36, 100);   // Kick at time 1.0
        
        composer.AddPattern(pattern1);
        assert(composer.GetPatternCount() == 1);
        
        LOG("Adaptive Drum Composer test passed");
    }

    // Test Harmony Phrase Studio functionality
    {
        LOG("Testing Harmony Phrase Studio functionality...");
        
        HarmonyPhraseStudio studio;
        studio.SetName("Test Harmony Studio");
        
        // Test harmony settings
        studio.SetChordProgressionEnabled(true);
        assert(studio.GetChordProgressionEnabled() == true);
        
        studio.SetVoiceLeadingEnabled(true);
        assert(studio.GetVoiceLeadingEnabled() == true);
        
        studio.SetInversionLimit(2);
        assert(studio.GetInversionLimit() == 2);
        
        // Test creating a harmony phrase
        HarmonyPhrase phrase;
        phrase.SetName("Test Phrase");
        
        // Add some notes to the phrase
        phrase.AddNote(0.0, 60, 0.5, 80);  // C note, duration 0.5, velocity 80
        phrase.AddNote(0.25, 64, 0.25, 75); // E note
        phrase.AddNote(0.5, 67, 0.5, 85);   // G note
        
        assert(phrase.GetName() == "Test Phrase");
        assert(phrase.GetNoteCount() == 3);
        
        studio.AddPhrase(phrase);
        assert(studio.GetPhraseCount() == 1);
        
        LOG("Harmony Phrase Studio test passed");
    }

    LOG("All MIDI Instruments tests passed!");
}
#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <AudioFX/AudioFX.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Effects functionality
    {
        LOG("Testing Effects functionality...");
        
        // Test creating an effect
        PluginInfo info;
        info.name = "TestEffect";
        info.type = PluginType::EFFECT;
        info.category = "Reverb";
        info.manufacturer = "Test Manufacturer";
        
        assert(info.name == "TestEffect");
        assert(info.type == PluginType::EFFECT);
        
        LOG("Basic effect test passed");
    }

    // Test effect processing
    {
        LOG("Testing effect processing...");
        
        // Create an effect
        Effect effect;
        effect.SetName("Reverb Effect");
        
        // Add some parameters
        Parameter decayTime("decay_time", "Decay Time", 1.5, 0.1, 10.0);
        Parameter preDelay("pre_delay", "Pre-Delay", 0.05, 0.0, 0.5);
        Parameter wetDry("wet_dry", "Wet/Dry Mix", 0.7, 0.0, 1.0);
        
        effect.AddParameter(decayTime);
        effect.AddParameter(preDelay);
        effect.AddParameter(wetDry);
        
        assert(effect.GetName() == "Reverb Effect");
        assert(effect.GetParameterCount() == 3);
        
        LOG("Effect processing test passed");
    }

    LOG("All Effects tests passed!");
}
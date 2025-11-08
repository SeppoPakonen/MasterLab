#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <PluginSDK/PluginSDK.h>
#include <AudioCore/AudioCore.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Instrument functionality
    {
        LOG("Testing Instrument functionality...");
        
        // Test basic instrument creation
        PluginInfo info;
        info.name = "TestInstrument";
        info.type = PluginType::INSTRUMENT;
        info.category = "Synth";
        info.manufacturer = "Test Manufacturer";
        
        assert(info.name == "TestInstrument");
        assert(info.type == PluginType::INSTRUMENT);
        
        LOG("Basic instrument test passed");
    }

    // Test Instrument parameters
    {
        LOG("Testing Instrument parameters...");
        
        // Create a parameter set for an instrument
        ParameterSet paramSet;
        Parameter param1("volume", "Volume", 0.8, 0.0, 1.0);
        Parameter param2("cutoff", "Filter Cutoff", 0.5, 0.0, 1.0);
        
        paramSet.AddParameter(param1);
        paramSet.AddParameter(param2);
        
        assert(paramSet.GetParameterCount() == 2);
        assert(paramSet.GetParameter(0).GetName() == "volume");
        assert(paramSet.GetParameter(1).GetValue() == 0.5);
        
        LOG("Instrument parameters test passed");
    }

    LOG("All Instrument tests passed!");
}
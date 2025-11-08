#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <PluginSDK/PluginSDK.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test PluginManager functionality
    {
        LOG("Testing PluginManager functionality...");
        
        PluginManager pm;
        assert(pm.GetPluginCount() == 0);
        
        // Register a test plugin
        PluginInfo info;
        info.name = "TestPlugin";
        info.type = PluginType::INSTRUMENT;
        info.category = "Synth";
        info.path = "/path/to/test.plugin";
        
        pm.RegisterPlugin(info);
        assert(pm.GetPluginCount() == 1);
        
        auto plugins = pm.GetPlugins();
        assert(plugins.GetCount() == 1);
        assert(plugins[0].name == "TestPlugin");
        
        LOG("PluginManager test passed");
    }

    // Test Parameter functionality
    {
        LOG("Testing Parameter functionality...");
        
        Parameter param("test_param", "Test Parameter", 0.5, 0.0, 1.0);
        
        assert(param.GetName() == "test_param");
        assert(param.GetLabel() == "Test Parameter");
        assert(abs(param.GetValue() - 0.5) < 0.001);
        assert(abs(param.GetMinValue() - 0.0) < 0.001);
        assert(abs(param.GetMaxValue() - 1.0) < 0.001);
        
        // Test value setting
        param.SetValue(0.8);
        assert(abs(param.GetValue() - 0.8) < 0.001);
        
        // Test value clamping
        param.SetValue(1.5); // Exceeds max
        assert(abs(param.GetValue() - 1.0) < 0.001); // Should be clamped to max
        
        param.SetValue(-0.5); // Below min
        assert(abs(param.GetValue() - 0.0) < 0.001); // Should be clamped to min
        
        LOG("Parameter test passed");
    }

    // Test ParameterSet functionality
    {
        LOG("Testing ParameterSet functionality...");
        
        ParameterSet paramSet;
        
        Parameter param1("param1", "Parameter 1", 0.2, 0.0, 1.0);
        Parameter param2("param2", "Parameter 2", 0.7, 0.0, 1.0);
        Parameter param3("param3", "Parameter 3", 0.4, 0.0, 1.0);
        
        paramSet.AddParameter(param1);
        paramSet.AddParameter(param2);
        paramSet.AddParameter(param3);
        
        assert(paramSet.GetParameterCount() == 3);
        assert(paramSet.GetParameter(0).GetName() == "param1");
        assert(paramSet.GetParameter(1).GetValue() == 0.7);
        assert(paramSet.GetParameter(2).GetLabel() == "Parameter 3");
        
        LOG("ParameterSet test passed");
    }

    LOG("All PluginSDK tests passed!");
}
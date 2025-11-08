#include <Core/Core.h>
#include <CtrlLog/CtrlLog.h>
#include <TransportUI/TransportUI.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
    // Test Transport functionality
    {
        LOG("Testing TransportUI functionality...");
        
        Transport transport;
        assert(transport.GetState() == TransportState::STOPPED);
        assert(abs(transport.GetPosition() - 0.0) < 0.001);
        assert(abs(transport.GetTempo() - 120.0) < 0.001); // Default tempo
        
        // Test position setting
        transport.SetPosition(5.5);
        assert(abs(transport.GetPosition() - 5.5) < 0.001);
        
        // Test tempo setting
        transport.SetTempo(130.0);
        assert(abs(transport.GetTempo() - 130.0) < 0.001);
        
        LOG("Transport test passed");
    }

    // Test Metronome functionality
    {
        LOG("Testing Metronome functionality...");
        
        Metronome metronome;
        assert(metronome.IsEnabled() == false);
        
        metronome.SetEnabled(true);
        assert(metronome.IsEnabled() == true);
        
        metronome.SetVolume(0.7);
        assert(abs(metronome.GetVolume() - 0.7) < 0.001);
        
        LOG("Metronome test passed");
    }

    // Test CycleRange functionality
    {
        LOG("Testing CycleRange functionality...");
        
        CycleRange cycle;
        assert(cycle.IsEnabled() == false);
        assert(abs(cycle.GetStart() - 0.0) < 0.001);
        assert(abs(cycle.GetEnd() - 0.0) < 0.001);
        
        cycle.SetRange(2.0, 8.0);
        assert(abs(cycle.GetStart() - 2.0) < 0.001);
        assert(abs(cycle.GetEnd() - 8.0) < 0.001);
        
        cycle.SetEnabled(true);
        assert(cycle.IsEnabled() == true);
        
        LOG("CycleRange test passed");
    }

    LOG("All TransportUI tests passed!");
}
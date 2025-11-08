#ifndef _Devices_RoutingRepository_h_
#define _Devices_RoutingRepository_h_

#include <Core/Core.h>
#include "PluginManager.h"

using namespace Upp;

namespace Devices {

// Repository for managing routing information
class RoutingRepository {
public:
    RoutingRepository();
    ~RoutingRepository();
    
    // Get available sources for routing
    Vector<String> GetAvailableSources() const;
    
    // Get available destinations for routing
    Vector<String> GetAvailableDestinations() const;
    
    // Refresh the available I/O list
    void RefreshIO();
    
    // Load routing presets
    bool LoadPreset(const String& presetName);
    
    // Save routing presets
    bool SavePreset(const String& presetName);
    
    // Get available presets
    Vector<String> GetPresets() const;
    
    // Apply preset routing configuration
    bool ApplyPreset(const String& presetName);
    
    // Get all available plugins for routing
    Vector<String> GetAvailablePlugins() const;
    
    // Get all available audio tracks for routing
    Vector<String> GetAvailableAudioTracks() const;
    
    // Get all available MIDI tracks for routing
    Vector<String> GetAvailableMIDITracks() const;
    
    // Get all available hardware I/O ports
    Vector<String> GetAvailableHardwarePorts() const;
    
    // Get current routing configuration as JSON
    String GetConfigurationAsJson() const;
    
    // Load routing configuration from JSON
    bool LoadConfigurationFromJson(const String& jsonStr);
    
private:
    Vector<String> availableSources;
    Vector<String> availableDestinations;
    Vector<String> availablePresets;
    
    void BuildIOLists();
    void LoadDefaultPresets();
};

}

#endif
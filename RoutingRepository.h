#ifndef _Devices_RoutingRepository_h_
#define _Devices_RoutingRepository_h_

#include <Core/Core.h>
#include <Devices/Devices.h>
#include <AudioCore/AudioCore.h>
#include "IOMatrixService.h"

NAMESPACE_UPP

// Repository for managing routing configurations
class RoutingRepository {
public:
    RoutingRepository();
    virtual ~RoutingRepository();
    
    // Load and save routing configurations to persistent storage
    bool LoadConfiguration(const String& configName);
    bool SaveConfiguration(const String& configName);
    bool DeleteConfiguration(const String& configName);
    Vector<String> GetConfigurationList() const;
    
    // Apply changes to the routing system
    bool ApplyChanges(const Vector<RoutingConnection>& changes);
    bool CommitChanges(); // Save pending changes to persistent storage
    bool RollbackChanges(); // Discard pending changes
    
    // Working with routing snapshots
    bool AddSnapshot(const RoutingSnapshot& snapshot);
    bool UpdateSnapshot(const String& name, const RoutingSnapshot& snapshot);
    bool RemoveSnapshot(const String& name);
    RoutingSnapshot GetSnapshot(const String& name) const;
    
    // Working with presets
    bool AddPreset(const RoutingSnapshot& preset);
    bool UpdatePreset(const String& name, const RoutingSnapshot& preset);
    bool RemovePreset(const String& name);
    RoutingSnapshot GetPreset(const String& name) const;
    
    // Validation methods
    bool ValidateConnection(const RoutingConnection& connection) const;
    Vector<String> GetValidationErrors(const RoutingConnection& connection) const;
    
    // Access to current configuration
    const Vector<RoutingConnection>& GetCurrentConfig() const { return currentConfig; }
    Vector<RoutingConnection>& GetCurrentConfig() { return currentConfig; }
    
private:
    Vector<RoutingConnection> currentConfig;  // Current active configuration
    Vector<RoutingConnection> pendingChanges; // Changes not yet committed
    VectorMap<String, RoutingSnapshot> snapshots; // Saved snapshots
    VectorMap<String, RoutingSnapshot> presets;    // Saved presets
    
    // Private helper methods
    String GetConfigPath(const String& configName) const;
    bool SerializeConfig(const Vector<RoutingConnection>& config, const String& path) const;
    Vector<RoutingConnection> DeserializeConfig(const String& path) const;
    bool IsValidEndpoint(const String& endpoint) const;
};

END_UPP_NAMESPACE

#endif
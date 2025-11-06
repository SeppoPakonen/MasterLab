#ifndef _Devices_IOMatrixService_h_
#define _Devices_IOMatrixService_h_

#include <Core/Core.h>
#include <Devices/Devices.h>
#include <AudioCore/AudioCore.h>

NAMESPACE_UPP

// Represents a routing connection
struct RoutingConnection {
    String source;           // Source endpoint
    String destination;      // Destination endpoint
    String sourcePort;       // Specific port if applicable
    String destinationPort;  // Specific port if applicable
    bool isEnabled;          // Whether this routing is active
    int channelCount;        // Number of channels in this connection
    double latencyOffset;    // Latency offset in milliseconds
    
    RoutingConnection() : isEnabled(true), channelCount(2), latencyOffset(0.0) {}
};

// Represents a snapshot of the routing state
struct RoutingSnapshot {
    String name;
    String description;
    Vector<RoutingConnection> connections;
    Time timestamp;
    
    RoutingSnapshot() : timestamp(GetSysTime()) {}
};

// Service for managing I/O routing matrix
class IOMatrixService {
public:
    IOMatrixService();
    virtual ~IOMatrixService();
    
    // Methods for managing routing connections
    bool Connect(const String& source, const String& destination, int channels = 2);
    bool Disconnect(const String& source, const String& destination);
    bool IsConnected(const String& source, const String& destination) const;
    Vector<RoutingConnection> GetAllConnections() const;
    
    // Methods for managing routing snapshots
    bool SaveSnapshot(const String& name, const String& description = "");
    bool LoadSnapshot(const String& name);
    bool DeleteSnapshot(const String& name);
    VectorMap<String, String> GetSnapshotList() const; // name -> description
    
    // Methods for preset management
    bool ApplyPreset(const String& presetName);
    bool SavePreset(const String& presetName, const String& description = "");
    bool DeletePreset(const String& presetName);
    VectorMap<String, String> GetPresetList() const; // name -> description
    
    // Update a connection with new parameters
    bool UpdateConnection(const String& source, const String& destination, 
                         bool enabled = true, double latency = 0.0);
    
private:
    Vector<RoutingConnection> connections;
    VectorMap<String, RoutingSnapshot> snapshots;
    VectorMap<String, RoutingSnapshot> presets; // Presets are special snapshots
    
    // Private helper methods
    int FindConnectionIndex(const String& source, const String& destination) const;
    int FindSnapshotIndex(const String& name) const;
    int FindPresetIndex(const String& name) const;
};

END_UPP_NAMESPACE

#endif
#ifndef _Devices_IOMatrixService_h_
#define _Devices_IOMatrixService_h_

#include <Core/Core.h>
#include <plugin/PluginManager/PluginManager.h>
#include "RoutingRepository.h"

using namespace Upp;

namespace Devices {

// Represents a connection between source and destination in the I/O matrix
struct Connection {
    String source;      // Plugin/track name, bus name, etc.
    String destination; // Plugin/track name, bus name, etc.
    int channel;        // Audio channel or MIDI channel
    bool isActive;      // Whether the connection is currently active
    
    Connection() : channel(0), isActive(true) {}
    Connection(const String& src, const String& dst, int ch, bool active = true)
        : source(src), destination(dst), channel(ch), isActive(active) {}
};

// IOMatrixService manages VST connections and I/O routing
class IOMatrixService {
public:
    IOMatrixService();
    ~IOMatrixService();
    
    // Get current connection snapshot
    Vector<Connection> GetSnapshot() const;
    
    // Apply connections to the audio system
    bool ApplyConnections(const Vector<Connection>& connections);
    
    // Create a new connection
    bool CreateConnection(const Connection& conn);
    
    // Remove an existing connection
    bool RemoveConnection(const Connection& conn);
    
    // Update an existing connection
    bool UpdateConnection(const Connection& oldConn, const Connection& newConn);
    
    // Get available sources for connections
    Vector<String> GetAvailableSources() const;
    
    // Get available destinations for connections
    Vector<String> GetAvailableDestinations() const;
    
    // Get connections for a specific source
    Vector<Connection> GetConnectionsForSource(const String& source) const;
    
    // Get connections for a specific destination
    Vector<Connection> GetConnectionsForDestination(const String& destination) const;
    
    // Get audio routing repository
    RoutingRepository& GetRoutingRepository() { return routingRepo; }
    
    // Update connection status in real-time
    void UpdateConnectionStatus(const String& source, const String& destination, bool active);
    
    // Refresh available sources and destinations
    void RefreshAvailableIO();
    
private:
    RoutingRepository routingRepo;
    Vector<Connection> currentConnections;
    
    // Internal methods
    bool ValidateConnection(const Connection& conn) const;
    void NotifyConnectionChange(const Connection& conn, int changeType); // 0=added, 1=removed, 2=updated
};

}

#endif
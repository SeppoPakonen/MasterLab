#include "IOMatrixService.h"

namespace Devices {

IOMatrixService::IOMatrixService() {
    RefreshAvailableIO();
}

IOMatrixService::~IOMatrixService() {
    // Clean up connections
}

Vector<Connection> IOMatrixService::GetSnapshot() const {
    return currentConnections;
}

bool IOMatrixService::ApplyConnections(const Vector<Connection>& connections) {
    // Apply the connections to the audio system
    for(const Connection& conn : connections) {
        if(!ValidateConnection(conn)) {
            return false;
        }
    }
    
    // For now, just store the connections
    currentConnections = connections;
    
    // In a real implementation, this would apply the routing to the audio system
    return true;
}

bool IOMatrixService::CreateConnection(const Connection& conn) {
    if(!ValidateConnection(conn)) {
        return false;
    }
    
    // Check if connection already exists
    for(const Connection& existing : currentConnections) {
        if(existing.source == conn.source && 
           existing.destination == conn.destination && 
           existing.channel == conn.channel) {
            return false; // Connection already exists
        }
    }
    
    currentConnections.Add(conn);
    NotifyConnectionChange(conn, 0); // 0 = added
    return true;
}

bool IOMatrixService::RemoveConnection(const Connection& conn) {
    for(int i = 0; i < currentConnections.GetCount(); i++) {
        const Connection& existing = currentConnections[i];
        if(existing.source == conn.source && 
           existing.destination == conn.destination && 
           existing.channel == conn.channel) {
            NotifyConnectionChange(existing, 1); // 1 = removed
            currentConnections.Remove(i);
            return true;
        }
    }
    return false;
}

bool IOMatrixService::UpdateConnection(const Connection& oldConn, const Connection& newConn) {
    if(!ValidateConnection(newConn)) {
        return false;
    }
    
    for(int i = 0; i < currentConnections.GetCount(); i++) {
        Connection& existing = currentConnections[i];
        if(existing.source == oldConn.source && 
           existing.destination == oldConn.destination && 
           existing.channel == oldConn.channel) {
            existing = newConn;
            NotifyConnectionChange(newConn, 2); // 2 = updated
            return true;
        }
    }
    return false;
}

Vector<String> IOMatrixService::GetAvailableSources() const {
    return routingRepo.GetAvailableSources();
}

Vector<String> IOMatrixService::GetAvailableDestinations() const {
    return routingRepo.GetAvailableDestinations();
}

Vector<Connection> IOMatrixService::GetConnectionsForSource(const String& source) const {
    Vector<Connection> result;
    for(const Connection& conn : currentConnections) {
        if(conn.source == source) {
            result.Add(conn);
        }
    }
    return result;
}

Vector<Connection> IOMatrixService::GetConnectionsForDestination(const String& destination) const {
    Vector<Connection> result;
    for(const Connection& conn : currentConnections) {
        if(conn.destination == destination) {
            result.Add(conn);
        }
    }
    return result;
}

void IOMatrixService::UpdateConnectionStatus(const String& source, const String& destination, bool active) {
    for(Connection& conn : currentConnections) {
        if(conn.source == source && conn.destination == destination) {
            conn.isActive = active;
            // In a real implementation, update the audio routing here
        }
    }
}

void IOMatrixService::RefreshAvailableIO() {
    // Refresh available I/O ports
    routingRepo.RefreshIO();
}

bool IOMatrixService::ValidateConnection(const Connection& conn) const {
    // Basic validation
    return !conn.source.IsEmpty() && !conn.destination.IsEmpty();
}

void IOMatrixService::NotifyConnectionChange(const Connection& conn, int changeType) {
    // In a real implementation, this would notify interested parties about the change
    // This could be used to update UI, update the audio routing, etc.
}

}
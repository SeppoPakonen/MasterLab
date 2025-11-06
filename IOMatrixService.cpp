#include "IOMatrixService.h"

NAMESPACE_UPP

IOMatrixService::IOMatrixService() {
    // Initialize the I/O matrix service
}

IOMatrixService::~IOMatrixService() {
    // Clean up resources
}

bool IOMatrixService::Connect(const String& source, const String& destination, int channels) {
    // Check if connection already exists
    if (IsConnected(source, destination)) {
        return false; // Already connected
    }
    
    // Create new connection
    RoutingConnection conn;
    conn.source = source;
    conn.destination = destination;
    conn.channelCount = channels;
    conn.isEnabled = true;
    
    connections.Add(conn);
    return true;
}

bool IOMatrixService::Disconnect(const String& source, const String& destination) {
    int idx = FindConnectionIndex(source, destination);
    if (idx >= 0) {
        connections.Remove(idx);
        return true;
    }
    return false;
}

bool IOMatrixService::IsConnected(const String& source, const String& destination) const {
    return FindConnectionIndex(source, destination) >= 0;
}

Vector<RoutingConnection> IOMatrixService::GetAllConnections() const {
    return connections;
}

bool IOMatrixService::SaveSnapshot(const String& name, const String& description) {
    // Check if snapshot already exists
    if (FindSnapshotIndex(name) >= 0) {
        return false; // Snapshot already exists
    }
    
    // Create new snapshot
    RoutingSnapshot snapshot;
    snapshot.name = name;
    snapshot.description = description;
    snapshot.connections = connections; // Copy all current connections
    
    snapshots.Add(name, snapshot);
    return true;
}

bool IOMatrixService::LoadSnapshot(const String& name) {
    int idx = FindSnapshotIndex(name);
    if (idx >= 0) {
        // Apply the snapshot connections
        connections = snapshots[idx].connections; // This performs a deep copy
        return true;
    }
    return false;
}

bool IOMatrixService::DeleteSnapshot(const String& name) {
    int idx = FindSnapshotIndex(name);
    if (idx >= 0) {
        snapshots.RemoveIdx(idx);
        return true;
    }
    return false;
}

VectorMap<String, String> IOMatrixService::GetSnapshotList() const {
    VectorMap<String, String> result;
    for(int i = 0; i < snapshots.GetCount(); i++) {
        result.Add(snapshots.GetKey(i), snapshots[i].description);
    }
    return result;
}

bool IOMatrixService::ApplyPreset(const String& presetName) {
    int idx = FindPresetIndex(presetName);
    if (idx >= 0) {
        connections = presets[idx].connections; // Apply preset connections
        return true;
    }
    return false;
}

bool IOMatrixService::SavePreset(const String& presetName, const String& description) {
    // Check if preset already exists
    if (FindPresetIndex(presetName) >= 0) {
        return false; // Preset already exists
    }
    
    // Create new preset from current connections
    RoutingSnapshot preset;
    preset.name = presetName;
    preset.description = description;
    preset.connections = connections; // Copy all current connections
    
    presets.Add(presetName, preset);
    return true;
}

bool IOMatrixService::DeletePreset(const String& presetName) {
    int idx = FindPresetIndex(presetName);
    if (idx >= 0) {
        presets.RemoveIdx(idx);
        return true;
    }
    return false;
}

VectorMap<String, String> IOMatrixService::GetPresetList() const {
    VectorMap<String, String> result;
    for(int i = 0; i < presets.GetCount(); i++) {
        result.Add(presets.GetKey(i), presets[i].description);
    }
    return result;
}

bool IOMatrixService::UpdateConnection(const String& source, const String& destination, 
                                      bool enabled, double latency) {
    int idx = FindConnectionIndex(source, destination);
    if (idx >= 0) {
        connections[idx].isEnabled = enabled;
        connections[idx].latencyOffset = latency;
        return true;
    }
    return false;
}

int IOMatrixService::FindConnectionIndex(const String& source, const String& destination) const {
    for(int i = 0; i < connections.GetCount(); i++) {
        if (connections[i].source == source && connections[i].destination == destination) {
            return i;
        }
    }
    return -1;
}

int IOMatrixService::FindSnapshotIndex(const String& name) const {
    for(int i = 0; i < snapshots.GetCount(); i++) {
        if (snapshots.GetKey(i) == name) {
            return i;
        }
    }
    return -1;
}

int IOMatrixService::FindPresetIndex(const String& name) const {
    for(int i = 0; i < presets.GetCount(); i++) {
        if (presets.GetKey(i) == name) {
            return i;
        }
    }
    return -1;
}

END_UPP_NAMESPACE
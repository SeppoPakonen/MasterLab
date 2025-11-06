#include "RoutingRepository.h"
#include <plugin/bcrypt/bcrypt.h>

NAMESPACE_UPP

RoutingRepository::RoutingRepository() {
    // Initialize the routing repository
}

RoutingRepository::~RoutingRepository() {
    // Save any pending changes before destruction
    CommitChanges();
}

bool RoutingRepository::LoadConfiguration(const String& configName) {
    String path = GetConfigPath(configName);
    if (FileExists(path)) {
        currentConfig = DeserializeConfig(path);
        return true;
    }
    return false;
}

bool RoutingRepository::SaveConfiguration(const String& configName) {
    String path = GetConfigPath(configName);
    return SerializeConfig(currentConfig, path);
}

bool RoutingRepository::DeleteConfiguration(const String& configName) {
    String path = GetConfigPath(configName);
    if (FileExists(path)) {
        return DeleteFile(path);
    }
    return false;
}

Vector<String> RoutingRepository::GetConfigurationList() const {
    Vector<String> configs;
    // Look for configuration files in the appropriate directory
    FindFile ff(GetConfigPath("*"));
    while(ff) {
        if (!ff.IsDirectory()) {
            String name = ff.GetName();
            if (name.EndsWith(".cfg")) {
                configs.Add(name.Mid(0, name.GetLength() - 4)); // Remove .cfg extension
            }
        }
        ff.Next();
    }
    return configs;
}

bool RoutingRepository::ApplyChanges(const Vector<RoutingConnection>& changes) {
    // Validate all changes before applying them
    for(const auto& change : changes) {
        if (!ValidateConnection(change)) {
            return false; // Invalid connection found
        }
    }
    
    // Apply the changes to pending changes
    pendingChanges = changes;
    return true;
}

bool RoutingRepository::CommitChanges() {
    // Save pending changes to permanent storage
    if (pendingChanges.GetCount() > 0) {
        currentConfig = pendingChanges;
        pendingChanges.Clear();
        return SaveConfiguration("default");
    }
    return true; // Nothing to commit, but operation is successful
}

bool RoutingRepository::RollbackChanges() {
    pendingChanges.Clear(); // Discard pending changes
    return true;
}

bool RoutingRepository::AddSnapshot(const RoutingSnapshot& snapshot) {
    if (FindIndex(snapshots.GetKeys(), snapshot.name) >= 0) {
        return false; // Snapshot already exists
    }
    
    snapshots.Add(snapshot.name, snapshot);
    return true;
}

bool RoutingRepository::UpdateSnapshot(const String& name, const RoutingSnapshot& snapshot) {
    int idx = FindIndex(snapshots.GetKeys(), name);
    if (idx >= 0) {
        snapshots.Set(idx, snapshot);
        return true;
    }
    return false;
}

bool RoutingRepository::RemoveSnapshot(const String& name) {
    int idx = FindIndex(snapshots.GetKeys(), name);
    if (idx >= 0) {
        snapshots.RemoveIdx(idx);
        return true;
    }
    return false;
}

RoutingSnapshot RoutingRepository::GetSnapshot(const String& name) const {
    int idx = FindIndex(snapshots.GetKeys(), name);
    if (idx >= 0) {
        return snapshots[idx];
    }
    return RoutingSnapshot(); // Return empty snapshot if not found
}

bool RoutingRepository::AddPreset(const RoutingSnapshot& preset) {
    if (FindIndex(presets.GetKeys(), preset.name) >= 0) {
        return false; // Preset already exists
    }
    
    presets.Add(preset.name, preset);
    return true;
}

bool RoutingRepository::UpdatePreset(const String& name, const RoutingSnapshot& preset) {
    int idx = FindIndex(presets.GetKeys(), name);
    if (idx >= 0) {
        presets.Set(idx, preset);
        return true;
    }
    return false;
}

bool RoutingRepository::RemovePreset(const String& name) {
    int idx = FindIndex(presets.GetKeys(), name);
    if (idx >= 0) {
        presets.RemoveIdx(idx);
        return true;
    }
    return false;
}

RoutingSnapshot RoutingRepository::GetPreset(const String& name) const {
    int idx = FindIndex(presets.GetKeys(), name);
    if (idx >= 0) {
        return presets[idx];
    }
    return RoutingSnapshot(); // Return empty preset if not found
}

bool RoutingRepository::ValidateConnection(const RoutingConnection& connection) const {
    // Check if source and destination endpoints are valid
    if (!IsValidEndpoint(connection.source) || !IsValidEndpoint(connection.destination)) {
        return false;
    }
    
    // Additional validation rules could be added here
    if (connection.source == connection.destination) {
        return false; // Cannot connect source to itself
    }
    
    return true;
}

Vector<String> RoutingRepository::GetValidationErrors(const RoutingConnection& connection) const {
    Vector<String> errors;
    
    if (!IsValidEndpoint(connection.source)) {
        errors.Add("Invalid source endpoint: " + connection.source);
    }
    
    if (!IsValidEndpoint(connection.destination)) {
        errors.Add("Invalid destination endpoint: " + connection.destination);
    }
    
    if (connection.source == connection.destination) {
        errors.Add("Cannot connect source to itself");
    }
    
    return errors;
}

String RoutingRepository::GetConfigPath(const String& configName) const {
    // Return the path where configuration files are stored
    return AppendFileName(GetExeDir(), "Configs");
}

bool RoutingRepository::SerializeConfig(const Vector<RoutingConnection>& config, const String& path) const {
    // For now, we'll serialize to a simple text format
    // In production, this would use a more structured format like JSON or a binary format
    FileOut out(path);
    if (!out) {
        return false;
    }
    
    for (const auto& conn : config) {
        out << conn.source << "\t" 
            << conn.destination << "\t" 
            << conn.isEnabled << "\t"
            << conn.channelCount << "\t"
            << conn.latencyOffset << "\n";
    }
    
    return out.IsEof();
}

Vector<RoutingConnection> RoutingRepository::DeserializeConfig(const String& path) const {
    Vector<RoutingConnection> config;
    
    FileIn in(path);
    if (!in) {
        return config; // Return empty config if file doesn't exist
    }
    
    String line;
    while (ReadLine(in, line)) {
        if (line.IsEmpty()) continue;
        
        Vector<String> parts = Split(line, '\t');
        if (parts.GetCount() >= 5) {
            RoutingConnection conn;
            conn.source = parts[0];
            conn.destination = parts[1];
            conn.isEnabled = parts[2] == "1";
            conn.channelCount = StrInt(parts[3]);
            conn.latencyOffset = StrDouble(parts[4]);
            config.Add(conn);
        }
    }
    
    return config;
}

bool RoutingRepository::IsValidEndpoint(const String& endpoint) const {
    // Basic validation: endpoint should not be empty and should not contain special characters
    // that would cause issues in routing paths
    return !endpoint.IsEmpty() && 
           endpoint.FindFirstOf("<>") < 0 && 
           endpoint.FindFirstOf("|") < 0;
}

END_UPP_NAMESPACE
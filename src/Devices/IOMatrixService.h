#ifndef _Devices_IOMatrixService_h_
#define _Devices_IOMatrixService_h_

#include <Core/Core.h>
#include <AudioCore/AudioCore.h>
using namespace Upp;

namespace am {

// Structure for representing connection points
struct ConnectionPoint : public Moveable<ConnectionPoint> {
    String name;
    String id;
    String deviceName;
    String portName;
    String speakers; // e.g., "Stereo", "Mono", "5.1"
    double delayMs = 0.0;
    double gainDb = 0.0;
    bool isUsed = false;
    bool hasClickOutput = false;
    
    // Add explicit constructors for U++ compatibility
    ConnectionPoint() = default;
    ConnectionPoint(const ConnectionPoint& other) = default;
    ConnectionPoint& operator=(const ConnectionPoint& other) = default;
    ConnectionPoint(ConnectionPoint&& other) = default;
    ConnectionPoint& operator=(ConnectionPoint&& other) = default;
};


// Structure for external FX connections
struct ExternalFxConnection : public Moveable<ExternalFxConnection> {
    String name;
    String id;
    String audioDevice;
    String inputPort;
    String outputPort;
    double delayMs = 0.0;
    double sendGainDb = 0.0;
    double returnGainDb = 0.0;
    String midiDevice;
    bool isUsed = false;
    
    // Add explicit constructors for U++ compatibility
    ExternalFxConnection() = default;
    ExternalFxConnection(const ExternalFxConnection& other) = default;
    ExternalFxConnection& operator=(const ExternalFxConnection& other) = default;
    ExternalFxConnection(ExternalFxConnection&& other) = default;
    ExternalFxConnection& operator=(ExternalFxConnection&& other) = default;
};


// Structure for external instrument connections
struct ExternalInstrumentConnection : public Moveable<ExternalInstrumentConnection> {
    String name;
    String id;
    String audioDevice;
    String outputPort;
    String midiDevice;
    double delayMs = 0.0;
    double returnGainDb = 0.0;
    bool isUsed = false;
    
    // Add explicit constructors for U++ compatibility
    ExternalInstrumentConnection() = default;
    ExternalInstrumentConnection(const ExternalInstrumentConnection& other) = default;
    ExternalInstrumentConnection& operator=(const ExternalInstrumentConnection& other) = default;
    ExternalInstrumentConnection(ExternalInstrumentConnection&& other) = default;
    ExternalInstrumentConnection& operator=(ExternalInstrumentConnection&& other) = default;
};


// Structure for groups/FX channels
struct GroupFxConnection : public Moveable<GroupFxConnection> {
    String name;
    String id;
    String speakers; // e.g., "Stereo", "Mono", "5.1"
    String routeTo;  // Where this group routes to
    String childRoutes; // Comma-separated string of child routes instead of Vector to enable copying
    
    // Add explicit constructors for U++ compatibility
    GroupFxConnection() = default;
    GroupFxConnection(const GroupFxConnection& other) = default;
    GroupFxConnection& operator=(const GroupFxConnection& other) = default;
    GroupFxConnection(GroupFxConnection&& other) = default;
    GroupFxConnection& operator=(GroupFxConnection&& other) = default;
};


// Structure for studio connections
struct StudioConnection : public Moveable<StudioConnection> {
    String name;
    String id;
    String speakers; // e.g., "Stereo", "Mono", "5.1"
    String audioDevice;
    String devicePort;
    bool controlRoomEnabled = false;
    
    // Add explicit constructors for U++ compatibility
    StudioConnection() = default;
    StudioConnection(const StudioConnection& other) = default;
    StudioConnection& operator=(const StudioConnection& other) = default;
    StudioConnection(StudioConnection&& other) = default;
    StudioConnection& operator=(StudioConnection&& other) = default;
};


// Repository for managing connection presets
class RoutingRepository {
public:
    RoutingRepository();
    
    // Preset management functions
    bool SavePreset(const String& name, const Vector<ConnectionPoint>& connections);
    bool LoadPreset(const String& name, Vector<ConnectionPoint>& connections);
    bool DeletePreset(const String& name);
    Vector<String> GetAvailablePresets() const;
    
    // CRUD operations for connections
    bool SaveCurrentRouting(const String& name);
    bool LoadRouting(const String& name);
    bool DeleteRouting(const String& name);
    
private:
    // Internal storage for routing presets
    VectorMap<String, Vector<ConnectionPoint>> presets;
    
    void InitializeDefaultPresets();
};

// Service for managing the I/O matrix (routing of audio/MIDI)
class IOMatrixService {
public:
    IOMatrixService();
    ~IOMatrixService();
    
    // Input connections management
    const Vector<ConnectionPoint>& GetInputs() const { return inputs; }
    bool SetInput(const ConnectionPoint& input);
    bool RemoveInput(const String& id);
    
    // Output connections management
    const Vector<ConnectionPoint>& GetOutputs() const { return outputs; }
    bool SetOutput(const ConnectionPoint& output);
    bool RemoveOutput(const String& id);
    
    // Groups/FX connections management
    const Vector<GroupFxConnection>& GetGroupsFx() const { return groupsFxs; }
    bool SetGroupFx(const GroupFxConnection& group);
    bool RemoveGroupFx(const String& id);
    
    // External FX connections management
    const Vector<ExternalFxConnection>& GetExternalFx() const { return externalFxs; }
    bool SetExternalFx(const ExternalFxConnection& fx);
    bool RemoveExternalFx(const String& id);
    
    // External Instrument connections management
    const Vector<ExternalInstrumentConnection>& GetExternalInstruments() const { return externalInstruments; }
    bool SetExternalInstrument(const ExternalInstrumentConnection& instrument);
    bool RemoveExternalInstrument(const String& id);
    
    // Studio connections management
    const Vector<StudioConnection>& GetStudio() const { return studioConnections; }
    bool SetStudio(const StudioConnection& studio);
    bool RemoveStudio(const String& id);
    
    // Apply changes to the actual audio system
    void ApplyChanges();
    
    // Access to the routing repository
    RoutingRepository& GetRoutingRepository() { return routingRepo; }
    
    // Singleton access pattern
    static IOMatrixService& GetInstance();
    
private:
    // Internal storage for all connection types
    Vector<ConnectionPoint> inputs;
    Vector<ConnectionPoint> outputs;
    Vector<GroupFxConnection> groupsFxs;
    Vector<ExternalFxConnection> externalFxs;
    Vector<ExternalInstrumentConnection> externalInstruments;
    Vector<StudioConnection> studioConnections;
    
    RoutingRepository routingRepo;
    
    // Singleton instance
    static IOMatrixService* instance;
    
    void InitializeDefaultConnections();
};

}

#endif
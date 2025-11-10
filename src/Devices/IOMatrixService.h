#ifndef _Devices_IOMatrixService_h_
#define _Devices_IOMatrixService_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h> // For audio device management

using namespace Upp;

namespace Devices {

// Structure representing an audio bus
struct AudioBus : Moveable<AudioBus> {
    String name;
    String speakerConfig;  // Mono, Stereo, 5.0, 5.1, etc.
    String audioDevice;
    Vector<String> devicePorts;  // Per channel when expanded
    bool isExpanded;
    
    AudioBus() : isExpanded(false) {}
};

// Structure for external FX
struct ExternalFx : Moveable<ExternalFx> {
    String name;
    String sendConfig;
    String returnConfig;
    String midiDevice;
    double delayMs;
    double sendGainDb;
    double returnGainDb;
    bool isUsed;
    
    ExternalFx() : delayMs(0.0), sendGainDb(0.0), returnGainDb(0.0), isUsed(false) {}
};

// Structure for external instruments
struct ExternalInstrument : Moveable<ExternalInstrument> {
    String name;
    int monoReturnsCount;
    int stereoReturnsCount;
    String midiDevice;
    double delayMs;
    double returnGainDb;
    bool isUsed;
    
    ExternalInstrument() : monoReturnsCount(0), stereoReturnsCount(0), delayMs(0.0), returnGainDb(0.0), isUsed(false) {}
};

// Enum for connection types
enum ConnectionType {
    INPUTS,
    OUTPUTS,
    GROUPS_FX,
    EXTERNAL_FX,
    EXTERNAL_INSTRUMENTS,
    STUDIO
};

// Service class for managing I/O routing matrix
class IOMatrixService {
public:
    IOMatrixService();
    ~IOMatrixService();
    
    // Core functionality
    void Initialize();
    void Shutdown();
    
    // Input management
    Vector<AudioBus> GetInputs() const;
    void AddInput(const AudioBus& bus);
    void RemoveInput(int index);
    void UpdateInput(int index, const AudioBus& bus);
    
    // Output management
    Vector<AudioBus> GetOutputs() const;
    void AddOutput(const AudioBus& bus);
    void RemoveOutput(int index);
    void UpdateOutput(int index, const AudioBus& bus);
    
    // Groups/FX management
    Vector<AudioBus> GetGroupsFx() const;
    void AddGroup(const AudioBus& bus);
    void RemoveGroup(int index);
    void UpdateGroup(int index, const AudioBus& bus);
    void AddFxChannel(const AudioBus& bus);
    void RemoveFxChannel(int index);
    void UpdateFxChannel(int index, const AudioBus& bus);
    
    // External FX management
    Vector<ExternalFx> GetExternalFx() const;
    void AddExternalFx(const ExternalFx& fx);
    void RemoveExternalFx(int index);
    void UpdateExternalFx(int index, const ExternalFx& fx);
    
    // External Instruments management
    Vector<ExternalInstrument> GetExternalInstruments() const;
    void AddExternalInstrument(const ExternalInstrument& inst);
    void RemoveExternalInstrument(int index);
    void UpdateExternalInstrument(int index, const ExternalInstrument& inst);
    
    // Studio (Control Room) management
    Vector<AudioBus> GetStudio() const;
    void AddStudioBus(const AudioBus& bus);
    void RemoveStudioBus(int index);
    void UpdateStudioBus(int index, const AudioBus& bus);
    
    // Preset management
    void SavePreset(const String& name);
    void LoadPreset(const String& name);
    void DeletePreset(const String& name);
    Vector<String> GetPresets() const;
    
    // Apply changes to the system
    void ApplyChanges();
    
    // Get snapshots of current state
    ValueMap GetSnapshot(ConnectionType type) const;
    void ApplySnapshot(ConnectionType type, const ValueMap& snapshot);
    
private:
    Vector<AudioBus> inputs;
    Vector<AudioBus> outputs;
    Vector<AudioBus> groupsFx;  // Groups and FX channels mixed
    Vector<ExternalFx> externalFx;
    Vector<ExternalInstrument> externalInstruments;
    Vector<AudioBus> studio;  // Control Room buses
    
    Vector<String> presets;
    
    // Private methods
    void Reset();
};

} // namespace Devices

#endif
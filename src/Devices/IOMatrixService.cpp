#include "IOMatrixService.h"

namespace Devices {

IOMatrixService::IOMatrixService() {
    Initialize();
}

IOMatrixService::~IOMatrixService() {
    Shutdown();
}

void IOMatrixService::Initialize() {
    Reset();

    // Add default buses
    AudioBus defaultInput;
    defaultInput.name = "Stereo In";
    defaultInput.speakerConfig = "Stereo";
    defaultInput.audioDevice = "ASIO DirectX Full Duplex";
    defaultInput.devicePorts.Add("Channel 1");
    defaultInput.devicePorts.Add("Channel 2");
    inputs.Add(pick(defaultInput));  // Use pick() for move semantics

    AudioBus defaultOutput;
    defaultOutput.name = "Stereo Out";
    defaultOutput.speakerConfig = "Stereo";
    defaultOutput.audioDevice = "ASIO DirectX Full Duplex";
    defaultOutput.devicePorts.Add("Channel 1");
    defaultOutput.devicePorts.Add("Channel 2");
    outputs.Add(pick(defaultOutput));  // Use pick() for move semantics

    // Add default group and FX
    AudioBus defaultGroup;
    defaultGroup.name = "Group 1";
    defaultGroup.speakerConfig = "Stereo";
    groupsFx.Add(pick(defaultGroup));  // Use pick() for move semantics

    ExternalFx defaultFx;
    defaultFx.name = "External FX";
    defaultFx.sendConfig = "Stereo/Stereo";
    externalFx.Add(pick(defaultFx));  // Use pick() for move semantics

    ExternalInstrument defaultInst;
    defaultInst.name = "External Instrument";
    defaultInst.monoReturnsCount = 0;
    defaultInst.stereoReturnsCount = 0;
    externalInstruments.Add(pick(defaultInst));  // Use pick() for move semantics

    // Add default studio bus
    AudioBus defaultStudio;
    defaultStudio.name = "Monitor 1";
    defaultStudio.speakerConfig = "Stereo";
    studio.Add(pick(defaultStudio));  // Use pick() for move semantics
}

void IOMatrixService::Shutdown() {
    // Clean up resources if needed
    Reset();
}

void IOMatrixService::Reset() {
    inputs.Clear();
    outputs.Clear();
    groupsFx.Clear();
    externalFx.Clear();
    externalInstruments.Clear();
    studio.Clear();
    presets.Clear();
}

// Input management
Vector<AudioBus> IOMatrixService::GetInputs() const {
    Vector<AudioBus> result;
    for(int i = 0; i < inputs.GetCount(); i++) {
        AudioBus bus;
        bus.name = inputs[i].name;
        bus.speakerConfig = inputs[i].speakerConfig;
        bus.audioDevice = inputs[i].audioDevice;
        bus.isExpanded = inputs[i].isExpanded;
        bus.devicePorts <<= inputs[i].devicePorts;  // Use <<= for deep copy
        result.Add(pick(bus));  // Use pick for move semantics
    }
    return result;
}

void IOMatrixService::AddInput(const AudioBus& bus) {
    AudioBus newBus;
    newBus.name = bus.name;
    newBus.speakerConfig = bus.speakerConfig;
    newBus.audioDevice = bus.audioDevice;
    newBus.isExpanded = bus.isExpanded;
    newBus.devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    inputs.Add(pick(newBus));  // Use pick() for move semantics
}

void IOMatrixService::RemoveInput(int index) {
    if (index >= 0 && index < inputs.GetCount()) {
        inputs.Remove(index);
    }
}

void IOMatrixService::UpdateInput(int index, const AudioBus& bus) {
    if (index >= 0 && index < inputs.GetCount()) {
        inputs[index].name = bus.name;
        inputs[index].speakerConfig = bus.speakerConfig;
        inputs[index].audioDevice = bus.audioDevice;
        inputs[index].isExpanded = bus.isExpanded;
        inputs[index].devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    }
}

// Output management
Vector<AudioBus> IOMatrixService::GetOutputs() const {
    Vector<AudioBus> result;
    for(int i = 0; i < outputs.GetCount(); i++) {
        AudioBus bus;
        bus.name = outputs[i].name;
        bus.speakerConfig = outputs[i].speakerConfig;
        bus.audioDevice = outputs[i].audioDevice;
        bus.isExpanded = outputs[i].isExpanded;
        bus.devicePorts <<= outputs[i].devicePorts;  // Use <<= for deep copy
        result.Add(pick(bus));  // Use pick for move semantics
    }
    return result;
}

void IOMatrixService::AddOutput(const AudioBus& bus) {
    AudioBus newBus;
    newBus.name = bus.name;
    newBus.speakerConfig = bus.speakerConfig;
    newBus.audioDevice = bus.audioDevice;
    newBus.isExpanded = bus.isExpanded;
    newBus.devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    outputs.Add(pick(newBus));  // Use pick() for move semantics
}

void IOMatrixService::RemoveOutput(int index) {
    if (index >= 0 && index < outputs.GetCount()) {
        outputs.Remove(index);
    }
}

void IOMatrixService::UpdateOutput(int index, const AudioBus& bus) {
    if (index >= 0 && index < outputs.GetCount()) {
        outputs[index].name = bus.name;
        outputs[index].speakerConfig = bus.speakerConfig;
        outputs[index].audioDevice = bus.audioDevice;
        outputs[index].isExpanded = bus.isExpanded;
        outputs[index].devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    }
}

// Groups/FX management
Vector<AudioBus> IOMatrixService::GetGroupsFx() const {
    Vector<AudioBus> result;
    for(int i = 0; i < groupsFx.GetCount(); i++) {
        AudioBus bus;
        bus.name = groupsFx[i].name;
        bus.speakerConfig = groupsFx[i].speakerConfig;
        bus.audioDevice = groupsFx[i].audioDevice;
        bus.isExpanded = groupsFx[i].isExpanded;
        bus.devicePorts <<= groupsFx[i].devicePorts;  // Use <<= for deep copy
        result.Add(pick(bus));  // Use pick for move semantics
    }
    return result;
}

void IOMatrixService::AddGroup(const AudioBus& bus) {
    AudioBus newBus;
    newBus.name = bus.name;
    newBus.speakerConfig = bus.speakerConfig;
    newBus.audioDevice = bus.audioDevice;
    newBus.isExpanded = bus.isExpanded;
    newBus.devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    groupsFx.Add(pick(newBus));  // Use pick() for move semantics
}

void IOMatrixService::RemoveGroup(int index) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx.Remove(index);
    }
}

void IOMatrixService::UpdateGroup(int index, const AudioBus& bus) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx[index].name = bus.name;
        groupsFx[index].speakerConfig = bus.speakerConfig;
        groupsFx[index].audioDevice = bus.audioDevice;
        groupsFx[index].isExpanded = bus.isExpanded;
        groupsFx[index].devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    }
}

void IOMatrixService::AddFxChannel(const AudioBus& bus) {
    AudioBus newBus;
    newBus.name = bus.name;
    newBus.speakerConfig = bus.speakerConfig;
    newBus.audioDevice = bus.audioDevice;
    newBus.isExpanded = bus.isExpanded;
    newBus.devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    groupsFx.Add(pick(newBus));  // Use pick() for move semantics
}

void IOMatrixService::RemoveFxChannel(int index) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx.Remove(index);
    }
}

void IOMatrixService::UpdateFxChannel(int index, const AudioBus& bus) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx[index].name = bus.name;
        groupsFx[index].speakerConfig = bus.speakerConfig;
        groupsFx[index].audioDevice = bus.audioDevice;
        groupsFx[index].isExpanded = bus.isExpanded;
        groupsFx[index].devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    }
}

// External FX management
Vector<ExternalFx> IOMatrixService::GetExternalFx() const {
    Vector<ExternalFx> result;
    for(int i = 0; i < externalFx.GetCount(); i++) {
        result.Add(externalFx[i]);  // Copy each element
    }
    return result;
}

void IOMatrixService::AddExternalFx(const ExternalFx& fx) {
    ExternalFx newFx;
    newFx.name = fx.name;
    newFx.sendConfig = fx.sendConfig;
    newFx.returnConfig = fx.returnConfig;
    newFx.midiDevice = fx.midiDevice;
    newFx.delayMs = fx.delayMs;
    newFx.sendGainDb = fx.sendGainDb;
    newFx.returnGainDb = fx.returnGainDb;
    newFx.isUsed = fx.isUsed;
    externalFx.Add(pick(newFx));  // Use pick() for move semantics
}

void IOMatrixService::RemoveExternalFx(int index) {
    if (index >= 0 && index < externalFx.GetCount()) {
        externalFx.Remove(index);
    }
}

void IOMatrixService::UpdateExternalFx(int index, const ExternalFx& fx) {
    if (index >= 0 && index < externalFx.GetCount()) {
        externalFx[index] = fx;
    }
}

// External Instruments management
Vector<ExternalInstrument> IOMatrixService::GetExternalInstruments() const {
    Vector<ExternalInstrument> result;
    for(int i = 0; i < externalInstruments.GetCount(); i++) {
        result.Add(externalInstruments[i]);  // Copy each element
    }
    return result;
}

void IOMatrixService::AddExternalInstrument(const ExternalInstrument& inst) {
    ExternalInstrument newInst;
    newInst.name = inst.name;
    newInst.monoReturnsCount = inst.monoReturnsCount;
    newInst.stereoReturnsCount = inst.stereoReturnsCount;
    newInst.midiDevice = inst.midiDevice;
    newInst.delayMs = inst.delayMs;
    newInst.returnGainDb = inst.returnGainDb;
    newInst.isUsed = inst.isUsed;
    externalInstruments.Add(pick(newInst));  // Use pick() for move semantics
}

void IOMatrixService::RemoveExternalInstrument(int index) {
    if (index >= 0 && index < externalInstruments.GetCount()) {
        externalInstruments.Remove(index);
    }
}

void IOMatrixService::UpdateExternalInstrument(int index, const ExternalInstrument& inst) {
    if (index >= 0 && index < externalInstruments.GetCount()) {
        externalInstruments[index] = inst;
    }
}

// Studio (Control Room) management
Vector<AudioBus> IOMatrixService::GetStudio() const {
    Vector<AudioBus> result;
    for(int i = 0; i < studio.GetCount(); i++) {
        AudioBus bus;
        bus.name = studio[i].name;
        bus.speakerConfig = studio[i].speakerConfig;
        bus.audioDevice = studio[i].audioDevice;
        bus.isExpanded = studio[i].isExpanded;
        bus.devicePorts <<= studio[i].devicePorts;  // Use <<= for deep copy
        result.Add(pick(bus));  // Use pick for move semantics
    }
    return result;
}

void IOMatrixService::AddStudioBus(const AudioBus& bus) {
    AudioBus newBus;
    newBus.name = bus.name;
    newBus.speakerConfig = bus.speakerConfig;
    newBus.audioDevice = bus.audioDevice;
    newBus.isExpanded = bus.isExpanded;
    newBus.devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    studio.Add(pick(newBus));  // Use pick() for move semantics
}

void IOMatrixService::RemoveStudioBus(int index) {
    if (index >= 0 && index < studio.GetCount()) {
        studio.Remove(index);
    }
}

void IOMatrixService::UpdateStudioBus(int index, const AudioBus& bus) {
    if (index >= 0 && index < studio.GetCount()) {
        studio[index].name = bus.name;
        studio[index].speakerConfig = bus.speakerConfig;
        studio[index].audioDevice = bus.audioDevice;
        studio[index].isExpanded = bus.isExpanded;
        studio[index].devicePorts <<= bus.devicePorts;  // Use <<= for deep copy of Vector
    }
}

// Preset management
void IOMatrixService::SavePreset(const String& name) {
    // Search for existing preset by name manually since U++ Vector doesn't have Find for string
    bool presetExists = false;
    for(int i = 0; i < presets.GetCount(); i++) {
        if(presets[i] == name) {
            presetExists = true;
            break;
        }
    }
    
    if (!presetExists) {
        presets.Add(name);
    }
    // In a real implementation, we would save the current state to a file
}

void IOMatrixService::LoadPreset(const String& name) {
    // In a real implementation, we would load the state from a file
    // For now, just validate that preset exists
    bool presetExists = false;
    for(int i = 0; i < presets.GetCount(); i++) {
        if(presets[i] == name) {
            presetExists = true;
            break;
        }
    }
    
    if (!presetExists) {
        LOG("Preset " + name + " does not exist");
    }
}

void IOMatrixService::DeletePreset(const String& name) {
    int index = -1;
    for(int i = 0; i < presets.GetCount(); i++) {
        if(presets[i] == name) {
            index = i;
            break;
        }
    }
    
    if (index >= 0) {
        presets.Remove(index);
    }
}

Vector<String> IOMatrixService::GetPresets() const {
    Vector<String> result;
    for(int i = 0; i < presets.GetCount(); i++) {
        result.Add(presets[i]);  // Copy each element
    }
    return result;
}

// Apply changes to the system
void IOMatrixService::ApplyChanges() {
    // In a real implementation, this would apply all routing changes to the audio system
    LOG("Applying I/O routing changes to the system");
}

// Get snapshots of current state
ValueMap IOMatrixService::GetSnapshot(ConnectionType type) const {
    ValueMap snapshot;

    switch (type) {
        case INPUTS:
            snapshot.Set("inputs", (int)inputs.GetCount());
            break;
        case OUTPUTS:
            snapshot.Set("outputs", (int)outputs.GetCount());
            break;
        case GROUPS_FX:
            snapshot.Set("groups_fx", (int)groupsFx.GetCount());
            break;
        case EXTERNAL_FX:
            snapshot.Set("external_fx", (int)externalFx.GetCount());
            break;
        case EXTERNAL_INSTRUMENTS:
            snapshot.Set("external_instruments", (int)externalInstruments.GetCount());
            break;
        case STUDIO:
            snapshot.Set("studio", (int)studio.GetCount());
            break;
    }

    return snapshot;
}

void IOMatrixService::ApplySnapshot(ConnectionType type, const ValueMap& snapshot) {
    // In a real implementation, this would restore the state from a snapshot
    LOG("Applying snapshot for connection type: " << (int)type);
}

} // namespace Devices
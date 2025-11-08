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
    inputs.Add(defaultInput);
    
    AudioBus defaultOutput;
    defaultOutput.name = "Stereo Out";
    defaultOutput.speakerConfig = "Stereo";
    defaultOutput.audioDevice = "ASIO DirectX Full Duplex";
    defaultOutput.devicePorts.Add("Channel 1");
    defaultOutput.devicePorts.Add("Channel 2");
    outputs.Add(defaultOutput);
    
    // Add default group and FX
    AudioBus defaultGroup;
    defaultGroup.name = "Group 1";
    defaultGroup.speakerConfig = "Stereo";
    groupsFx.Add(defaultGroup);
    
    ExternalFx defaultFx;
    defaultFx.name = "External FX";
    defaultFx.sendConfig = "Stereo/Stereo";
    externalFx.Add(defaultFx);
    
    ExternalInstrument defaultInst;
    defaultInst.name = "External Instrument";
    defaultInst.monoReturnsCount = 0;
    defaultInst.stereoReturnsCount = 0;
    externalInstruments.Add(defaultInst);
    
    // Add default studio bus
    AudioBus defaultStudio;
    defaultStudio.name = "Monitor 1";
    defaultStudio.speakerConfig = "Stereo";
    studio.Add(defaultStudio);
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
    return inputs;
}

void IOMatrixService::AddInput(const AudioBus& bus) {
    inputs.Add(bus);
}

void IOMatrixService::RemoveInput(int index) {
    if (index >= 0 && index < inputs.GetCount()) {
        inputs.Remove(index);
    }
}

void IOMatrixService::UpdateInput(int index, const AudioBus& bus) {
    if (index >= 0 && index < inputs.GetCount()) {
        inputs[index] = bus;
    }
}

// Output management
Vector<AudioBus> IOMatrixService::GetOutputs() const {
    return outputs;
}

void IOMatrixService::AddOutput(const AudioBus& bus) {
    outputs.Add(bus);
}

void IOMatrixService::RemoveOutput(int index) {
    if (index >= 0 && index < outputs.GetCount()) {
        outputs.Remove(index);
    }
}

void IOMatrixService::UpdateOutput(int index, const AudioBus& bus) {
    if (index >= 0 && index < outputs.GetCount()) {
        outputs[index] = bus;
    }
}

// Groups/FX management
Vector<AudioBus> IOMatrixService::GetGroupsFx() const {
    return groupsFx;
}

void IOMatrixService::AddGroup(const AudioBus& bus) {
    groupsFx.Add(bus);
}

void IOMatrixService::RemoveGroup(int index) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx.Remove(index);
    }
}

void IOMatrixService::UpdateGroup(int index, const AudioBus& bus) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx[index] = bus;
    }
}

void IOMatrixService::AddFxChannel(const AudioBus& bus) {
    groupsFx.Add(bus);
}

void IOMatrixService::RemoveFxChannel(int index) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx.Remove(index);
    }
}

void IOMatrixService::UpdateFxChannel(int index, const AudioBus& bus) {
    if (index >= 0 && index < groupsFx.GetCount()) {
        groupsFx[index] = bus;
    }
}

// External FX management
Vector<ExternalFx> IOMatrixService::GetExternalFx() const {
    return externalFx;
}

void IOMatrixService::AddExternalFx(const ExternalFx& fx) {
    externalFx.Add(fx);
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
    return externalInstruments;
}

void IOMatrixService::AddExternalInstrument(const ExternalInstrument& inst) {
    externalInstruments.Add(inst);
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
    return studio;
}

void IOMatrixService::AddStudioBus(const AudioBus& bus) {
    studio.Add(bus);
}

void IOMatrixService::RemoveStudioBus(int index) {
    if (index >= 0 && index < studio.GetCount()) {
        studio.Remove(index);
    }
}

void IOMatrixService::UpdateStudioBus(int index, const AudioBus& bus) {
    if (index >= 0 && index < studio.GetCount()) {
        studio[index] = bus;
    }
}

// Preset management
void IOMatrixService::SavePreset(const String& name) {
    if (!presets.Find(name)) {
        presets.Add(name);
    }
    // In a real implementation, we would save the current state to a file
}

void IOMatrixService::LoadPreset(const String& name) {
    // In a real implementation, we would load the state from a file
    // For now, just validate that preset exists
    if (presets.Find(name) < 0) {
        LOG("Preset " + name + " does not exist");
    }
}

void IOMatrixService::DeletePreset(const String& name) {
    int index = presets.Find(name);
    if (index >= 0) {
        presets.Remove(index);
    }
}

Vector<String> IOMatrixService::GetPresets() const {
    return presets;
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
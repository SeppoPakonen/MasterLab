#include "IOMatrixService.h"

// Define the static instance variable
am::IOMatrixService* am::IOMatrixService::instance = nullptr;

namespace am {

// Implementation for RoutingRepository
RoutingRepository::RoutingRepository() {
    InitializeDefaultPresets();
}

void RoutingRepository::InitializeDefaultPresets() {
    // Initialize with some default routing presets
    Vector<ConnectionPoint> stereoInOut;
    
    // Add default stereo input
    ConnectionPoint stereoIn;
    stereoIn.name = "Stereo In";
    stereoIn.id = "stereo_in_01";
    stereoIn.deviceName = "ASIO4ALL v2";
    stereoIn.portName = "1/2";
    stereoIn.speakers = "Stereo";
    stereoInOut.Add(stereoIn);
    
    // Add default stereo output
    ConnectionPoint stereoOut;
    stereoOut.name = "Stereo Out";
    stereoOut.id = "stereo_out_01";
    stereoOut.deviceName = "ASIO4ALL v2";
    stereoOut.portName = "1/2";
    stereoOut.speakers = "Stereo";
    stereoInOut.Add(stereoOut);
    
    presets.Add("Default Stereo", stereoInOut);
}

bool RoutingRepository::SavePreset(const String& name, const Vector<ConnectionPoint>& connections) {
    presets.GetAdd(name) = connections;
    return true; // In a real implementation, this might involve file I/O
}

bool RoutingRepository::LoadPreset(const String& name, Vector<ConnectionPoint>& connections) {
    if (presets.Find(name) >= 0) {
        connections = presets.Get(name);
        return true;
    }
    return false;
}

bool RoutingRepository::DeletePreset(const String& name) {
    return presets.RemoveKey(name);
}

Vector<String> RoutingRepository::GetAvailablePresets() const {
    Vector<String> result;
    for (const auto& key : presets.GetKeys()) {
        result.Add(key);
    }
    return result;
}

bool RoutingRepository::SaveCurrentRouting(const String& name) {
    // In a real implementation, this would save the current system routing state
    return true;
}

bool RoutingRepository::LoadRouting(const String& name) {
    // In a real implementation, this would load a routing state and apply it to the system
    return true;
}

bool RoutingRepository::DeleteRouting(const String& name) {
    // In a real implementation, this would delete a saved routing state
    return true;
}

// Implementation for IOMatrixService
IOMatrixService::IOMatrixService() {
    InitializeDefaultConnections();
}

IOMatrixService::~IOMatrixService() {
}

void IOMatrixService::InitializeDefaultConnections() {
    // Add default input connections
    ConnectionPoint defaultIn;
    defaultIn.name = "Input 1/2";
    defaultIn.id = "input_01_02";
    defaultIn.deviceName = "System Default";
    defaultIn.portName = "1/2";
    defaultIn.speakers = "Stereo";
    inputs.Add(defaultIn);
    
    // Add default output connections
    ConnectionPoint defaultOut;
    defaultOut.name = "Output 1/2";
    defaultOut.id = "output_01_02";
    defaultOut.deviceName = "System Default";
    defaultOut.portName = "1/2";
    defaultOut.speakers = "Stereo";
    outputs.Add(defaultOut);
    
    // Add default group/FX
    GroupFxConnection defaultGroup;
    defaultGroup.name = "Group 1";
    defaultGroup.id = "group_01";
    defaultGroup.speakers = "Stereo";
    defaultGroup.routeTo = "Main Out";
    groupsFxs.Add(defaultGroup);
    
    // Add default external FX
    ExternalFxConnection defaultFx;
    defaultFx.name = "Ext. FX 1";
    defaultFx.id = "ext_fx_01";
    defaultFx.audioDevice = "System Default";
    defaultFx.inputPort = "3/4";
    defaultFx.outputPort = "5/6";
    defaultFx.sendGainDb = 0.0;
    defaultFx.returnGainDb = 0.0;
    externalFxs.Add(defaultFx);
    
    // Add default external instrument
    ExternalInstrumentConnection defaultInst;
    defaultInst.name = "Ext. Instrument 1";
    defaultInst.id = "ext_inst_01";
    defaultInst.audioDevice = "System Default";
    defaultInst.outputPort = "7/8";
    defaultInst.midiDevice = "MIDI Device 1";
    externalInstruments.Add(defaultInst);
    
    // Add default studio connection
    StudioConnection defaultStudio;
    defaultStudio.name = "Control Room";
    defaultStudio.id = "studio_ctrl_room";
    defaultStudio.speakers = "Stereo";
    defaultStudio.audioDevice = "System Default";
    defaultStudio.devicePort = "9/10";
    studioConnections.Add(defaultStudio);
}

Vector<ConnectionPoint> IOMatrixService::GetInputs() const {
    return inputs;
}

bool IOMatrixService::SetInput(const ConnectionPoint& input) {
    // Check if input with this ID already exists
    for (auto& existingInput : inputs) {
        if (existingInput.id == input.id) {
            existingInput = input;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    inputs.Add(input);
    return true;
}

bool IOMatrixService::RemoveInput(const String& id) {
    for (int i = 0; i < inputs.GetCount(); i++) {
        if (inputs[i].id == id) {
            inputs.Remove(i);
            return true;
        }
    }
    return false;
}

Vector<ConnectionPoint> IOMatrixService::GetOutputs() const {
    return outputs;
}

bool IOMatrixService::SetOutput(const ConnectionPoint& output) {
    // Check if output with this ID already exists
    for (auto& existingOutput : outputs) {
        if (existingOutput.id == output.id) {
            existingOutput = output;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    outputs.Add(output);
    return true;
}

bool IOMatrixService::RemoveOutput(const String& id) {
    for (int i = 0; i < outputs.GetCount(); i++) {
        if (outputs[i].id == id) {
            outputs.Remove(i);
            return true;
        }
    }
    return false;
}

Vector<GroupFxConnection> IOMatrixService::GetGroupsFx() const {
    return groupsFxs;
}

bool IOMatrixService::SetGroupFx(const GroupFxConnection& group) {
    // Check if group with this ID already exists
    for (auto& existingGroup : groupsFxs) {
        if (existingGroup.id == group.id) {
            existingGroup = group;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    groupsFxs.Add(group);
    return true;
}

bool IOMatrixService::RemoveGroupFx(const String& id) {
    for (int i = 0; i < groupsFxs.GetCount(); i++) {
        if (groupsFxs[i].id == id) {
            groupsFxs.Remove(i);
            return true;
        }
    }
    return false;
}

Vector<ExternalFxConnection> IOMatrixService::GetExternalFx() const {
    return externalFxs;
}

bool IOMatrixService::SetExternalFx(const ExternalFxConnection& fx) {
    // Check if external FX with this ID already exists
    for (auto& existingFx : externalFxs) {
        if (existingFx.id == fx.id) {
            existingFx = fx;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    externalFxs.Add(fx);
    return true;
}

bool IOMatrixService::RemoveExternalFx(const String& id) {
    for (int i = 0; i < externalFxs.GetCount(); i++) {
        if (externalFxs[i].id == id) {
            externalFxs.Remove(i);
            return true;
        }
    }
    return false;
}

Vector<ExternalInstrumentConnection> IOMatrixService::GetExternalInstruments() const {
    return externalInstruments;
}

bool IOMatrixService::SetExternalInstrument(const ExternalInstrumentConnection& instrument) {
    // Check if external instrument with this ID already exists
    for (auto& existingInstrument : externalInstruments) {
        if (existingInstrument.id == instrument.id) {
            existingInstrument = instrument;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    externalInstruments.Add(instrument);
    return true;
}

bool IOMatrixService::RemoveExternalInstrument(const String& id) {
    for (int i = 0; i < externalInstruments.GetCount(); i++) {
        if (externalInstruments[i].id == id) {
            externalInstruments.Remove(i);
            return true;
        }
    }
    return false;
}

Vector<StudioConnection> IOMatrixService::GetStudio() const {
    return studioConnections;
}

bool IOMatrixService::SetStudio(const StudioConnection& studio) {
    // Check if studio connection with this ID already exists
    for (auto& existingStudio : studioConnections) {
        if (existingStudio.id == studio.id) {
            existingStudio = studio;  // Update existing
            return true;
        }
    }
    // If not found, add as new
    studioConnections.Add(studio);
    return true;
}

bool IOMatrixService::RemoveStudio(const String& id) {
    for (int i = 0; i < studioConnections.GetCount(); i++) {
        if (studioConnections[i].id == id) {
            studioConnections.Remove(i);
            return true;
        }
    }
    return false;
}

IOMatrixService& IOMatrixService::GetInstance() {
    if (!instance) {
        instance = new IOMatrixService();
    }
    return *instance;
}

void IOMatrixService::ApplyChanges() {
    // Apply changes to the audio system
    // In a real implementation, this would update the actual audio routing
    // based on the current state of all connection vectors
    LOG("Applying I/O matrix changes to audio system");
    
    // For now, just log the changes
    for (const auto& input : inputs) {
        LOG("Input: " << input.name << " -> " << input.deviceName << " (" << input.portName << ")");
    }
    
    for (const auto& output : outputs) {
        LOG("Output: " << output.name << " <- " << output.deviceName << " (" << output.portName << ")");
    }
}

}
#include "ModMatrix.h"

namespace DSP {

ModMatrix::ModMatrix() {
    // Initialize with no mappings
}

void ModMatrix::AddMapping(ModSource source, ModDestination destination, ParameterValue amount) {
    // Check if mapping already exists and update if so
    for (auto& mapping : mappings) {
        if (mapping.source == source && mapping.destination == destination) {
            mapping.amount = amount;
            return;
        }
    }
    // Add new mapping if it doesn't exist
    mappings.Add(ModulationMapping(source, destination, amount));
}

void ModMatrix::RemoveMapping(ModSource source, ModDestination destination) {
    for (int i = 0; i < mappings.GetCount(); i++) {
        if (mappings[i].source == source && mappings[i].destination == destination) {
            mappings.Remove(i--);
        }
    }
}

void ModMatrix::Process() {
    // In a real implementation, this would calculate modulation values
    // and apply them to destination parameters
    // For now, just a placeholder implementation
}

ParameterValue ModMatrix::GetModulationAmount(ModSource source, ModDestination destination) const {
    for (const auto& mapping : mappings) {
        if (mapping.source == source && mapping.destination == destination) {
            return mapping.amount;
        }
    }
    return 0.0;
}

Vector<ModulationMapping> ModMatrix::GetMappings() const {
    return mappings;
}

void ModMatrix::Clear() {
    mappings.Clear();
}

} // namespace DSP